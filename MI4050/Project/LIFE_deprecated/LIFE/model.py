import torch
import numpy as np
import torch.nn as nn
import torch.nn.init as init
import torch.nn.functional as F


class LIFENet(nn.Module):
    def __init__(self, D, k, T, n_group, out_size, C=None, F=3, dropout=0.2):
        '''
        Feature Separated Attention (LIFE) Network
        :param D: dimension of MTS = 96
        :param k: dimension of each feature part = 10
        :param T: max length of time series data = 96
        :param C: correlation matrix
        :param out_size: dimension of output = 10
        :param F: number of interpolation timestamps F
        :param n_group: number of input variable group, if the input is (X, \delta_f, M) then n_group=3, if the input is (X, \delta_f, M, \delta_b) then n_group=4
        :param dropout: dropout rate
        '''
        super(LIFENet, self).__init__()
        if C is None:
            print('C is set to full-1 matrix!')
            C = torch.ones(D, D)
        self.n_group = n_group
        self.InputEmbedding = InputEmbedding(D, k, T, n_group, C, dropout=dropout)
        self.SelfAttention = SelfAttention(k * D, dropout=dropout)
        self.TemporalDecay = TemporalDecay(D, k, T)
        self.Impute = ImputationModule(D, k)
        self.DenseInterpolation = DenseInterpolation(T, F)
        self.Predict = PredictionModule(k * D, F, out_size)

    def forward(self, X, M, deltas_f, deltas_b=None):
        '''

        :param X:
        :param M:
        :param deltas_f:
        :param deltas_b:
        :return: prediction, imputation
        '''

        # if self.n_group == 4 and deltas_b is not None:
        #     inputs = torch.cat([X, M, deltas_f, deltas_b], dim=2)
        # else:
        #     inputs = torch.cat([X, M, deltas_f], dim=2)

        inputs = torch.cat([X, M, deltas_f], dim=2)
        h_e = self.InputEmbedding(inputs)
        h_a = self.SelfAttention(h_e)
        h_r = self.TemporalDecay(h_a, deltas_f, M)
        imput = self.Impute(h_r)
        feature = self.DenseInterpolation(h_r)
        out = self.Predict(feature)

        return out, imput


class PositionalEncoding(nn.Module):
    def __init__(self, kD, T):
        '''
        Positional encoding, the position is represented by one-hot vector
        :param kD: dimension of the feature at a time stamp, which equals to k*D
        :param T: max length of time series data
        '''
        super(PositionalEncoding, self).__init__()
        self.d_model = kD
        self.embeds = nn.Embedding(T, kD)
        pos = torch.arange(0, T)
        self.register_buffer("pos", pos)

    def forward(self, x):
        T = x.shape[1]
        x = x + self.embeds(self.pos[:T])

        return x

#
#
# class InputEmbedding(nn.Module):
#     def __init__(self, d_input, n_group, d_per_group, seq_len_max, C = None, dropout = 0.2):
#         super(InputEmbedding, self).__init__()
#         d_model = d_input*d_per_group
#         self.w = nn.Parameter(torch.empty(d_model, d_input*n_group))
#         init.xavier_uniform_(self.w)
#
#         if C is None:
#             C = torch.ones(d_input, d_input).requires_grad_(False)
#         C_mask = C.repeat(d_per_group, n_group)
#         self.register_buffer('C_mask', C_mask)
#
#         # self.input_emb = PositionWiseFeedForward(d_input, d_model)
#         self.pos_encoding = PositionalEncoding(d_model, seq_len_max, pe_type='ont_hot')
#         self.elu = nn.ELU()
#         self.dropout = nn.Dropout(dropout)
#
#     def forward(self, x):
#         # batch_size, seq_len, d_input = x.size()
#         # emb_vector = self.pos_encoding(self.input_emb(x))
#         emb_vector = F.linear(x, self.w * self.C_mask)
#         emb_vector = self.pos_encoding(emb_vector)
#         h_vector = self.dropout(self.elu(emb_vector))
#
#         return h_vector


class InputEmbedding(nn.Module):
    def __init__(self, D, k, T, n_group=3, C=None, dropout=0.2):
        '''
        embed the input sequence to feature sequence, meanwhile separating the features by correlation matrix.
        :param D: dimension of MTS
        :param k: dimension of each feature part
        :param T: max length of time series data
        :param n_group: number of input variable group, if the input is (X, \delta_f, M) then n_group=3, if the input is (X, \delta_f, M, \delta_b) then n_group=4
        :param C: correlation matrix
        :param dropout: dropout rate
        '''
        super(InputEmbedding, self).__init__()
        self.W_e = nn.Parameter(torch.zeros(k * D, D * n_group))
        self.b_e = nn.Parameter(torch.zeros(k * D))
        init.xavier_uniform_(self.W_e)

        if C is None:
            C = torch.ones(D, D).requires_grad_(False)

        # expand C
        C_prime = C.repeat(k, n_group).requires_grad_(False)
        self.register_buffer('C_prime', C_prime)

        self.pos_encoding = PositionalEncoding(k * D, T)
        self.elu = nn.ELU()
        self.dropout = nn.Dropout(dropout)

    def forward(self, x):
        emb_vector = F.linear(x, self.W_e * self.C_prime, self.b_e)
        emb_vector = self.pos_encoding(emb_vector)
        h_e = self.dropout(self.elu(emb_vector))

        return h_e


class SelfAttention(nn.Module):
    def __init__(self, kD, dropout=0.2):
        '''
        apply Self-Attention mechanism to the separated feature sequence.
        :param kD: dimension of the feature at a time stamp, which equals to k*D
        :param dropout: dropout rate
        '''
        super(SelfAttention, self).__init__()

        self.W_a = nn.Parameter(torch.empty(kD, kD))
        self.V_a = nn.Parameter(torch.empty(kD, kD))

        self.w_a = nn.Parameter(torch.empty(1, kD))
        self.b_a = nn.Parameter(torch.zeros(kD))

        init.xavier_uniform_(self.W_a)
        init.xavier_uniform_(self.V_a)
        init.xavier_uniform_(self.w_a)
        self.tanh = nn.Tanh()

        self.dropout = nn.Dropout(dropout)

    def forward(self, h_e):
        batch_size, T, kD = h_e.size()

        # Make logits
        key_vec = F.linear(h_e, self.W_a).unsqueeze(1)  # (batch, 1, T, d_a)
        query_vec = F.linear(h_e, self.V_a).unsqueeze(2)  # (batch, T, 1, d_a)
        logits = F.linear(self.tanh((key_vec + query_vec)), self.w_a)  # (batch, T, T, hid_dim)

        # Attention scores
        # (batch, T, T, 1)
        scores = torch.softmax(logits, dim=2)
        scores = self.dropout(scores)

        # Attention results
        h_e = h_e.unsqueeze(1).expand(batch_size, T, T, kD)
        h_a = torch.sum(scores * h_e, dim=2)

        return h_a


class TemporalDecay(nn.Module):
    def __init__(self, D, k, T):
        '''
        repair the feature parts corresponding to the missing vairables and make other parts unaffected, for which we apply Decay mechanism
        :param D: dimension of MTS
        :param k: dimension of each feature part
        :param T: sequence length
        '''
        super(TemporalDecay, self).__init__()
        self.W = nn.Parameter(torch.zeros(k * D))
        self.b = nn.Parameter(torch.rand(k * D))
        nn.init.uniform_(self.W, 0, 1)
        time_steps = torch.arange(T).requires_grad_(False).cuda()

        self.register_buffer('time_steps', time_steps)


    def forward(self, h_a, deltas_f, M, deltas_b=None):
        # h: [batch, T, k*D]
        # deltas: [batch, T, D]
        # masks: [batch, T, D]
        batch_size, T, D = deltas_f.size()
        k = int(h_a.size(-1) / D)
        masks_h = M.repeat(1, 1, k).requires_grad_(False)
        # masks_h = M.expand(batch_size, T, k*D).requires_grad_(False)

        # forward decay
        # gamma_f: [batch, T, D]
        gamma_f = F.relu(deltas_f.repeat(1, 1, k) * self.W + self.b)

        gamma_f = torch.exp(-gamma_f)


        # index = self.time_steps.repeat(batch_size, D, 1)
        index = self.time_steps.expand(batch_size, D, T)
        index = index.permute(0, 2, 1)
        # find the last observation
        index = index - (deltas_f - 1).long()
        h_forward = torch.gather(h_a, dim=1, index=index.repeat(1, 1, k).contiguous())
        # h_forward = h_forward.contiguous()
        h = masks_h * h_a + (1 - masks_h) * (gamma_f * h_forward + (1 - gamma_f) * h_a)

        return h


class DenseInterpolation(nn.Module):
    def __init__(self, T, F):
        """
        :param T: sequence length
        :param F: number of interpolation timestamps F
        """
        super(DenseInterpolation, self).__init__()
        self.T = T
        self.F = F

        W = np.zeros((F, T), dtype=np.float32)
        for t in range(T):
            p = np.array((F * (t + 1)) / T, dtype=np.float32)
            for f in range(F):
                tmp = np.array(1 - (np.abs(p - (1 + f)) / F), dtype=np.float32)
                w = np.power(tmp, 2, dtype=np.float32)
                W[f, t] = w

        W = torch.tensor(W).float().unsqueeze(0)
        self.register_buffer("W", W)

    def forward(self, h_r):
        # h_r: [batch, T, k*D]
        kD = h_r.shape[2]
        w = self.W.expand(h_r.shape[0], self.F, self.T).requires_grad_(False)

        V = torch.bmm(w, h_r).transpose_(1, 2)
        v = V.contiguous().view(-1, int(self.F * kD))
        return v


class ImputationModule(nn.Module):
    def __init__(self, D, k):
        super(ImputationModule, self).__init__()
        self.W = nn.Parameter(torch.empty(D, k * D))
        self.b = nn.Parameter(torch.zeros(D))
        init.xavier_uniform_(self.W)

        group_mask = torch.eye(D, D).repeat(1, k)
        self.register_buffer('group_mask', group_mask)

    def forward(self, h_r):
        # only use group features to imputation
        x_imput = F.linear(h_r, self.W * self.group_mask, self.b)
        return x_imput


class PredictionModule(nn.Module):
    def __init__(self, kD, F, out_size):
        super(PredictionModule, self).__init__()
        self.fc = nn.Linear((kD * F), out_size)
        # nn.init.normal_(self.fc.weight, std=0.02)
        # nn.init.normal_(self.fc.bias, 0)

    def forward(self, v):
        out = self.fc(v)
        return out
