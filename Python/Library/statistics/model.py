import numpy as np
import scipy.stats as st

def geometric_motion(rv, horizon, S_0, mu, sigma):
    """here mu-sigma**2 is the expected value
    of the differences S_{t} - S_{t-1} and not mu"""
    rvs = rv.rvs(size=horizon)
    process = np.cumsum(rvs)
    value = S_0*np.exp((mu-(sigma**2)/2)*horizon + sigma*process[-1])

    return value

def monte_carlo(random_function, simulations, *args):

    vals = np.zeros((simulations))

    for i in range(simulations):
        vals[i] = random_function(*args)

    return vals
