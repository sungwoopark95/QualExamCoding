import os
import gzip
import numpy as np
def load_mnist(path, kind='train'):
  labels_path = os.path.join(path,
                             '%s-labels-idx1-ubyte.gz'
                             % kind)
  images_path = os.path.join(path,
                             '%s-images-idx3-ubyte.gz'
                             % kind)

  with gzip.open(labels_path, 'rb') as lbpath:
    labels = np.frombuffer(lbpath.read(), dtype=np.uint8,
    offset=8)

  with gzip.open(images_path, 'rb') as imgpath:
    images = np.frombuffer(imgpath.read(), dtype=np.uint8,
    offset=16).reshape(len(labels), 784)

  return images, labels

def load_data_wrapper():
  x_train, y_train = load_mnist('/home/share/mnist/fashion', kind='train')
  x_test, y_test  = load_mnist('/home/share/mnist/fashion', kind='t10k')
  training_inputs = [np.reshape(x, (784, 1)).astype(np.float32)/256 for x in x_train]
  training_results = [vectorized_result(y) for y in y_train]
  training_data = list(zip(training_inputs, training_results))

  test_inputs = [np.reshape(x, (784, 1)).astype(np.float32)/256 for x in x_test]
  test_results = y_test 
  test_data = list(zip(test_inputs, test_results))
  return (training_data, test_data)

def vectorized_result(j):
  e = np.zeros((10, 1))
  e[j] = 1.0
  return e
