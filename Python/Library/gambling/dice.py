import numpy as np
import scipy.stats as st
import statistics.random_variable as ranv

class Die:
    def __init__(self, num_sides):
        self._num_sides = num_sides
        n = self.num_sides
        self.rv = st.rv_discrete(values=(np.arange(1, n+1), np.array([1/n]*n)))

    @property
    def num_sides(self):
        return self._num_sides

def sum(dice_list):
    """give list of dice, returns the random variable
    of the sum of the faces of the dice when rolled"""
    assert all([isinstance(die, Die) for die in dice_list])
    rvs = []
    for die in dice_list:
        n = die.num_sides
        xk = np.arange(1, n+1)
        pk = np.array([1/n]*n)
        rv = st.rv_discrete(values=(xk, pk))
        rvs.append(rv)

    sum = rvs[0]
    for rv in rvs[1:]:
        sum = ranv.convolve(sum, rv)

    return sum
