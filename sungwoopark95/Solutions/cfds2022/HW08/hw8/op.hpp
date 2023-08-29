#pragma once

class Tanh{
  public:
    Tanh();
    ~Tanh();
    Tensor* forward(Tensor* in);
    Tensor* backward(Tensor* out);
  private:
    Tensor* out_;
    Tensor* in_;
};

class Softmax{
  public:
    Softmax();
    ~Softmax();
    Tensor* forward(Tensor* in);
    Tensor* backward(Tensor* out);
  private:
    Tensor* out_;
    Tensor* in_;
};

class Linear{
  public:
    Linear();
    Linear(int n, int ic, int oc);
    ~Linear();
    Tensor* forward(Tensor* in);
    Tensor* backward(Tensor* out);
    void update_weight(double lr);
    Tensor* getWeight();

    double m_;
  private:
    int n_, ic_, oc_;
    Tensor* out_;
    Tensor* in_;
    Tensor* weight_;
};

class Loss{
  public:
    Loss();
    Loss(int n);
    ~Loss();
    double forward(Tensor* in, int *answer);
    void backward(Tensor* out);
  private:
    int n_;
    double *ctx_;
};
