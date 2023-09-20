#include "tensor.hpp"
#include <cstdlib>
#include <time.h>

Tensor::Tensor(){
}

Tensor::Tensor(int N, int W) : N_(N), W_(W) {
  data_ = new double[N_ * W_];
  grad_ = new double[N_ * W_];
}

Tensor::~Tensor(){
  delete data_;
  delete grad_;
}

double Tensor::getData(int n, int w){
  return data_[n * W_ + w];
}

double Tensor::getData(int n, int i, int o){
  return data_[n * W_ * O_ + i * O_ + o];
}

void Tensor::setData(int n, int w, double data){
  data_[n * W_ + w] = data;
}

void Tensor::setData(int n, double *data){
  for(int i=0; i<W_; ++i){
    data_[n*W_+i] = data[i];
  }
}

void Tensor::setData(int n, int i, int o, double data){
  data_[n * W_ * O_ + i * O_ + o] = data;
}

double Tensor::getGrad(int n, int w){
  return grad_[n * W_ + w];
}

double Tensor::getGrad(int n, int i, int o){
  return grad_[n * W_ * O_ + i * O_ + o];
}

void Tensor::setGrad(int n, int w, double grad){
  grad_[n * W_ + w] = grad;
}

void Tensor::setGrad(int n, int i, int o, double grad){
  grad_[n * W_ * O_ + i * O_ + o] = grad;
}

int Tensor::getN(){
  return N_;
}

int Tensor::getW(){
  return W_;
}
