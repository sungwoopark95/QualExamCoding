#pragma once

class Tensor{
  public:
    Tensor();
    Tensor(int N, int W);
    ~Tensor();
    double getData(int n, int w);
    double getData(int n, int i, int o);
    void setData(int n, int w, double data);
    void setData(int n, double *data);
    void setData(int n, int i, int o, double data);
    double getGrad(int n, int w);
    double getGrad(int n, int i, int o);
    void setGrad(int n, int w, double grad);
    void setGrad(int n, int i, int o, double grad);
    int getN();
    int getW();
  private:
    int N_;
    int W_;
    int O_;
    double *data_;
    double *grad_;
};
