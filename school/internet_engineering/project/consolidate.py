# Brian Behnke
# 12/2/2022
# Internet Engineering - CS-45231
#
# Script to randomly select data entries from the CICDDoS2019 dataset
# and stores them in a single .csv file. This is mainly so I can train 
# models involving all types of DDoS attacks without my 16GB of RAM exploding.

from sklearn.model_selection import train_test_split

import pandas as pd
import numpy as np
import os

def main():
    path = 'data/'
    for root, dirs, files in os.walk(path):
        for file in files:
            tmp = pd.read_csv(os.path.join(path, file))
            tmp.replace(np.inf, np.nan, inplace=True)
            tmp.dropna(axis=0, inplace=True)

            tmp_x = tmp.drop([' Label'], axis=1)
            tmp_y = tmp[' Label']

            x_train, x_test, y_train, y_test = train_test_split(tmp_x, tmp_y, test_size=0.025)

            tmp = pd.concat([x_test, y_test], axis=1)
            tmp.to_csv(os.path.join(path, 'CICDDoS2019_Consolidated.csv'), mode='a')


if __name__ == '__main__':
    main()