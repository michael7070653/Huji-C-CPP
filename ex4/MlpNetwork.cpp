#include "MlpNetwork.h"


MlpNetwork:: MlpNetwork ( Matrix *weights, Matrix *biases):
    first_ (weights[0],biases[0],activation::relu),
    second_ (weights[1],biases[1],activation::relu),
    third_ (weights[2],biases[2],activation::relu),
    forth_ (weights[3],biases[3],activation::softmax){}


digit MlpNetwork:: operator()(const Matrix& input_x)const
{
//  input_x.vectorize();
  Matrix output(input_x);
  output.vectorize();
  output = first_(output);
  output = second_(output);
  output = third_(output);
  output = forth_(output);
  int max = output.argmax();
  return digit{(unsigned int)max,output[max]};
}
  