import numpy as np
import scipy.stats as st

def up_dev(values, ddof=0):
    mu = np.average(values)
    up_sigma = 0
    for val in values:
         if val >= mu:
             up_sigma = up_sigma + (val-mu)**2
    up_sigma = up_sigma/(values.size - ddof)
    up_sigma = np.sqrt(up_sigma)

    return up_sigma

def down_dev(values, ddof=0):
    mu = np.average(values)
    down_sigma = 0
    for val in values:
         if val <= mu:
             down_sigma = down_sigma + (val-mu)**2
    down_sigma = down_sigma/(values.size - ddof)
    down_sigma = np.sqrt(down_sigma)

    return down_sigma

def bin_number():
    pass


def fit_data(data, bins):
    y, x = np.histogram(data, bins, density=True)
    x = x[:-1]

    distributions = [st.alpha,st.anglit,st.arcsine,st.beta,st.betaprime,st.bradford,st.burr,st.cauchy,st.chi,st.chi2,st.cosine,
                     st.dgamma,st.dweibull,st.erlang,st.expon,st.exponnorm,st.exponweib,st.exponpow,st.f,st.fatiguelife,st.fisk,
                     st.foldcauchy,st.foldnorm,st.frechet_r,st.frechet_l,st.genlogistic,st.genpareto,st.gennorm,st.genexpon,
                     st.genextreme,st.gausshyper,st.gamma,st.gengamma,st.genhalflogistic,st.gilbrat,st.gompertz,st.gumbel_r,
                     st.gumbel_l,st.halfcauchy,st.halflogistic,st.halfnorm,st.halfgennorm,st.hypsecant,st.invgamma,st.invgauss,
                     st.invweibull,st.johnsonsb,st.johnsonsu,st.ksone,st.kstwobign,st.laplace,st.levy,st.levy_l,st.levy_stable,
                     st.logistic,st.loggamma,st.loglaplace,st.lognorm,st.lomax,st.maxwell,st.mielke,st.nakagami,st.ncx2,st.ncf,
                     st.nct,st.norm,st.pareto,st.pearson3,st.powerlaw,st.powerlognorm,st.powernorm,st.rdist,st.reciprocal,
                     st.rayleigh,st.rice,st.recipinvgauss,st.semicircular,st.t,st.triang,st.truncexpon,st.truncnorm,st.tukeylambda,
                     st.uniform,st.vonmises,st.vonmises_line,st.wald,st.weibull_min,st.weibull_max,st.wrapcauchy]

    best_distribution = st.norm
    best_params = (0.0, 1.0)
    best_sse = np.inf

    for distribution in distributions:
        try:
            # fit dist to data
            params = distribution.fit(data)

            # Separate parts of parameters
            args = params[:-2]
            loc = params[-2]
            scale = params[-1]

            # Calculate fitted PDF and error with fit in distribution
            pdf = distribution.pdf(x, *args, loc=loc, scale=scale)
            sse = np.sum(np.power(y - pdf, 2.0))

            # identify if this distribution is better
            if best_sse > sse > 0:
                best_distribution = distribution
                best_params = params
                best_sse = sse

        except Exception:
            continue

        return [best_distribution, best_params]

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
