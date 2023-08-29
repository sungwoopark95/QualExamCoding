#include "tensor.hpp"
#include "config.hpp"
#include <iostream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION 
#include "stb/stb_image.h" 
#define STB_IMAGE_RESIZE_IMPLEMENTATION 
#include "stb/stb_image_resize.h"

using namespace std;

int max3(double a, double b, double c){
  if(a>b){
    if(a>c) return 0;
    else return 2;
  } 
  else {
    if(b>c) return 1;
    else return 2;
  }
}

// Tensor *t, *target : tensor and target values for training
// Tensor *it, *itarget : tensor and target values for inference
bool inputDataset(Tensor* t, int *target, Tensor *it, int *itarget){
  cout  << "Initialize Dataset from image files\n"
    << "==================================\n";

  int x, y, n;

  // bedroom images for training and inference
  for(int i=0; i < TRAIN_IMAGES_PER_CLASS + TEST_IMAGES_PER_CLASS; ++i){
    // load image 
    string filename = string(DATASET_DIR) + "/bed_room/" + to_string(i+1) + ".jpg";	
    char const *filename_char = filename.c_str();
    uint8_t *rgb_image = stbi_load(filename_char, &x, &y, &n, 0);
    if (rgb_image == NULL)
      return false;

    // resize image to 3x300x300
    uint8_t *resize_image = new uint8_t[3*300*300];
    stbir_resize_uint8(rgb_image, x, y, 0, resize_image, 300, 300, 0, 3);

    // flatten + divide by 255.0
    double *double_image = new double[3*300*300];
    for(int j=0; j<3*300*300; ++j){
      double_image[j] = (double)resize_image[0] / 255.0;
    }

    if(i < TRAIN_IMAGES_PER_CLASS) {
      // insert target(0~9) value for Loss function (CrossEntropy)
      target[(i+TRAIN_IMAGES_PER_CLASS*0)*3+0] = 1;
      target[(i+TRAIN_IMAGES_PER_CLASS*0)*3+1] = 0;
      target[(i+TRAIN_IMAGES_PER_CLASS*0)*3+2] = 0;

      // insert image data into i-th row of train Tensor
      t->setData(i+TRAIN_IMAGES_PER_CLASS*0, double_image);
    }
    else {
      itarget[(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*0)*3+0] = 1;
      itarget[(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*0)*3+1] = 0;
      itarget[(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*0)*3+2] = 0;

      it->setData(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*0, double_image);
    }
  }
  cout << "Loaded bed room images" << endl;

  // dining room images for training and inference
  for(int i=0; i < TRAIN_IMAGES_PER_CLASS + TEST_IMAGES_PER_CLASS; ++i){
    string filename = string(DATASET_DIR) + "/dining_room/" + to_string(i+1) + ".jpg";	
    char const *filename_char = filename.c_str();
    uint8_t *rgb_image = stbi_load(filename_char, &x, &y, &n, 0);
    if (rgb_image == NULL)
      return false;

    uint8_t *resize_image = new uint8_t[3*300*300];
    stbir_resize_uint8(rgb_image, x, y, 0, resize_image, 300, 300, 0, 3);
    double *double_image = new double[3*300*300];
    for(int j=0; j<3*300*300; ++j){
      double_image[j] = (double)resize_image[0] / 255.0;
    }
    if(i < TRAIN_IMAGES_PER_CLASS) {
      // insert target (10~19)
      target[(i+TRAIN_IMAGES_PER_CLASS*1)*3+0] = 0;
      target[(i+TRAIN_IMAGES_PER_CLASS*1)*3+1] = 1;
      target[(i+TRAIN_IMAGES_PER_CLASS*1)*3+2] = 0;

      // insert image into 10~19th row of train Tensor
      t->setData(i+TRAIN_IMAGES_PER_CLASS*1, double_image);
    }
    else {
      itarget[(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*1)*3+0] = 0;
      itarget[(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*1)*3+1] = 1;
      itarget[(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*1)*3+2] = 0;

      it->setData(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*1, double_image);
    }
  }
  cout << "Loaded dining room images" << endl;

  // living room images for training and inference
  for(int i=0; i < TRAIN_IMAGES_PER_CLASS + TEST_IMAGES_PER_CLASS; ++i){
    string filename = string(DATASET_DIR) + "/living_room/" + to_string(i+1) + ".jpg";	
    char const *filename_char = filename.c_str();
    uint8_t *rgb_image = stbi_load(filename_char, &x, &y, &n, 0);
    if (rgb_image == NULL)
      return false;

    uint8_t *resize_image = new uint8_t[3*300*300];
    stbir_resize_uint8(rgb_image, x, y, 0, resize_image, 300, 300, 0, 3);
    double *double_image = new double[3*300*300];
    for(int j=0; j<3*300*300; ++j){
      double_image[j] = (double)resize_image[0] / 255.0;
    }
    if (i < TRAIN_IMAGES_PER_CLASS) {
      // insert target(20-29)
      target[(i+TRAIN_IMAGES_PER_CLASS*2)*3+0] = 0;
      target[(i+TRAIN_IMAGES_PER_CLASS*2)*3+1] = 0;
      target[(i+TRAIN_IMAGES_PER_CLASS*2)*3+2] = 1;

      // insert image into 20-29th row of train Tensor
      t->setData(i+TRAIN_IMAGES_PER_CLASS*2, double_image);
    } 
    else {
      itarget[(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*2)*3+0] = 0;
      itarget[(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*2)*3+1] = 0;
      itarget[(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*2)*3+2] = 1;

      it->setData(i-TRAIN_IMAGES_PER_CLASS+TEST_IMAGES_PER_CLASS*2, double_image);
    }
  }
  cout << "Loaded living room images\n" << endl;

  return true;
}

void predict(Tensor *t, int *target){
  cout 	<< "\nInference : O(Correct), X(Wrong)\n"
    << "==================================\n";

  double accuracy = 0.0;
  int num_correct = 0;

  for(int n=0; n<TEST_BATCH; ++n){
    int pred = max3(t->getData(n, 0), t->getData(n,1), t->getData(n,2));

    cout << "Predict image["<< n << "] as ";
    if(pred == 0) cout << "Bed Room    ";
    else if(pred == 1) cout << "Dining Room ";
    else cout << "Living Room ";

    cout << "(";
    if(target[n*3+pred] == 1) {
      cout << "O)\n";
      ++num_correct;
    }
    else cout << "X)\n";
  }
  cout 	<< "----------------------------------\n"
    << "Accuracy : " << (double)num_correct / (double)TEST_BATCH << endl;
}

void print_config(int num_epochs){
  cout  << "\nModel: Image-Classification\n"
    << "----------------------------------\n"
    << "Layer\t\tShape\t\n"
    << "==================================\n"
    << "Linear_0 \t(" << TRAIN_BATCH << ", 3*300*300, 256)\n"
    << "Tanh_0   \t(" << TRAIN_BATCH << ", 256)\n"
    << "Linear_1 \t(" << TRAIN_BATCH << ", 256, 3)\n"
    << "Softmax_0\t(" << TRAIN_BATCH << ", 3)\n"
    << "----------------------------------\n\n"
    << "Hyper parameters\n"
    << "==================================\n"
    << "Epochs\t\t"       << num_epochs
    << "\nNumber of images for training  \t"   << TRAIN_BATCH 
    << "\nNumber of images for test  \t"   << TEST_BATCH 
    << "\nLearning Rate \t" << LEARNING_RATE
    << "\n----------------------------------\n"
    << endl;
}

void print_test_config(int type, int datasetsize){

  cout    << "Layer Test\n"
    << "----------------------------------\n"
    << "Type\t\tshape\n"
    << "==================================\n";

  if(type == 0){
    cout  << "Linear   \t(" << datasetsize << ", 3, 2)\n";
  }
  else if(type == 1){
    cout  << "Tanh     \t(" << datasetsize << ", 3)\n";
  }
  else if(type == 2){
    cout  << "Softmax  \t(" << datasetsize << ", 3)\n";
  }
  else if(type == 3){
    cout  << "Loss     \t(" << datasetsize << ", 1)\n";
  }

}


void validation(Tensor *t, int dataset_size, int test_type){

  cout    << "\nValidation\n"
    << "----------------------------------\n";

  double linear_answer[30] = {0.00123457, 0.00158154, 0.0011092, 0.00123457, 0.00158154, 0.0011092, 0.00123457, 0.00158154, 0.0011092, 0.00123457, 0.00158154, 0.0011092, 0.00123457, 0.00158154, 0.0011092, 0.00123457, 0.00158154, 0.0011092, 0.00123457, 0.00158154, 0.0011092, 0.00123457, 0.00158154, 0.0011092, 0.00123457, 0.00158154, 0.0011092, 0.00123457, 0.00158154, 0.0011092};

  double tanh_answer[30] = {0.52953, 0.859276, 0.571653, 0.560214, 0.478829, 0.961967, 0.895538, 0.582815, 0.926643, 0.746498, 0.802725, 0.689445, 0.877905, 0.776658, 0.451229, 0.47569, 0.684187, 0.621489, 0.980214, 0.706247, 0.999734, 0.943251, 0.981401, 0.555957, 0.975848, 0.855024, 0.983342, 0.988253, 0.420663, 0.953837};

  double softmax_answer[30] = {-0.378569, 0.0053179, 0.373251, -0.311342, 0.0710492, 0.240292, -0.282263, 0.00708343, 0.27518, -0.341501, -0.00798326, 0.349484, -0.303536, -0.0591553, 0.362691, -0.361141, 0.0205481, 0.340593, -0.27803, 0.0155336, 0.262497, -0.330206, -0.050775, 0.380981, -0.305166, 0.00320641, 0.30196, -0.225313, -0.0135999, 0.238913};

  double loss_answer[30] = {-0, -2.53561, -0, -0, -1.09692, -0, -0, -1.30169, -0, -0, -2.09469, -0, -0, -1.9478, -0, -0, -1.57304, -0, -0, -1.64753, -0, -0, -7.28695, -0, -0, -2.49411, -0, -0, -1.00108, -0};

  int cnt = 0;


  // Linear, FC(3,2)
  if(test_type == 0){
    for(int i=0; i<dataset_size; ++i){
      for(int j=0; j<3; ++j){
        if(abs(t->getGrad(i, j) - linear_answer[i*3+j]) < 1e-5 ) cnt++;
        else cout << "[" << i*3+j << "] " << "wrong value : " << t->getGrad(i, j) << "\tanswer : " << linear_answer[i*3+j] << endl;	
      }
    }
    cout << "[corrects/total] " << cnt << " / " << 3*dataset_size << endl;
  }

  // Tanh (3)
  else if(test_type == 1){
    for(int i=0; i<dataset_size; ++i){
      for(int j=0; j<3; ++j){
        if(abs(t->getGrad(i, j) - tanh_answer[i*3+j]) < 1e-3 ) cnt++;
        else cout << "[" << i*3+j << "] " << "wrong value : " << t->getGrad(i, j) << " answer : " << tanh_answer[i*3+j] << endl;	
      } 
    } 
    cout << "[corrects/total] " << cnt << " / " << 3*dataset_size << endl;
  }

  // Softmax(3)
  else if(test_type == 2){
    for(int i=0; i<dataset_size; ++i){
      for(int j=0; j<3; ++j){
        if(abs(t->getGrad(i, j) - softmax_answer[i*3+j]) < 1e-3 ) cnt++;
        else cout << "[" << i*3+j << "] " << "wrong value : " << t->getGrad(i, j) << " answer : " << softmax_answer[i*3+j] << endl;	
      }
    } 
    cout << "[corrects/total] " << cnt << " / " << 3*dataset_size << endl;
  }

  // Loss Func (3, 1)
  else if(test_type == 3){
    for(int i=0; i<dataset_size; ++i){
      for(int j=0; j<3; ++j){
        if(abs(t->getGrad(i, j) - loss_answer[i*3+j] / (double)dataset_size) < 1e-3 ) cnt++;
        else cout << "[" << i*3+j << "] " << "wrong value : " << t->getGrad(i, j) << " answer : " << loss_answer[i*3+j] / (double)dataset_size << endl;	
      }
    } cout << endl;
    cout << "[corrects/total] " << cnt << " / " << 3*dataset_size << endl;
  }
}


