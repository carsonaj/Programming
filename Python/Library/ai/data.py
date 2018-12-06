import numpy as np
import pandas as pd
import torch
from torch.utils.data.dataset import Dataset

class Train_Set(Dataset):

    def __init__(self, file_path):
        """This is for use with data that comes in a csv, not images.
        The csv must have first column as labels and when data is retrieved,
        it is retrieved as a tensor. When labels are retrieved, they are retrieved
        as one hot encoded tensors"""

        self.train_df = pd.read_csv(file_path)
        self.data_arr = self.train_df.iloc[:,1:].values
        self.label_arr = self.train_df.iloc[:,0].values
        self.enc_label_arr = pd.get_dummies(self.train_df.iloc[:,0]).values

    def __getitem__(self, index):
        sample = torch.Tensor(self.data_arr[index])
        enc_label = torch.Tensor(self.enc_label_arr[index])

        return (sample, enc_label)

    def __len__(self):
        return len(self.data_arr)

class Test_Set(Dataset):
    """This is for use with data that comes in a csv, not images.
    The csv must have first column as labels and when data is retrieved,
    it is retrieved as a tensor. When labels are retrieved, they are retrieved
    as one hot encoded tensors"""

    def __init__(self, file_path):

        self.test_df = pd.read_csv(file_path)
        self.data_arr = self.test_df.iloc[:,1:].values
        self.label_arr = self.test_df.iloc[:,0].values
        self.enc_label_arr = pd.get_dummies(self.test_df.iloc[:,0]).values

    def __getitem__(self, index):
        sample = torch.Tensor(self.data_arr[index])
        enc_label = torch.Tensor(self.enc_label_arr[index])

        return (sample, enc_label)

    def __len__(self):
        return len(self.data_arr)
