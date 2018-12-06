import requests
import numpy as np
import pandas as pd

class Connection:

    def __init__(self, api_key):
        self._api_key = api_key

    @property
    def api_key(self):
        return self._api_key

    def get_id(self, ticker):
        id_url = 'https://simfin.com/api/v1/info/find-id/ticker/' + ticker + '?api-key=' + self.api_key
        parameters = {'api-key': self.api_key}
        id_response = requests.get(id_url, params=parameters)
        assert id_response.status_code == 200
        id_list = id_response.json()
        if type(id_list) is not list:
            return None
        
        elif len(id_list) == 0:
            return None
        else: 
            id_dict = id_response.json()[0]
            if 'simId' not in id_dict.keys():
                return None
            else: 
                id_num = id_dict['simId']
            return id_num
        
    def get_series(self, id_num, start, end=None):
        """start/stop in format YYYY-MM-DD"""
        price_url = 'https://simfin.com/api/v1/companies/id/' + str(id) + '/shares/prices'
        if end is None:
            parameters = {'api-key': self.api_key, 'start': start}
        else: 
            parameters = {'api-key': self.api_key, 'start': start, 'end': end}
        price_response = requests.get(price_url, parameters)
        assert price_response.status_code == 200
        price_json = price_response.json()
        
        if 'priceData' not in price_json.keys():
            return None
        else: 
            price_list = price_json['priceData']
            length = len(price_list)
            prices = []
            dates = []
        
            for i in range(length-1,-1,-1):
                prices.append(price_list[i]['closeAdj'])
                dates.append(price_list[i]['date'])
            
            dates = pd.DatetimeIndex(dates)
            prices = np.array(prices, dtype='float64')
            series = pd.Series(data=prices, index=dates)
            series.dropna(inplace=True)
        
        return series