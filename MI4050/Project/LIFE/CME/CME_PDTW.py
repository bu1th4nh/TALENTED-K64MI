import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib
import os
import ot
from dtaidistance import dtw


matplotlib.use('Agg')

id_list = os.listdir('../data/json/split')
content = []
for id in id_list:
    content.append(open('../data/json/split/'+id).readline())

p_list = [0, 0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 0.5, 1.0, 10, 100]
# p_list = [0]

if not os.path.exists('figures/PDTW'):
    os.makedirs('figures/PDTW')

if not os.path.exists('matrix'):
    os.makedirs('matrix')

p_list = [0, 0.0001, 0.001, 0.01, 0.1, 0.5, 1.0, 10, 100]
for epoch in range(len(p_list)):
    df_null = None
    df_dtw = None
    df_dtw_f = None
    # penalty = 0.003
    # penalty = min(penalty * 2, penalty+ 0.1)
    penalty = p_list[epoch]
    print('p:{}'.format(penalty))
    w = None
    length = 48
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
        # distance = dtw.distance_matrix_fast(df_values.to_numpy().astype(float))
        df_values.fillna(0, inplace=True)
        distance = dtw.distance_matrix_fast(df_values.to_numpy().astype(float).swapaxes(1,0))
        # distance_f = dtw.distance_matrix_fast(df_forward.to_numpy().astype(float).swapaxes(1,0))

        num = df_mask.sum()
        # miss_num = (df_deltas-1).sum()
        miss_num = (df_deltas * (1-df_mask)).sum()
        miss_num = np.tile(miss_num, (35,1))
        penalty_matrix = miss_num + miss_num.transpose()


        distance += penalty_matrix * penalty
        # distance_f += penalty_matrix * penalty

        num = np.tile(num, (35,1))
        w_matrix = (num + num.transpose())/(2*length)

        # df_dtw += distance
        # df_values = df_values[df_mask == 1]
        # corr = df_values.corr(method='pearson', min_periods=2)
        if df_dtw is not None:
            df_dtw += distance * w_matrix
            # df_dtw_f += distance_f * w_matrix
            w += w_matrix
        else:
            df_dtw = distance * w_matrix
            # df_dtw_f = distance_f * w_matrix
            w = w_matrix
        #
        # if df_null is not None:
        #     df_null += 1-corr.isnull().astype('int64')
        # else:
        #     df_null = 1 - corr.isnull().astype('int64')
    inf_idx = np.isinf(df_dtw)
    df_dtw[inf_idx] = 0
    nan_idx = np.isnan(df_dtw)
    df_dtw[nan_idx] = 0

    df_dtw = df_dtw/(w+1e-5)

    df_dtw += df_dtw.transpose()
    df_dtw[np.where(np.eye(df_dtw.shape[0],dtype=bool))] += np.min(df_dtw[np.where(~np.eye(df_dtw.shape[0],dtype=bool))])



    def normalization(data):
        _range = np.max(data) - np.min(data)
        return (data - np.min(data)) / _range


    # plt.figure()
    # sns.heatmap(abs(w), cmap='Reds')
    # plt.close()

    # df_dtw_exp = normalization(np.exp(-df_dtw))
    # plt.figure()
    # sns.heatmap(abs(df_dtw_exp), cmap='Reds')
    # plt.savefig('../../../docs/figures/LPDTW/simple/p_'+str(penalty)+'.png')
    # plt.close()

    df_dtw_inv = normalization(1/df_dtw)
    column_names = [i for i in range(1,36)]
    df_dtw_inv = pd.DataFrame(df_dtw_inv, columns=column_names, index=column_names)
    plt.figure()
    sns.heatmap(abs(df_dtw_inv), cmap='Reds')


    # plt.savefig('../../../docs/figures/POT/p_inv_' + str(penalty) + '.eps', format='eps', dpi=300, bbox_inches='tight')
    plt.savefig('figures/PDTW/p_' + str(penalty) + '.png', format='png', bbox_inches='tight')
    plt.close()

    # np.savetxt('../data/POT_exp_' + str(penalty) + '.csv', df_ot_exp.to_numpy(), delimiter=',')
    np.savetxt('matrix/PDTW_' + str(penalty) + '.csv', df_dtw_inv.to_numpy(), delimiter=',')


print('Done! Figures are saved to \'{}\', Correlation Matrices are saved to \'{}\''.format('figures/PDTW/','matrix/'))