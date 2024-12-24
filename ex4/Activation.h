// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
typedef Matrix (*func)(const Matrix &m);

// Insert Activation namespace here...

namespace activation
{
Matrix relu(const Matrix& matrix_to);

Matrix softmax(const Matrix& matrix_to);

}
#endif //ACTIVATION_H