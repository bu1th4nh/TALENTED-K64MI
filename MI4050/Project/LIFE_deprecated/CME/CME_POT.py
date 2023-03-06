import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib
import os
import ot


matplotlib.use('Agg')

id_list = os.listdir('../data/json/split')
content = []
for id in id_list:
    content.append(open('../data/json/split/'+id).readline())

p_list = [0, 0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 0.5, 1.0, 10, 100]
# p_list = [0]

if not os.path.exists('figures/POT'):
    os.makedirs('figures/POT')

if not os.path.exists('matrix'):
    os.makedirs('matrix')

for epoch in range(len(p_list)):

    df_null = None
    df_ot = None
    df_ot_f = None

    penalty = p_list[epoch]
    print('p:{}'.format(penalty))
    w = None

    length = 48

    w_t = 1
    idx = np.arange(48)
    idx = (idx -np.mean(idx) )/ np.std(idx)
    M1_t = np.tile(idx, (48, 1))
    M2_t = M1_t.transpose()
    M_t = (M1_t - M2_t)**2 * w_t


    a = np.ones(48)/48
    b = np.ones(48)/48
    for i in range(len(content)):
    # for i in range(100): 
        if i % 20 == 0:
            print('Processing {} of {}'.format(i, len(content)))
        df = pd.read_json(content[i])
        df_values = pd.DataFrame(df['forward']['values'])
        # df_forward = pd.DataFrame(df['forward']['forwards'])
        df_mask = pd.DataFrame(df['forward']['masks'])
        df_deltas = pd.DataFrame(df['forward']['deltas']).astype(int)
        df_values[~df_mask.astype(bool)] = np.nan
        df_values.interpolate(method='linear', axis=0, inplace=True)
        # distance = ot.distance_matrix_fast(df_values.to_numpy().astype(float))
        df_values.fillna(0, inplace=True)

        distance = np.zeros((df_values.shape[1], df_values.shape[1]))

        for d1 in range(df_values.shape[1]):
            for d2 in range(d1 + 1, df_values.shape[1]):
                # cost matrix
                v1 = df_values.iloc[:, d1]
                v2 = df_values.iloc[:, d2]
                # M_v = abs(np.tile(v1, (48, 1)) - np.tile(v2, (48, 1)).transpose())
                M_v = (np.tile(v1, (48, 1)) - np.tile(v2, (48, 1)).transpose())**2
                M_p = (np.tile(df_deltas.iloc[:, d1] - 1, (48, 1)) + np.tile(df_deltas.iloc[:, d2] - 1,
                                                                             (48, 1))) * penalty
                # M_p = np.zeros_like(M_v)
                M = M_v + M_t + M_p
                distance[d1][d2] = ot.emd2(a, b, M)



        num = df_mask.sum()
        num = np.tile(num, (35, 1))
        w_matrix = (num + num.transpose()) / (2 * length)


        if df_ot is not None:
            df_ot += distance * w_matrix
            w += w_matrix
        else:
            df_ot = distance * w_matrix
            w = w_matrix
        #

    inf_idx = np.isinf(df_ot)
    df_ot[inf_idx] = 0
    nan_idx = np.isnan(df_ot)
    df_ot[nan_idx] = 0
    # print(w)
    df_ot = df_ot / (w+1e-5)
    df_ot += df_ot.transpose()
    df_ot[np.where(np.eye(df_ot.shape[0], dtype=bool))] += np.min(df_ot[np.where(~np.eye(df_ot.shape[0], dtype=bool))])




    def normalization(data):
        _range = np.max(data) - np.min(data)
        return (data - np.min(data)) / _range


    # df_ot_exp = normalization(np.exp(-df_ot))
    # plt.figure()
    # column_names = [i for i in range(1, 36)]
    # df_ot_exp = pd.DataFrame(df_ot_exp, columns=column_names, index=column_names)
    # sns.heatmap(abs(df_ot_exp), cmap='Reds')
    # plt.savefig('figures/POT/p_' + str(penalty) + '.eps', format='eps', dpi=300, bbox_inches='tight')
    # plt.savefig('figures/POT/p_' + str(penalty) + '.png', format='png', bbox_inches='tight')
    # plt.close()

    df_ot_inv = normalization(1 / df_ot)
    column_names = [i for i in range(1, 36)]
    df_ot_inv = pd.DataFrame(df_ot_inv, columns=column_names, index=column_names)
    plt.figure()
    sns.heatmap(abs(df_ot_inv), cmap='Reds')
    # plt.savefig('../../../docs/figures/POT/p_inv_' + str(penalty) + '.eps', format='eps', dpi=300, bbox_inches='tight')
    plt.savefig('figures/POT/p_' + str(penalty) + '.png', format='png', bbox_inches='tight')
    plt.close()

    # np.savetxt('../data/POT_exp_' + str(penalty) + '.csv', df_ot_exp.to_numpy(), delimiter=',')
    np.savetxt('matrix/POT_' + str(penalty) + '.csv', df_ot_inv.to_numpy(), delimiter=',')

print('Done! Figures are saved to \'{}\', Correlation Matrices are saved to \'{}\''.format('figures/POT/','matrix/'))