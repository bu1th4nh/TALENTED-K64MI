import copy
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.optim.lr_scheduler import StepLR
import os
import numpy as np

from torchmetrics import MeanAbsolutePercentageError

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
from sklearn.metrics import mean_squared_error, mean_absolute_error, mean_absolute_percentage_error
from tqdm import tqdm

parser = argparse.ArgumentParser()
parser.add_argument('--epochs', type=int, default=200)
parser.add_argument('--batch_size', type=int, default=96)
parser.add_argument('--impute_weight', type=float, default=1)
parser.add_argument('--label_weight', type=float, default=1)
parser.add_argument('--C', type=str, default='PDTW')
parser.add_argument('--T', type=int, default=128)
parser.add_argument('--D', type=int, default=10)
parser.add_argument('--k', type=int, default=10)
parser.add_argument('--factor', type=int, default=3)
parser.add_argument('--dropout', type=float, default=0.2)
parser.add_argument('--metric', type=str, default="MSE")
args = parser.parse_args()



loss_module = None;
loss_eval   = None;
loss_str    = None;

if(args.metric == "MSE"):
    loss_module = nn.MSELoss()
    loss_eval   = mean_squared_error
    loss_str    = "MSE"
elif(args.metric == "MAE"):
    loss_module = nn.L1Loss()
    loss_eval   = mean_absolute_error
    loss_str    = "MAE"
elif(args.metric == "MAPE"):
    loss_module = MeanAbsolutePercentageError()
    loss_eval   = mean_absolute_percentage_error
    loss_str    = "MAPE"

Ariel = pd.DataFrame(columns=['loss', f'{loss_str}_train', f'{loss_str}_test', f'{loss_str}_min_train', f'{loss_str}_min_test', 'time'])
print("Current metric: ", loss_str)

def train(model, model_save_path=None):


    if torch.cuda.is_available():
        model = model.cuda()

    optimizer = optim.Adam(model.parameters(), lr=1e-3)


    train_iter, test_iter = data_loader.get_loader(
        data_train='/home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/data/json/split-train', 
        data_valid='/home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/data/json/split-valid', 
        batch_size=args.batch_size
    )

    metric_min_test = np.inf
    metric_min_train = np.inf


    for epoch in range(args.epochs):
        model.train()

        run_loss = 0.0
        train_time = []
        for idx, data in tqdm(enumerate(train_iter), desc = 'Training, Epoch #{}'.format(epoch + 1), total = len(train_iter), unit = 'batch'):
            data = utils.to_var(data)
            values = data['forward']['values']
            masks = data['forward']['masks']
            deltas_f = data['forward']['deltas']
            # deltas_b = data['backward']['deltas'].flip(dims=[1])

            # print(np.shape(data))
            # print(np.shape(values))
            # print(np.shape(masks))

            labels = data['labels']

            tSt = datetime.datetime.now()

            out, imput = model(values, masks, deltas_f)

            t = (datetime.datetime.now() - tSt).total_seconds()
            train_time.append(t)

            x_loss = torch.sum(torch.abs(values - imput) * masks) / (torch.sum(torch.mean(masks, dim=1)) + 1e-5)

            # y_loss = binary_cross_entropy_with_logits(out, labels, reduce=False)
            # is_train = data['is_train'].view(-1, 1)
            # y_loss = torch.sum(y_loss * is_train) / (torch.sum(is_train) + 1e-5)

            y_loss = (loss_module)(out, labels)

            loss = args.impute_weight * x_loss + args.label_weight * y_loss

            # loss = torch.binary_cross_entropy_with_logits(out, labels)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()


            run_loss += loss.item()
            
        print('Average loss {}'.format(run_loss / (idx + 1.0)))

        metric_test = evaluate(model, test_iter, descc = "Testing Epoch #{}".format(epoch + 1))
        metric_train = evaluate(model, train_iter, descc = "Validating Epoch #{}".format(epoch + 1))
        # if MSE_test > MSE_min_test and MSE_test > 0.84 and model_save_path is not None:
        #     torch.save(model.state_dict(), model_save_path + '/test_' + str(MSE_test))

        metric_min_test = min(metric_test, metric_min_test)
        metric_min_train = min(metric_train, metric_min_train)

        print(f'{loss_str}_train %f, min %f' % (
        metric_train, metric_min_train))
        print(f'{loss_str}_test %f, min %f' % (
        metric_test, metric_min_test))

        Ariel.loc[epoch] = [run_loss / (idx + 1.0), metric_train, metric_test, metric_min_train, metric_min_test, np.mean(train_time)]

        if(epoch % 4 == 0 or epoch == args.epochs - 1): 
            Ariel.to_csv(model_save_path + '/Loss_log_' + loss_str + '_' + args.C + '_' + str(args.factor) + '_' + str(args.dropout) + '.csv')
            print("Snapshot loss saved to" + model_save_path + '/Loss_log_' + loss_str + '_' + args.C + '_' + str(args.factor) + '_' + str(args.dropout) + '.csv')





def evaluate(model, val_iter, descc):
    model.eval()

    labels = []
    preds = []


    for idx, data in tqdm(enumerate(val_iter), desc = descc):
        data = utils.to_var(data)
        values = data['forward']['values']
        masks = data['forward']['masks']
        deltas_f = data['forward']['deltas']
        # deltas_b = data['backward']['deltas'].flip(dims=[1])

        label = data['labels']


        out, imput = model(values, masks, deltas_f)

        # collect test label & prediction
        pred = out.data.cpu().numpy()
        label = label.data.cpu().numpy()

        labels += label.tolist()
        preds += pred.tolist()


    labels = np.asarray(labels)
    preds = np.asarray(preds)

    metric = loss_eval(labels, preds)

    return metric



def run():


    if args.C == 'Pearson':
        C = torch.Tensor(abs(pd.read_csv('../data/Pearson.csv', header=None)).to_numpy()).requires_grad_(
            False)
    elif args.C == 'diag':
        C = torch.eye(10).requires_grad_(False)
    elif args.C == 'rand':
        C = torch.rand(10, 10).requires_grad_(False)
    elif args.C == 'ones':
        C = torch.ones(10, 10).requires_grad_(False)
    elif args.C == 'PDTW0.01':
        C = torch.Tensor(pd.read_csv('/home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/CME/matrix/PDTW_0.01.csv', header=None).to_numpy()).requires_grad_(
            False)
    elif args.C == 'PDTW0.1':
        C = torch.Tensor(pd.read_csv('/home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/CME/matrix/PDTW_0.1.csv', header=None).to_numpy()).requires_grad_(
            False)
    elif args.C == 'PDTW0.5':
        C = torch.Tensor(pd.read_csv('/home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/CME/matrix/PDTW_0.5.csv', header=None).to_numpy()).requires_grad_(
            False)
    else:
        print('Unknow C! C is set to \'PDTW\'!')
        C = torch.Tensor(pd.read_csv('/home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/CME/matrix/PDTW_0.01.csv', header=None).to_numpy()).requires_grad_(
            False)
    print(args.C, C)


    model = LIFENet(D=args.D, k=args.k, T=args.T, n_group=3, out_size=10, C=C, F=args.factor, dropout=args.dropout)
    total_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
    print('Total params is {}'.format(total_params))
    #
    #
    if torch.cuda.is_available():
        model = model.cuda()

    cur_time = datetime.datetime.now()
    model_save_path = os.path.join('../model', cur_time.strftime("%Y_%m_%d_%H_%M_%S"))
    os.makedirs(model_save_path)
    # model_save_path = None
    train(model, model_save_path=model_save_path)



if __name__ == '__main__':



    run()
    print(args)
