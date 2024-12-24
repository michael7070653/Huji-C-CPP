// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
//typedef Matrix (*func)(const Matrix &m);
class Dense{
 private:
  Matrix weights_;
  Matrix bias_;
  func active_func;


 public:
  Dense(const Matrix &weights, const Matrix& bias, func activation);


  const Matrix &get_weights ()const;
  const Matrix &get_bias ()const;
  func get_activation()const;


  Matrix operator()(const Matrix& x_vec)const;




};




#endif //DENSE_H