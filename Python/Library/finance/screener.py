import numpy as np
import scipy.stats as st
import computing.data_structures as ds
import statistics.time_series as ts
import statistics.model as mod
import statistics.data_analysis as da
import statistics.random_variable as ranv
import finance.technical as tech
import finance.simfin as sf

api_key = 'lSQLTX1xqdQcFK6smyOA7aOcaHLH5VWq'
connection = sf.Connection(api_key)

class Screener:
    """basically just a list of symbols in the same industry:
    takes a list of tickers... uses log prices"""
    def __init__(self, tickers, start_date, end_date=None):
        """start,end in YYYY-MM-DD format, """
        assert isinstance(tickers, list)
        self._ticker_data = self.get_ticker_data(tickers, start_date, end_date)
        self._tickers = list(self.ticker_data.keys())
        self._start_date = start_date
        self._end_date = end_date
        self._size = len(self.tickers)
        self._encoding_dict = {i: self.tickers[i] for i in range(self.size)}
        self._id_dict = self.get_id_dict()
        self._series_dict = self.get_series_dict()
        self._series_length = self.series_dict[self.tickers[0]].size

    @property
    def ticker_data(self):
        return self._ticker_data

    @property
    def tickers(self):
        return self._tickers

    @property
    def start_date(self):
        return self._start_date

    @property
    def end_date(self):
        return self._end_date

    @property
    def size(self):
        return self._size

    @property
    def encoding_dict(self):
        return self._encoding_dict

    @property
    def id_dict(self):
        return self._id_dict

    @property
    def series_dict(self):
        return self._series_dict

    @property
    def series_length(self):
        return self._series_length

    def get_ticker_data(self, tickers, start_date, end_date):
        ticker_data = dict()

        for ticker in tickers:
            ticker_id = connection.get_id(ticker)
            if ticker_id is None:
                continue
            ticker_series = connection.get_series(ticker_id, start_date, end_date)
            if ticker_series is None:
                continue
            ticker_data[ticker] = {'ticker_id': ticker_id, 'ticker_series': ticker_series}
        return ticker_data

    def get_id_dict(self):
        id_dict = dict()

        for ticker in self.tickers:
            id_dict[ticker] = self.ticker_data[ticker]['ticker_id']
        return id_dict

    def get_series_dict(self):
        series_dict = dict()

        for ticker in self.tickers:
            ticker_series = self.ticker_data[ticker]['ticker_series']
            ticker_series = np.log(ticker_series)
            series_dict[ticker] = ticker_series

        return series_dict

    def adj_mat(self):
        """entries can be zero if uncorrelated or not I(1)"""
        adj_mat = np.zeros((self.size, self.size))
        for i in range(self.size):
            for j in range(self.size):
                if i < j:
                    vals = ts.coint_data(self.series_dict[self.encoding_dict[i]],
                    self.series_dict[self.encoding_dict[j]])
                    if vals != None:
                        if vals[0] <= .00001:
                            adj_mat[i][j] = 1
                            adj_mat[j][i] = 1
        return adj_mat

    def graph(self, adj_mat):
        return ds.Graph(adj_mat=adj_mat)

    def trend_dict(self):
        """returns the tickers that have a statistically significant
        linear trend of the logprices (using AR(1) stochastic
        trend model)"""

        trend_dict = dict()
        for ticker in self.tickers:
            series = self.series_dict[ticker]
            trend = ts.trend(series)
            if trend is not None:
                trend_dict[ticker] = trend
        return trend_dict

    def geometric_dict(self, trend_dict, horizon=20):
        geo_dict = dict()
        bin_num = np.int(np.floor(self.series_length/2.3))
        for ticker in trend_dict.keys():
            if trend_dict[ticker] > 0:
                differenced = ts.diff(self.series_dict[ticker])

                #for distributions
                args = [differenced.values, bin_num]
                best_fit = da.fit_data(*args)
                dist = best_fit[0]
                params = best_fit[1]
                dist_args = params[:-2]
                loc = params[-2]
                scale = params[-1]

                #for geomeric motion
                avg = np.average(differenced.values)
                sigma = np.std(differenced.values, ddof=1)
                mu = avg + sigma**2

                class rv(st.rv_continuous):
                    def _pdf(self,x):
                        return ranv.normalize_pdf(dist.pdf(x, *dist_args, loc=loc, scale=scale))

                function = mod.geometric_motion
                args = [rv, horizon, self.series_dict[ticker].values[0], mu, sigma]
                predicted_vals = mod.monte_carlo(function, 1000, *args)
                geo_dict[ticker] = {'avg': np.average(predicted_vals), 'std': np.std(predicted_vals, ddof=1)}

        return geo_dict

    def extreme_val_dict(self, trend_dict, moving_length, threshold):
        ext_vals = dict()
        for equity in trend_dict.keys():
            if trend_dict[equity] != 0:
                series = self.series_dict[equity]
                args = [series, np.std, moving_length, 2, True]
                [low, high] = tech.bands(*args)

                if series[-1] <= low + np.multiply(threshold, series[-1]):
                    ext_vals[equity] = 'low'
                elif series[-1] >= high - np.multiply(threshold, series[-1]):
                    ext_vals[equity] = 'high'

        return ext_vals
