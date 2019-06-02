import numpy as np
import pandas as pd
import torch
from torch.utils.data.dataset import Dataset

class Train_Set(Dataset):

    def __init__(self, train_data, train_labels):
        """When labels are retrieved, they are retrieved
        as one hot encoded tensorsself.

        train_data: pandas DataFrame of train data
        train_labels: pandas DataFrame of train labels
        """

        self.train_data = train_data
        self.train_labels = train_labels
        self.data_arr = self.train_data.values
        self.label_arr = self.train_labels.values
        self.enc_label_arr = pd.get_dummies(self.train_labels).values

    def __getitem__(self, index):
        sample = torch.Tensor(self.data_arr[index])
        enc_label = torch.Tensor(self.enc_label_arr[index])

        return (sample, enc_label)

    def __len__(self):
        return len(self.data_arr)

class Test_Set(Dataset):
    """When labels are retrieved, they are retrieved
    as one hot encoded tensors

    test_data: pandas DataFrame of test data
    test_labels: pandas DataFrame of test labels"""

    def __init__(self, test_data, test_labels):

        self.test_data = test_data
        self.test_labels = test_labels
        self.data_arr = self.test_data.values
        self.label_arr = self.test_labels.values
        self.enc_label_arr = pd.get_dummies(self.test_labels).values

    def __getitem__(self, index):
        sample = torch.Tensor(self.data_arr[index])
        enc_label = torch.Tensor(self.enc_label_arr[index])

        return (sample, enc_label)

    def __len__(self):
        return len(self.data_arr)
