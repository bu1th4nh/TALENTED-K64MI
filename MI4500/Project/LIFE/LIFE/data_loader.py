import os
import time

import ujson as json
import numpy as np
import pandas as pd

import torch
import torch.nn as nn
from torch.utils.data import Dataset, DataLoader
from sklearn.model_selection import train_test_split
from sklearn.model_selection import KFold


class SplitSet(Dataset):
    def __init__(self, path, id_list):
        super(SplitSet, self).__init__()
        self.path = path
        self.id_list = id_list

    def __len__(self):
        return len(self.id_list)

    def __getitem__(self, idx):
        id = self.id_list[idx]
        with open(os.path.join(self.path, id)) as f:
            rec = json.load(f)
        return rec



def collate_fn(recs):
    forward = list(map(lambda x: x['forward'], recs))
    backward = list(map(lambda x: x['backward'], recs))

    def to_tensor_dict(recs):
        values = torch.FloatTensor(list(map(lambda r: r['values'], recs)))
        masks = torch.FloatTensor(list(map(lambda r: r['masks'], recs)))
        deltas = torch.FloatTensor(list(map(lambda r: r['deltas'], recs)))

        forwards = torch.FloatTensor(list(map(lambda r: r['forwards'], recs)))

        return {'values': values, 'forwards': forwards, 'masks': masks, 'deltas': deltas}

    ret_dict = {'forward': to_tensor_dict(forward), 'backward': to_tensor_dict(backward)}

    ret_dict['labels'] = torch.FloatTensor(list(map(lambda x: x['label'], recs)))

    return ret_dict


def get_loader(data_path, batch_size=64, shuffle=True):
    id_list = np.sort(os.listdir(data_path))
    train_ids, test_ids = train_test_split(id_list, test_size=0.2, random_state=0)


    train_set = SplitSet(path=data_path, id_list=train_ids)
    test_set = SplitSet(path=data_path, id_list=test_ids)

    train_iter = DataLoader(dataset=train_set, \
                            batch_size=batch_size, \
                            num_workers=4, \
                            shuffle=shuffle, \
                            pin_memory=True, \
                            collate_fn=collate_fn
                            )

    test_iter = DataLoader(dataset=test_set, \
                           batch_size=batch_size, \
                           num_workers=4, \
                           shuffle=shuffle, \
                           pin_memory=True, \
                           collate_fn=collate_fn
                           )

    return train_iter, test_iter

