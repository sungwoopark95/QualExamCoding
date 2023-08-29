#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <Eigen/Dense>
using namespace std; 
using namespace Eigen;

class Network {
private:
    int num_layers;
    vector<int> sizes;
    vector<VectorXd> biases;
    vector<MatrixXd> weights;

public:
    Network(vector<int> sizes) : sizes(sizes) {
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<> d(0, 1);

        for (int i = 1; i < sizes.size(); ++i) {
            VectorXd b(sizes[i]);
            for (int j = 0; j < sizes[i]; ++j) {
                b(j) = d(gen);
            }
            biases.push_back(b);
        }

        for (int i = 0; i < sizes.size() - 1; ++i) {
            MatrixXd w(sizes[i + 1], sizes[i]);
            for (int j = 0; j < sizes[i + 1]; ++j) {
                for (int k = 0; k < sizes[i]; ++k) {
                    w(j, k) = d(gen);
                }
            }
            weights.push_back(w);
        }
    }

    VectorXd feedforward(VectorXd a) {
        for (int i = 0; i < weights.size(); ++i) {
            a = sigmoid(weights[i] * a + biases[i]);
        }
        return a;
    }


    void SGD(vector<pair<VectorXd, VectorXd>> training_data, int epochs, int mini_batch_size, double lr, vector<pair<VectorXd, int>> test_data = {}) {
        int n = training_data.size();
        random_device rd;
        mt19937 g(rd());

        for (int j = 0; j < epochs; ++j) {
            shuffle(training_data.begin(), training_data.end(), g);
            for (int k = 0; k < n; k += mini_batch_size) {
                vector<pair<VectorXd, VectorXd>> mini_batch(training_data.begin() + k, training_data.begin() + k + mini_batch_size);
                update_mini_batch(mini_batch, lr);
            }
            if (!test_data.empty()) {
                cout << "Epoch " << j << ": " << evaluate(test_data) << " / " << test_data.size() << endl;
            } else {
                cout << "Epoch " << j << " complete" << endl;
            }
        }
    }

    void update_mini_batch(vector<pair<VectorXd, VectorXd>>& mini_batch, double lr) {
        vector<VectorXd> nabla_b;
        vector<MatrixXd> nabla_w;
        for (int i = 0; i < biases.size(); ++i) {
            nabla_b.push_back(VectorXd::Zero(biases[i].size()));
            nabla_w.push_back(MatrixXd::Zero(weights[i].rows(), weights[i].cols()));
        }

        for (auto& xy : mini_batch) {
            auto delta_nablas = backprop(xy.first, xy.second);
            for (int i = 0; i < nabla_b.size(); ++i) {
                nabla_b[i] += delta_nablas.first[i];
                nabla_w[i] += delta_nablas.second[i];
            }
        }

        for (int i = 0; i < weights.size(); ++i) {
            weights[i] -= (lr / mini_batch.size()) * nabla_w[i];
            biases[i] -= (lr / mini_batch.size()) * nabla_b[i];
        }
    }

    int evaluate(const vector<pair<VectorXd, int>>& test_data) {
        int correct_count = 0;
        for (const auto& data : test_data) {
            VectorXd result = feedforward(data.first);
            int predicted = distance(result.data(), max_element(result.data(), result.data() + result.size()));
            if (predicted == data.second) {
                correct_count++;
            }
        }
        return correct_count;
    }

    pair<vector<VectorXd>, vector<MatrixXd>> backprop(const VectorXd& x, const VectorXd& y) {
        vector<VectorXd> nabla_b;
        for (const auto& b : biases) {
            nabla_b.push_back(VectorXd::Zero(b.size()));
        }

        vector<MatrixXd> nabla_w;
        for (const auto& w : weights) {
            nabla_w.push_back(MatrixXd::Zero(w.rows(), w.cols()));
        }

        // Feedforward
        VectorXd activation = x;
        vector<VectorXd> activations = {x};
        vector<VectorXd> zs;

        for (size_t i = 0; i < biases.size(); ++i) {
            VectorXd z = weights[i] * activation + biases[i];
            zs.push_back(z);
            activation = sigmoid(z);
            activations.push_back(activation);
        }

        // Backward pass
        VectorXd delta = cost_derivative(activations.back(), y).cwiseProduct(sigmoid_prime(zs.back()));
        nabla_b.back() = delta;
        nabla_w.back() = delta * activations[activations.size() - 2].transpose();

        for (int l = 2; l < num_layers; ++l) {
            VectorXd z = zs[zs.size() - l];
            VectorXd sp = sigmoid_prime(z);
            delta = (weights[weights.size() - l + 1].transpose() * delta).cwiseProduct(sp);
            nabla_b[nabla_b.size() - l] = delta;
            nabla_w[nabla_w.size() - l] = delta * activations[activations.size() - l - 1].transpose();
        }

        return {nabla_b, nabla_w};
    }

    static VectorXd cost_derivative(const VectorXd& output_activations, const VectorXd& y) {
        return output_activations - y;
    }

    static VectorXd sigmoid(const VectorXd& z) {
        return 1.0 / (1.0 + (-z.array()).exp());
    }

    static VectorXd sigmoid_prime(const VectorXd& z) {
        return sigmoid(z).array() * (1 - sigmoid(z).array());
    }
};

int main() {
    vector<int> sizes = {2, 3, 1};
    Network net(sizes);
    // Further operations on the network
    return 0;
}
