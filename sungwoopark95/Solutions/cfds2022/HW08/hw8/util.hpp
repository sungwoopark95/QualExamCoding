#pragma once

int max3(double a, double b, double c);
bool inputDataset(Tensor* t, int *target, Tensor *it, int *itarget);
void predict(Tensor *t, int *target);
void print_config(int num_epochs);
void print_test_config(int type, int batchsize);
void validation(Tensor *t, int batchsize, int testtype);
