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

df = pd.read_parquet("../DataWater_train_cleansed_phase3.parquet")

# Ariel = df[:int(len(df)//5*4)]
Belle = df[int(len(df)//5*4):].copy()

D = 10
T = len(Belle)

def normize(df):
    mean = df.describe().loc["mean", :].to_numpy()
    std  = df.describe().loc["std", :].to_numpy()
    for i in range(len(df.columns)):
        df.iloc[:, i] = (df.iloc[:, i] - mean[i]) / std[i]
    return (df, mean, std)


mask = ~pd.isnull(Belle)
print(mask.head(5))
# pp.ProfileReport(Ariel)


n_steps = args.T

def build_delta(start):
    delta = np.zeros((n_steps, D))
    for i in range(1, n_steps):
        delta[i] = np.ones(D) + (np.ones(D).astype('int') - mask.iloc[start + i - 1, :].astype('int')) * delta[i - 1]
    return delta



idx_list = []
start = 0;
end = 0;

for i in tqdm(range(n_steps, T), desc="Building sample index list"):
    if(not np.any(pd.isnull(Belle.iloc[i, :]))): 
        idx_list.append((i - n_steps, i))


print(len(idx_list))


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



save_path = 'data/json/split-train'
if not os.path.exists(save_path):
    os.makedirs(save_path)
for i, (start, end) in enumerate(tqdm(idx_list, desc='Building JSON')):

    Belle.fillna(0, inplace=True);
    values, mean, std = normize(Belle.iloc[start:end].copy())
    
    values = values.fillna(0).to_numpy()
    delta  = build_delta(start)
    mask_  = mask.iloc[start:end].to_numpy()
    label  = (Belle.iloc[end].to_numpy() - mean) / std;

    rec = {'label': label.tolist()}
    rec['forward']  = parse_rec(values, mask_, delta)
    rec['backward'] = parse_rec(values, mask_, delta)
    rec = json.dumps(rec)

    save_file = os.path.join(save_path, str(i))
    with open(save_file,'w') as f:
        f.write(rec)