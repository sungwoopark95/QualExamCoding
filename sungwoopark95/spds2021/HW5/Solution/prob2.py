import random
import numpy as np

class FTNetwork(object):
    def __init__(self, sizes):
        np.seterr(all='ignore')
        self.rng = np.random.RandomState(2021)
        self.num_layers = len(sizes)
        self.sizes = sizes
        self.biases = [self.rng.randn(y, 1) for y in sizes[1:]]
        self.weights = [self.rng.randn(y, x)
                        for x, y in zip(sizes[:-1], sizes[1:])]
      
    def feedforward(self, a):
        # applies a = sigma(wa + b)
        for b, w in zip(self.biases, self.weights):
            a = sigmoid(np.dot(w, a)+b)
        return a

    def SGD(self, training_data, epochs, mini_batch_size, lr, test_data=None, tuning=False):
        # training_data is a list of tuples(x,y) representing the training inputs and
            # corresponding desired outputs.
        # epochs = number of epochs to train for
        # mini_batch_size = size of mini-batches to use when sampling
        # lr = eta is learning rate
        # when test_data is supplied, then the program will evaluate the network after each
            # of the traiing and print out partial progress - useful for tracking progress (but slow)
        
        if test_data: n_test = len(test_data)
        n = len(training_data)
        for j in range(epochs):
            # first randomly shuffle training data
            self.rng.shuffle(training_data)
            #partition training data into mini-batches of the appropriate size
            mini_batches = [
                training_data[k:k+mini_batch_size]
                for k in range(0, n, mini_batch_size)]
            # For each mini-batch, apply a single step of gradient descent
            for mini_batch in mini_batches:
                # the code will update the network weights and biases according to a single iteration
                # of graident descent
                self.update_mini_batch(mini_batch, lr, tuning)
            if test_data:
                print("Epoch {0}: {1} / {2}".format(
                    j, self.evaluate(test_data), n_test))
            else:
                print("Epoch {0} complete".format(j))

    def update_mini_batch(self, mini_batch, lr, tuning=False):
    # TODO: Implement here
    #pass
    # I have used code from Michael Nielsen
        """Update the network's weights and biases by applying
        gradient descent using backpropagation to a single mini batch.
        The ``mini_batch`` is a list of tuples ``(x, y)``, and ``eta``
        is the learning rate."""
        # first initialize nabla values for b and w to be 0
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        # for each mini batch
        for x, y in mini_batch:
            # apply backpropagation algorithm to compute the gradient of cost function
            delta_nabla_b, delta_nabla_w = self.backprop(x, y, tuning)
            # update the values according to back propogation
            nabla_b = [nb+dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]
            nabla_w = [nw+dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
        # update weights and biases
        self.weights = [w-(lr/len(mini_batch))*nw 
                        for w, nw in zip(self.weights, nabla_w)]
        self.biases = [b-(lr/len(mini_batch))*nb 
                       for b, nb in zip(self.biases, nabla_b)]
    
    def backprop(self, x, y, tuning):
        """Return a tuple ``(nabla_b, nabla_w)`` representing the
        gradient for the cost function C_x.  ``nabla_b`` and
        ``nabla_w`` are layer-by-layer lists of numpy arrays, similar
        to ``self.biases`` and ``self.weights``."""
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        # feedforward
        activation = x
        activations = [x] # list to store all the activations, layer by layer
        zs = [] # list to store all the z vectors, layer by layer
        for b, w in zip(self.biases, self.weights):
            z = np.dot(w, activation)+b
            zs.append(z)
            activation = sigmoid(z)
            activations.append(activation)
        # backward pass
        # start from the back
        
        # The first term self.cost_derivative(activations[-1], y) measures
            # how fast the cost is changing as function of the output activation
        # The second term sigmoid_prime(zs[-1]) comes from sum of all nuerons k in output layer
            # where we have sum of k of da_k^L/ dz_j^L
            # because it only depends on case when k = j, this simplifies to
            # da_j^L/ dz_j^L
            # because a_j^L = sigma(z_j^L), it become sigmoid_prime(z_j^L)
        delta = self.cost_derivative(activations[-1], y) * \
            sigmoid_prime(zs[-1])
        nabla_b[-1] = delta
        # This looks complicated, but there is an simple explanation
            # since we know delta and activations, the transpose of weight matrix is applied
            # because we can think it as moving error backward through network
            # giving idea of measure of error at output layer 
            # (here he expects column vector so that is why transpose is applied)
        nabla_w[-1] = np.dot(delta, activations[-2].transpose())
        
        # Because last layer is finished, if tuning will end here
        if tuning:
            return (nabla_b, nabla_w)
        else:
            # Note that the variable l in the loop below is used a little
            # differently to the notation in Chapter 2 of the book.  Here,
            # l = 1 means the last layer of neurons, l = 2 is the
            # second-last layer, and so on.  It's a renumbering of the
            # scheme in the book, used here to take advantage of the fact
            # that Python can use negative indices in lists.

            for l in range(2, self.num_layers):
                z = zs[-l]
                sp = sigmoid_prime(z)
                delta = np.dot(self.weights[-l+1].transpose(), delta) * sp
                nabla_b[-l] = delta
                nabla_w[-l] = np.dot(delta, activations[-l-1].transpose())
            return (nabla_b, nabla_w)
  
    def evaluate(self, test_data):
        test_results = [(np.argmax(self.feedforward(x)), y)
                        for (x, y) in test_data]
        return sum(int(x == y) for (x, y) in test_results)

    def cost_derivative(self, output_activations, y):
        return (output_activations-y)

def sigmoid(z):
    return 1.0/(1.0+np.exp(-z))

def sigmoid_prime(z):
    return sigmoid(z)*(1-sigmoid(z))

