import numpy as np
import scipy.stats as st

def convolve(rv1, rv2, discrete=True):
    """return convolved rv"""
    if discrete == True:
        supp = list(range(rv1.a, rv1.b+1))

        xk = list(range(rv1.a + rv2.a, rv1.b + rv2.b + 1))
        pk = list(map(lambda z: sum(list(map(lambda k: rv1.pmf(k)*rv2.pmf(z-k), supp))), xk))
        conv_rv = st.rv_discrete(values=(xk, pk))
        return conv_rv

def scale(rv, scalar, discrete=True):
    if discrete == True:
        supp = np.arange(rv.a, rv.b+1)
        xk = scalar*supp
        pk = np.array(list(map(lambda k: rv.pmf(k), supp)))
        scaled_rv = st.rv_discrete(values=(xk, pk))
        return scaled_rv

def prob_val(rv, *args, loc, scale, x):
    """given a random variable rv with parameters (*args, loc, scale) and value x,
    returns the probability of receiving a number more extreme than x (one sided)"""
    cdf_val = rv.cdf(x, *args, loc, scale)
    if cdf_val <= .5:
        return cdf_val
    elif cdf_val > .5:
        return 1 - cdf_val

def normalize_pdf(pdf, mu, sigma):
    """takes a pdf that is fitted to some data and
    transforms it to have mean zero and variance one.
    Here, mu is the mean of the distribution and sigma the std deviation"""
    def new_pdf(x):
        return sigma*pdf(x*sigma + mu)

    return new_pdf
