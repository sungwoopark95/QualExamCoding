import random
import numpy as np

class MomentumNetwork(object):
    def __init__(self, sizes):
        np.seterr(all='ignore')
        self.rng = np.random.RandomState(2021)
        self.num_layers = len(sizes)
        self.sizes = sizes
        self.biases = [self.rng.randn(y, 1) for y in sizes[1:]]
        self.weights = [self.rng.randn(y, x)
                        for x, y in zip(sizes[:-1], sizes[1:])]
        # Add velocities for weight and biases
        self.bias_velocities = [np.zeros((y, 1)) for y in sizes[1:]]
        self.weight_velocities = [np.zeros((y, x))
                        for x, y in zip(sizes[:-1], sizes[1:])]

    def feedforward(self, a):
        # applies a = sigma(wa + b)
        for b, w in zip(self.biases, self.weights):
            a = sigmoid(np.dot(w, a)+b)
        return a

    def SGD(self, training_data, epochs, mini_batch_size, lr, momentum, test_data=None):
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
                self.update_mini_batch(mini_batch, lr, momentum)
            if test_data:
                print("Epoch {0}: {1} / {2}".format(
                    j, self.evaluate(test_data), n_test))
            else:
                print("Epoch {0} complete".format(j))

    def update_mini_batch(self, mini_batch, lr, momentum):
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        for x, y in mini_batch:
            delta_nabla_b, delta_nabla_w = self.backprop(x, y)
            nabla_b = [nb+dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]
            nabla_w = [nw+dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
        
        # Update velocities using momentum
        self.bias_velocities = [momentum * v + lr * nb for v, nb in zip(self.bias_velocities, nabla_b)]
        self.weight_velocities = [momentum * v + lr * nw for v, nw in zip(self.weight_velocities, nabla_w)]
        
        # Update weights and biases using velocities
        self.weights = [w - v for w, v in zip(self.weights, self.weight_velocities)]
        self.biases = [b - v for b, v in zip(self.biases, self.bias_velocities)]

    def backprop(self, x, y):
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        # feedforward
        activation = x
        activations = [x]
        zs = []
        for b, w in zip(self.biases, self.weights):
            z = np.dot(w, activation)+b
            zs.append(z)
            activation = sigmoid(z)
            activations.append(activation)
        # backward pass
        delta = self.cost_derivative(activations[-1], y) * sigmoid_prime(zs[-1])
        nabla_b[-1] = delta
        nabla_w[-1] = np.dot(delta, activations[-2].transpose())
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

