import torch

def encoding_function(num_categories):
    """one hot encoder, given the number of categories returns a one-hot 
    encoder function the eats tensors of size (N,1) (where N is batch size 
    and each row corresonds to one numerical value) and spits out a 
    tensors of size (N,num_categories) where each row corresponds to 
    the one hot encoding associated to the numerical value"""

    def encoder(vals):
        """vals of size (N,1), each row is a one value in 
        [0,num_categories-1]"""
        batch_size = vals.size(0)
        encoded_vals = torch.zeros((batch_size, num_categories))
        
        for i in range(batch_size):
            val = vals[i].item()
            encoded_vals[i][val] = 1
            
        return encoded_vals
        
    return encoder 
        
class NN(torch.nn.Module):
    
    def __init__(self, linear_args, activation_functions, softmax=False):
        """layer_shapes is a list, activation_functions is a ModuleList 
        of activation functions (not including softmax)"""
        super(NN, self).__init__()
        assert len(activation_functions) == len(linear_args) - 1
        k = len(linear_args)
        assert all([linear_args[j][1] == linear_args[j+1][0] for j in range(k-1)])
        self.linears = torch.nn.ModuleList([torch.nn.Linear(*arg) for arg in linear_args])
        self.activation_functions = activation_functions
        self.softmax = softmax

    def forward(self, x):
        y = x
        k = len(self.linears)
        for j in range(k-1):
            linear = self.linears[j]
            actv = self.activation_functions[j]
            y = actv(linear(y))
            
        y = self.linears[-1](y)
        
        if self.softmax == True:
            sm = torch.nn.Softmax(dim=1)
            y = sm(y)
    
        return y
    #softmax at end mandatory?
    
class CNN2d(torch.nn.Module):
    
    def __init__(self, convolution_args, pool_args, linear_args, 
                 activation_functions, softmax=False):
        """convolution_args, pool_Args, linear_args are lists of *args for the 
        Conv2d, MaxPool, and Linear modules respectively and activation_functions is 
        a ModuleList of activation functions (not including softmax)"""
        super(CNN2d, self).__init__()
        assert len(convolution_args) == len(pool_args)
        
        l = len(convolution_args)
        assert all([convolution_args[j][1] == convolution_args[j+1][0]
                   for j in range(l-1)])
        self.convolutions = torch.nn.ModuleList([torch.nn.Conv2d(*arg) 
                            for arg in convolution_args])
        self.pools = torch.nn.ModuleList([torch.nn.MaxPool2d(*arg) 
                            for arg in pool_args])
        
        k = len(linear_args)
        assert all([linear_args[j][1] == linear_args[j+1][0] for j 
                                         in range(k-1)]) 
        assert len(activation_functions) == len(linear_args) - 1
        self.linears = torch.nn.ModuleList([torch.nn.Linear(*arg) 
                       for arg in linear_args])
        self.activation_functions = activation_functions
        self.softmax = softmax
        
        
    def forward(self, x):
        y = x
        n = len(self.convolutions)
        l = len(self.linears)
        relu = torch.nn.ReLU()
        dropout = torch.nn.Dropout()
        
        for i in range(n):
            conv = self.convolutions[i]
            pool = self.pools[i]
            y = pool(relu(conv(y)))
        
        y = y.reshape(y.size(0),-1)
        y = dropout(y)
        
        for j in range(l-1): 
            linear = self.linears[j]
            actv = self.activation_functions[j]
            y = actv(linear(y))
        
        y = self.linears[-1](y)
        
        if self.softmax == True:
            sm = torch.nn.Softmax(dim=1)
            y = sm(y)
        
        return y
        
        
        
        
        
        
        
        
        