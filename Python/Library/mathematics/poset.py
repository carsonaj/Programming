from abc import ABC, abstractmethod
import data_stucutres as ds

class Poset(ds.Graph):
    def __init__(self, adj_mat):
            super().init(adj_mat)
