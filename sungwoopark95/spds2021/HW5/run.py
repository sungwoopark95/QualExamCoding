import fashion_mnist_loader
import prob1
import prob2
import prob3
import sys

train, test = fashion_mnist_loader.load_data_wrapper()

if sys.argv[1] == 'prob1':
  net = prob1.Network([784, 30, 10])
  net.SGD(train, 5, 10, 0.05, test_data=test)
elif sys.argv[1] == 'prob2':
  net = prob2.FTNetwork([784, 30, 10])
  print("==Full training==")
  net.SGD(train, 3, 10, 0.05, test_data=test, tuning=False)
  print("==Fine-tuning==")
  net.SGD(train, 3, 10, 0.05, test_data=test, tuning=True)
elif sys.argv[1] == 'prob3':
  net = prob3.MomentumNetwork([784, 30, 10])
  net.SGD(train, 5, 10, 0.005, 0.9, test_data=test)

