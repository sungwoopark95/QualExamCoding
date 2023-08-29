#include "tensor.hpp"
#include "op.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <time.h>

Tanh::Tanh(){
}

Tanh::~Tanh(){
}

Tensor* Tanh::forward(Tensor* in){
  int N = in->getN();
  int W = in->getW();
  int len = N * W;
  out_ = new Tensor(N, W);

  for(int n=0; n<N; ++n){
    for(int w=0; w<W; ++w){
      out_->setData(n, w, tanh(in->getData(n, w)));
    }
  }
  return out_;
}

Tensor* Tanh::backward(Tensor* out){
  int N = out->getN();
  int W = out->getW();
  int len = N * W;
  in_ = new Tensor(N, W);

  double tmp;
  for(int n=0; n<N; ++n){
    for(int w=0; w<W; ++w){
      // TODO: read data from 'out' tensor
      //tmp = out->getData(n, w);

      // TODO: set gradient of 'in_' tensor
      //in_->setGrad(n, w, (1 - tmp * tmp) * out->getGrad(n, w));
    }
  }

  return in_;
}


Softmax::Softmax(){
}

Softmax::~Softmax(){
}

Tensor* Softmax::forward(Tensor* in){
  int N = in->getN();
  in_ = in;
  out_ = new Tensor(N, 3);

  double sum, exp0, exp1, exp2;
  for(int n=0; n<N; ++n){
    sum = 0.0;
    exp0 = exp(in->getData(n, 0));
    exp1 = exp(in->getData(n, 1));
    exp2 = exp(in->getData(n, 2));
    sum = exp0 + exp1 + exp2;

    out_->setData(n, 0, exp0/sum);
    out_->setData(n, 1, exp1/sum);
    out_->setData(n, 2, exp2/sum);
  }

  return out_;
}

Tensor* Softmax::backward(Tensor* out){
  int N = out->getN();

  double grad_val[3];
  double exp0, exp1, exp2, sum;
  double p0, p1, p2;

  for(int n=0; n<N; ++n){
    p0 = out->getData(n, 0);
    p1 = out->getData(n, 1);
    p2 = out->getData(n, 2);

    // TODO: calculate grad_val[0], grad_val[1], grad_val[2]
    ;

    in_->setGrad(n, 0, grad_val[0]);
    in_->setGrad(n, 1, grad_val[1]);
    in_->setGrad(n, 2, grad_val[2]);
  }

  return in_;
}

Linear::Linear() : ic_(1), oc_(1) {
}


Linear::Linear(int n, int ic, int oc) : n_(n), ic_(ic), oc_(oc) {
  in_ = new Tensor(n_, ic_);
  out_ = new Tensor(n_, oc_);
  weight_ = new Tensor(ic_, oc_);
  m_ = 0.0;

  std::srand(1);
  for(int i=0; i<ic_; ++i){
    for(int o=0; o<oc_; ++o){
      double rand_val =
        (double)std::rand() / (double)(RAND_MAX * 1000.0);

      weight_->setData(i, o, rand_val);
      weight_->setGrad(i, o, 0.0);
    }
  }
}

Linear::~Linear(){
  delete weight_;
}

Tensor* Linear::forward(Tensor* in){	

  int N = in->getN();

  for(int n=0; n<N; ++n){
    for(int o=0; o<oc_; ++o){
      double tmp = 0.0;
      for(int i=0; i<ic_; ++i){
        tmp += in->getData(n,i) * weight_->getData(i, o);
      }
      out_->setData(n, o, tmp);
    }
  }
  in_ = in;
  return out_;
}

Tensor* Linear::backward(Tensor* out){	
  out_ = out;
  int N = out->getN();

  // calculate and set gradeint of 'in_' tensor
  for(int n=0; n<N; ++n){
    for(int i=0; i<ic_; ++i){
      double tmp = 0.0;
      // TODO: calculate tmp
      for(int o=0; o<oc_; ++o){
        ;
      }

      in_->setGrad(n, i, tmp);
    }
  }

  // calculate and set gradient of 'weight_' tensor
  for(int i=0; i<ic_; ++i){
    for(int o=0; o<oc_; ++o){
      double tmp_grad = 0;
      // TODO: calculate tmp_grad
      for(int n=0; n<N; ++n){
        ;
      }

      weight_->setGrad(i, o, tmp_grad);
    }
  }

  return in_;
}

void Linear::update_weight(double learning_rate){
  for(int i=0; i<ic_; ++i){
    for(int o=0; o<oc_; ++o){
      m_ = 0.9 * m_ + 0.1 * weight_->getGrad(i, o);
      double revised_grad = weight_->getData(i, o) - learning_rate * m_;
      weight_->setData(i, o, revised_grad);
    }
  }
}

Tensor* Linear::getWeight(){
  return weight_;
}


Loss::Loss() : n_(1){
}

Loss::Loss(int n) : n_(n){
}

Loss::~Loss(){
  delete ctx_;
}

double Loss::forward(Tensor *in, int *answer){
  double loss = 0.0;
  ctx_ = new double[n_ * 6];

  for(int n=0; n<n_; ++n){
    loss += - answer[n*3 + 0] * log(in->getData(n, 0))
      - answer[n*3 + 1] * log(in->getData(n, 1))
      - answer[n*3 + 2] * log(in->getData(n, 2));

    ctx_[n*6 + 0] = (double)answer[n*3 + 0];
    ctx_[n*6 + 1] = (double)answer[n*3 + 1];
    ctx_[n*6 + 2] = (double)answer[n*3 + 2];

    ctx_[n*6 + 3] = in->getData(n, 0);
    ctx_[n*6 + 4] = in->getData(n, 1);
    ctx_[n*6 + 5] = in->getData(n, 2);
  }
  return loss / (double)(n_);
}

void Loss::backward(Tensor *out){
  double dloss = 1.0;
  double grad;

  // TODO: calculate grad and set gradient of 'out' tensor
  ;
}
