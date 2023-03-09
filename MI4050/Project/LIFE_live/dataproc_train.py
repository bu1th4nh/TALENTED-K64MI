# /*==========================================================================================*\
# **                        _           _ _   _     _  _         _                            **
# **                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
# **                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
# **                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
# **                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
# \*==========================================================================================*/


# Author: Bùi Tiến Thành (@bu1th4nh)
# Date: 2022/12/26 14:13 
# CTTN Toán tin K64

from tqdm import tqdm
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
import warnings
warnings.filterwarnings('ignore')
# %matplotlib inline
import os
import re
import ujson as json
import os
import ot
# import pandas_profiling as pp
from dtaidistance import dtw
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--T', type=int, default=128)
args = parser.parse_args()


# Figure size
height = 20
width  = 8
D = 10



n_steps = args.T
df    = pd.read_parquet("../DataWater_train_cleansed_phase3.parquet")
Ariel = df[:int(len(df)//5*4)].copy()
Belle = df[int(len(df)//5*4):].copy()

save_paths = ['data/json/split-train', 'data/json/split-test']
if not os.path.exists(save_paths[0]):
    os.makedirs(save_paths[0])
if not os.path.exists(save_paths[1]):
    os.makedirs(save_paths[1])



def normize(df):
    mean = df.describe().loc["mean", :].to_numpy()
    std  = df.describe().loc["std", :].to_numpy()
    for i in range(len(df.columns)):
        df.iloc[:, i] = (df.iloc[:, i] - mean[i]) / std[i]
    return (df, mean, std)

def build_delta(start):
    delta = np.zeros((n_steps, D))
    for i in range(1, n_steps):
        delta[i] = np.ones(D) + (np.ones(D).astype('int') - mask.iloc[start + i - 1, :].astype('int')) * delta[i - 1]
    return delta

    

def parse_rec(values, masks, deltas):

    assert np.any(pd.isnull(values)) == False
    assert np.any(pd.isnull(masks)) == False
    assert np.any(pd.isnull(deltas)) == False

    # only used in GRU-D
    forwards = pd.DataFrame(values).fillna(method='ffill').fillna(0.0).iloc[:,:].values

    rec = {}

    rec['values'] = np.nan_to_num(values).tolist()
    rec['masks'] = masks.astype('int32').tolist()
    rec['forwards'] = forwards.tolist()
    rec['deltas'] = deltas.tolist()

    return rec


for idxfp, save_path in enumerate(save_paths):
    dataaaaaa = Ariel if idxfp == 0 else Belle

    idx_list = []
    T        = len(dataaaaaa)
    mask     = ~pd.isnull(dataaaaaa)
    dataaaaaa.reset_index(drop=True, inplace=True)


    for i in tqdm(range(n_steps, T), desc="Building sample index list for {0}".format("train" if idxfp == 0 else "test")):
        idx_list.append((i - n_steps, i))
    print("Initial size:", len(idx_list))


    true_size = 0;
    for i, (start, end) in enumerate(tqdm(idx_list, desc='Building JSON train' if idxfp == 0 else 'Building JSON test')):
        values, mean, std = normize(dataaaaaa.iloc[start:end].copy())

        values = values.fillna(0).to_numpy()
        delta  = build_delta(start)
        mask_  = mask.iloc[start:end].to_numpy()
        label  = (dataaaaaa.loc[end].to_numpy() - mean) / (std + 1e-8);

        if np.any(pd.isnull(label)): continue;
        true_size += 1

        rec = {'label': label.tolist()}
        rec['forward']  = parse_rec(values, mask_, delta)
        rec['backward'] = parse_rec(values, mask_, delta)
        rec = json.dumps(rec)

        save_file = os.path.join(save_path, str(i))
        with open(save_file,'w') as f:
            f.write(rec)
    print("True size: {0}".format(true_size))