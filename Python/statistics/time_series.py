import numpy as np
import pandas as pd
import statsmodels.api as sm
import statsmodels.stats.weightstats as wst
from statsmodels.tsa.stattools import adfuller

def diff(series):
    diff = series.copy()
    for i in range(1, diff.size):
        diff.iloc[i] = series.iloc[i] - series.iloc[i-1]
    diff = diff.drop(diff.index[0])
    return diff

def is_stationary(series):
    if adfuller(series.values, regression='nc')[1] <= .0000001:
        return True
    else:
        return False

def ord_int(series):
    try:
        ts = series
        i = 0
        while True:
            if is_stationary(ts):
                break
            i = i+1
            ts = diff(ts)
        return i
    except:
        return None

def coint_data(ser1, ser2):
    """given two I(1) times series, returns the p value for cointegration
    (small p -> cointegrated), the optimized coeffcient beta such that
    self - beta*other is stationary, the time series given by
    self - beta*other, the estimate for the mean of the self - beta*other
    and the rmse estimate for the standard deviation of
    self - beta*other in a list in the given order"""
    assert isinstance(ser1, pd.Series) and isinstance(ser2, pd.Series)
    if ord_int(ser1) <= 1 and ord_int(ser2) <= 1:
        y = ser1.values
        x = ser2.values
        x = sm.add_constant(x)
        model = sm.OLS(y,x)
        results = model.fit()
        beta0 = results.params[0]
        beta1 = results.params[1]
        s = np.sqrt(results.mse_resid)
        res = results.resid
        p_val = adfuller(np.add(res, beta0), regression='nc')[1]
        series = pd.Series(np.add(res, beta0), index=ser1.index)
        return [p_val, beta1, series, beta0, s]
    else:
        return None

def moving(series, function, moving_length, final=False):
    """given a function that acts on arrays and a specificed array length,
    returns a rolling time series of that function over that length, 
    final=False gives all the data and final=True skips all the computation 
    and computes just for the last data point"""
    assert moving_length < series.size
    size = series.size
    if final == False:
        vals = np.zeros((size,))
        vals[:moving_length] = np.nan
        for i in range(moving_length, size):
            vals[i] = function(series.values[i-moving_length:i])
        return pd.Series(vals, index=series.index)
    else:
        return function(series.values[size-moving_length:size])

def trend(series):
    """find a linear trend in an AR(1) stochastic trend stationary model"""
    if is_stationary(series) == True:
        return 0
    else:
        first_diff = diff(series)
        if is_stationary(first_diff) == False:
            return None
        else:
            data = first_diff.values
            mu = np.average(data)
            pval = wst.ztest(data, value=0)[1]

            if pval <= .1:
                return mu
            else:
                return 0
