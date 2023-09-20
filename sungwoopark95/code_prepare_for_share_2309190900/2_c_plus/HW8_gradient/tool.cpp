#include "tensor.hpp"
#include "util.hpp"
#include "op.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){
  int test_type = 0;
  int num_inputs = 3;
  test_type = stoi(argv[1]); // 0 : fc, 1 : tanh, 2 : softmax, 3 : loss function
  num_inputs = stoi(argv[2]); // number of inputs : 1~10

  // Init Tensors to check validation of each layer
  Tensor *t0 = new Tensor(num_inputs, 3);
  Tensor *t1 = new Tensor(num_inputs, 3);
  Tensor *t2 = new Tensor(num_inputs, 2);

  // Input random values
  srand(1);
  for(int i=0; i<num_inputs; ++i){
    for(int j=0; j<3; ++j){
      t0->setData(i, j, rand() /(double)RAND_MAX);
    }
  }

  // Print configuration
  print_test_config(test_type, num_inputs);	

  // Linear Layer : FC(3, 2)
  if(test_type == 0){
    Linear linear0 = Linear(num_inputs, 3, 2);
    t2 = linear0.forward(t0);
    for(int i=0; i<num_inputs; ++i){
      for(int j=0; j<2; ++j){
        t2->setGrad(i, j, 1);
      }
    }
    t0 = linear0.backward(t2);
    validation(t0, num_inputs, test_type);
  }

  // Tanh Layer (3)
  else if(test_type == 1){
    Tanh tanh0 = Tanh();
    t1 = tanh0.forward(t0);
    for(int i=0; i<num_inputs; ++i){
      for(int j=0; j<3; ++j){
        t1->setGrad(i, j, 1);
      }
    }
    t0 = tanh0.backward(t1);
    validation(t0, num_inputs, test_type);
  }

  // Softmax Layer (3)
  else if(test_type == 2){
    Softmax softmax0 = Softmax();
    t1 = softmax0.forward(t0);
    for(int i=0; i<num_inputs; ++i){
      for(int j=0; j<3; ++j){
        t1->setGrad(i, j, j+1);
      }
    }
    t0 = softmax0.backward(t1);
    validation(t0, num_inputs, test_type);
  }

  // Loss Function (3, 1)
  else if(test_type == 3){
    int *target = new int[num_inputs * 3];
    for(int i=0; i<num_inputs; ++i){
      target[i*3+0] = 0;
      target[i*3+1] = 1;
      target[i*3+2] = 0;
    }
    Loss lossfunc0 = Loss(num_inputs);
    double loss = lossfunc0.forward(t0, target);
    lossfunc0.backward(t0);
    validation(t0, num_inputs, test_type);
  }

  delete t0, t1, t2;

  return 0;
}
