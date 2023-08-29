#include "tensor.hpp"
#include "op.hpp"
#include "util.hpp"
#include "config.hpp"
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]){
  int num_epochs = 3;
  if(argc > 1) {
    num_epochs = stoi(argv[1]);
  } 

  // print configuration of this model
  print_config(num_epochs);

  // Tensors for training
  Tensor *t0 = new Tensor(TRAIN_BATCH, 3*300*300);
  Tensor *t1 = new Tensor(TRAIN_BATCH, 256);
  Tensor *t2 = new Tensor(TRAIN_BATCH, 256);
  Tensor *t3 = new Tensor(TRAIN_BATCH, 3);
  Tensor *t4 = new Tensor(TRAIN_BATCH, 3);
  int train_target[TRAIN_BATCH * 3];

  // Tensors for inference
  Tensor *i0 = new Tensor(TEST_BATCH, 3*300*300);
  Tensor *i1 = new Tensor(TEST_BATCH, 256);
  Tensor *i2 = new Tensor(TEST_BATCH, 256);
  Tensor *i3 = new Tensor(TEST_BATCH, 3);
  Tensor *i4 = new Tensor(TEST_BATCH, 3);
  int test_target[TEST_BATCH * 3];

  bool loaded = inputDataset(t0, train_target, i0, test_target);
  if (loaded == false) {
    fprintf(stderr, "Failed to load images\n");
    return EXIT_FAILURE;
  }

  // Init Model
  Linear linear0 = Linear(TRAIN_BATCH, 3*300*300, 256);
  Tanh tanh0 = Tanh();
  Linear linear1 = Linear(TRAIN_BATCH, 256, 3);
  Softmax softmax0 = Softmax();
  Loss lossfunc0 = Loss(TRAIN_BATCH);

  cout 	<< "Start Training\n"
    << "==================================\n";

  // Training
  for(int e=0; e<num_epochs; ++e){
    // Forward
    t1 = linear0.forward(t0);
    t2 = tanh0.forward(t1);
    t3 = linear1.forward(t2);
    t4 = softmax0.forward(t3);

    double loss = lossfunc0.forward(t4, train_target);
    cout << "[Epoch " << e+1 << "/" << num_epochs << "] Loss : " << loss << endl;

    lossfunc0.backward(t4);
    t3 = softmax0.backward(t4);
    t2 = linear1.backward(t3);
    t1 = tanh0.backward(t2);
    t0 = linear0.backward(t1);

    linear1.update_weight(LEARNING_RATE);
    linear0.update_weight(LEARNING_RATE);
  }

  // Inference 
  i1 = linear0.forward(i0);
  i2 = tanh0.forward(i1);
  i3 = linear1.forward(i2);
  i4 = softmax0.forward(i3);

  predict(i4, test_target);

  delete t0, t1, t2, t3, t4;
  delete i0, i1, i2, i3, i4;

  return 0;
}
