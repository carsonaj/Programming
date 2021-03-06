import requests
import numpy as np
import pandas as pd

class Connection:

    def __init__(self, api_key):
        self._api_key = api_key
        self._api_url = 'https://www.alphavantage.co/query?'

    @property
    def api_key(self):
        return self._api_key

    @property
    def api_url(self):
        return self._api_url

    def daily_series(self, symbol, length=100, price='close'):
        """returns pd.Series object"""
        if length <= 100:
            outputsize = 'compact'
        else:
            outputsize = 'full'
        query_parameters = {'symbol': symbol, 'function': 'TIME_SERIES_DAILY_ADJUSTED',
                            'outputsize': outputsize, 'apikey': self.api_key}
        response = requests.get(self.api_url, params=query_parameters)
        assert response.status_code == 200

        json_data = response.json()
        
        if 'Information' in json_data.keys():
            print('You got ad, try again!')
            print(json_data['Information'])
            return None
        type_dict = {'open': '1. open', 'high': '2. high', 'low': '3. low',
                     'close': '4. close', 'adj_close': '5. adjusted close',
                     'volume': '6. volume'}
        
        dates = pd.DatetimeIndex(list(json_data['Time Series (Daily)'].keys()))
        prices = np.array([json_data['Time Series (Daily)'][x][type_dict[price]]
                          for x in json_data['Time Series (Daily)'].keys()],
                          dtype='float64')

        series = pd.Series(data=prices, index=dates)
        series.drop(series.index[length:], axis=0, inplace=True)
        series.dropna(inplace=True)
        series = series.reindex(index=series.index[::-1])

        return series

    #def daily_quote()
