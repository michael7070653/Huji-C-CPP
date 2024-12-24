#include "Activation

.h"
#include <cmath>



Matrix activation::relu(const Matrix& matrix_to)
{
  Matrix relu_matrix(matrix_to);
for (int i = 0; i < matrix_to.get_rows()*matrix_to.get_cols(); i++)
  {
    if (relu_matrix[i] < 0)
    {
      relu_matrix[i] = 0;
    }
  }
  return relu_matrix;
}


Matrix activation::softmax(const Matrix& matrix_to)
{
  Matrix relu_matrix(matrix_to);
    float sum = 0;
    for (int i = 0; i < matrix_to.get_rows()*matrix_to.get_cols(); i++)
        {
          relu_matrix[i] = std::exp(matrix_to[i]);
            sum += relu_matrix[i];
        }
    sum= 1 / sum;
    relu_matrix = sum * relu_matrix;

    return relu_matrix;

}


