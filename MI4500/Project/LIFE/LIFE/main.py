import copy
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.optim.lr_scheduler import StepLR
import os
import numpy as np

# import datetime
import datetime
import utils
from model import LIFENet
import argparse
import data_loader
import pandas as pd
import ujson as json

from sklearn import metrics
from sklearn.model_selection import KFold


parser = argparse.ArgumentParser()
parser.add_argument('--epochs', type=int, default=100)
parser.add_argument('--batch_size', type=int, default=64)
parser.add_argument('--impute_weight', type=float, default=1)
parser.add_argument('--label_weight', type=float, default=1)
parser.add_argument('--C', type=str, default='PDTW')
parser.add_argument('--T', type=int, default=48)
parser.add_argument('--D', type=int, default=35)
parser.add_argument('--k', type=int, default=6)
parser.add_argument('--factor', type=int, default=3)
parser.add_argument('--dropout', type=float, default=0.2)
args = parser.parse_args()




def train(model, model_save_path=None):


    if torch.cuda.is_available():
        model = model.cuda()

    optimizer = optim.Adam(model.parameters(), lr=1e-3)


    train_iter, test_iter = data_loader.get_loader(data_path='../data/json/split', batch_size=args.batch_size)

    AUC_max_test = 0.0
    AUC_max_train = 0.0


    for epoch in range(args.epochs):
        model.train()

        run_loss = 0.0
        train_time = []
        for idx, data in enumerate(train_iter):
            data = utils.to_var(data)
            values = data['forward']['values']
            masks = data['forward']['masks']
            deltas_f = data['forward']['deltas']
            # deltas_b = data['backward']['deltas'].flip(dims=[1])

            labels = data['labels'].view(-1, 1)

            tSt = datetime.datetime.now()

            out, imput = model(values, masks, deltas_f)

            t = (datetime.datetime.now() - tSt).total_seconds()
            train_time.append(t)

            x_loss = torch.sum(torch.abs(values - imput) * masks) / (torch.sum(torch.mean(masks, dim=1)) + 1e-5)

            # y_loss = binary_cross_entropy_with_logits(out, labels, reduce=False)
            # is_train = data['is_train'].view(-1, 1)
            # y_loss = torch.sum(y_loss * is_train) / (torch.sum(is_train) + 1e-5)

            y_loss = F.binary_cross_entropy_with_logits(out, labels)

            loss = args.impute_weight * x_loss + args.label_weight * y_loss

            # loss = torch.binary_cross_entropy_with_logits(out, labels)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()


            run_loss += loss.item()
            if idx % 20 == 0:
                print(
                    '\r Progress epoch {}, {:.2f}%, average loss {}'.format(epoch, (idx + 1) * 100.0 / len(train_iter),
                                                                            run_loss / (idx + 1.0)), )

        AUC_test = evaluate(model, test_iter)
        AUC_train = evaluate(model, train_iter)
        # if AUC_test > AUC_max_test and AUC_test > 0.84 and model_save_path is not None:
        #     torch.save(model.state_dict(), model_save_path + '/test_' + str(AUC_test))

        AUC_max_test = max(AUC_test, AUC_max_test)
        AUC_max_train = max(AUC_train, AUC_max_train)

        print('AUC_train %f, max %f' % (
        AUC_train, AUC_max_train))
        print('AUC_test %f, max %f' % (
        AUC_test, AUC_max_test))



def evaluate(model, val_iter):
    model.eval()

    labels = []
    preds = []


    for idx, data in enumerate(val_iter):
        data = utils.to_var(data)
        values = data['forward']['values']
        masks = data['forward']['masks']
        deltas_f = data['forward']['deltas']
        # deltas_b = data['backward']['deltas'].flip(dims=[1])

        label = data['labels'].view(-1, 1)


        out, imput = model(values, masks, deltas_f)

        # collect test label & prediction
        pred = torch.sigmoid(out).data.cpu().numpy()
        label = label.data.cpu().numpy()

        labels += label.tolist()
        preds += pred.tolist()


    labels = np.asarray(labels).astype('int32')
    preds = np.asarray(preds)

    AUC = metrics.roc_auc_score(labels, preds)

    return AUC




def run():


    if args.C == 'Pearson':
        C = torch.Tensor(abs(pd.read_csv('../data/Pearson.csv', header=None)).to_numpy()).requires_grad_(
            False)
    elif args.C == 'diag':
        C = torch.eye(35).requires_grad_(False)
    elif args.C == 'rand':
        C = torch.rand(35, 35).requires_grad_(False)
    elif args.C == 'ones':
        C = torch.ones(35, 35).requires_grad_(False)
    elif args.C == 'PDTW':
        C = torch.Tensor(pd.read_csv('../data/PDTW_0.5.csv', header=None).to_numpy()).requires_grad_(
            False)
    else:
        print('Unknow C! C is set to \'PDTW\'!')
        C = torch.Tensor(pd.read_csv('../data/PDTW_0.5.csv', header=None).to_numpy()).requires_grad_(
            False)
    print(args.C, C)


    model = LIFENet(D=args.D, k=args.k, T=args.T, n_group=3, out_size=1, C=C, F=args.factor, dropout=args.dropout)
    total_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
    print('Total params is {}'.format(total_params))
    #
    #
    if torch.cuda.is_available():
        model = model.cuda()

    cur_time = datetime.datetime.now()
    model_save_path = os.path.join('../model', cur_time.strftime("%Y_%m_%d_%H_%M_%S"))
    os.makedirs(model_save_path)
    model_save_path = None
    train(model, model_save_path=model_save_path)


if __name__ == '__main__':



    run()
    print(args)
