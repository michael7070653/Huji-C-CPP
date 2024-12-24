#include "Dense.h"


Dense::Dense(const Matrix &weights, const Matrix& bias, func activation)
{
  this->bias_= bias;
  this->weights_ = weights;
  this->active_func = activation;
}



const Matrix& Dense::get_weights ()const
{
return weights_;
}


const Matrix& Dense:: get_bias ()const
{
  return bias_;
}




func Dense:: get_activation ()const
{
  return active_func;
}




Matrix Dense::operator()(const Matrix& x_vec)const
{
  Matrix new_mat = weights_ * x_vec;
  new_mat  = new_mat + bias_;
  return active_func(new_mat);
}
