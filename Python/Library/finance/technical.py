import numpy as np
import pandas as pd
from scipy.stats import rv_continuous
import computing.data_structures as ds
import statistics.time_series as ts

def bands(series, variate_function, moving_length, radius, final=False):
    """given a (usually nonnegative) function that acts on arrays and a specificed array length and radius,
    returns a list of two time series [l,h]: v-original series, l-low series, h-high series"""
    variation = ts.moving(series, variate_function, moving_length, final)
    avg = ts.moving(series, np.average, moving_length, final)
    low = np.subtract(avg, np.multiply(variation, radius))
    high = np.add(avg, np.multiply(variation, radius))

    return [low, high]
