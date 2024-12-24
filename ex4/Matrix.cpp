#include "Matrix.h"
#include <iostream>
#include <cmath>
// Created by מיכאל מסיקה on 18/02/2024.


//#define LENGTH_ERROR "The dimensions arent good"
//#define OUT_OF_RANGE "you are out of matrix range"
//#define FILE_ERROR "the file isn't good"
#define MIN 0.1



/**
 *Constructor for the matrix.
 */

Matrix::Matrix (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::exception();
  }
  this->cols = cols;
  this-> rows = rows;
  this->matrix = new(std::nothrow) float [rows * cols]();
  if (this->matrix == nullptr)
  {
    throw std::exception();
  }
}



int Matrix::get_cols () const
{
  return this->cols;
}


int Matrix::get_rows () const
{return this->rows;}



/**
 *Copy constructor for the matrix.
 */

Matrix::Matrix(const Matrix& matrix_1)
{


    this->cols = matrix_1.cols;
    this->rows = matrix_1.rows;
    this->matrix = new(std::nothrow) float [rows*cols]();
    if (this->matrix == nullptr)
    {
        throw;
    }
    for (int i = 0; i < rows*cols; i++)
    {
      (*this)[i] = matrix_1[i];
    }
}
/**
 *Transposes the matrix.
 */

Matrix& Matrix::transpose ()
{
  float *tamp_matrix = new(std::nothrow) float [rows * cols]();
  if (tamp_matrix == nullptr)
  {
    throw;
  }
  std::copy(this->matrix,
            this->matrix + rows*cols, tamp_matrix);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
          matrix[j * rows + i] =   tamp_matrix[i * cols + j];
        }
    }
    int temp = this->cols;
    this->cols = this->rows;
    this->rows = temp;
    delete[] tamp_matrix;
  return *this;
}

/**
 *Changes the matrix to a vector.
 */
Matrix& Matrix::vectorize()
{
  this->rows = this->rows * this->cols;
  this->cols = 1;
  return *this;
}


/**
 *Prints the matrix to the standard output.
 */

void Matrix::plain_print () const
{
    for (int i = 0; i < rows * cols; i++)
    {
        std::cout<<matrix[i]<<" ";
        if(i % cols == cols - 1)
        {
            std::cout<<std::endl;
        }
    }

}










/**
 *Calculates the dot product of two matrices.
 */

Matrix Matrix::dot (const Matrix &matrix_1)const
{
  if (cols!= matrix_1.cols || rows != matrix_1.rows)
  {
    throw std::exception();
  }

  Matrix new_matrix(rows, cols);

  for(int row = 0; row < new_matrix.rows; row++)
  {
    for(int col = 0; col < cols * rows; col++)
    {
      new_matrix[col] = matrix[col]* matrix_1[col];
    }
  }
  return new_matrix;
}





/**
 *Calculates the norm of the matrix.
 */


float Matrix::norm () const
{
  float res=0;
  for (int i = 0; i < rows*cols; i++)
  {
    res += this->matrix[i]*this->matrix[i];
  }
  return sqrt(res);
}






/**
 *Destructor for the matrix.
 */

Matrix::~Matrix ()
{
  delete[] this->matrix;
}


/**
 *Returns the index of the maximum element in the matrix.
 */

int Matrix::argmax ()const
{
  int max_ind = 0;
  float max = this->matrix[0];
  for (int i = 0; i < rows * cols; i++)
  {
    if (this->matrix[i] > max)
    {
      max = this->matrix[i];
      max_ind = i;
    }
  }
  return max_ind;
}





/**
 *Calculates the reduced row echelon form of the matrix.
 */

Matrix Matrix::rref()
{
  Matrix result(*this);
  int lead = 0;
  int row_count = result.get_rows ();
  int col_count = result.get_cols ();
  for (int row = 0; row < row_count; row++){
    if (col_count <= lead){
      break;}
    int pivot_row = row;
    while (result(pivot_row, lead) == 0){
      pivot_row++;
      if (pivot_row == row_count){
        pivot_row = row;
        lead++;
        if (col_count == lead){
          return result;}
      }
    }

    for (int col = 0; col < col_count; col++){
      float temp = result(pivot_row, col);
      result(pivot_row, col)
      = result(row, col);
      result(row, col) = temp;
    }

    float pivot = result(row, lead);
    for (int col = 0; col < col_count; col++){
      result(row, col) /= pivot;
    }

    for (int other_row = 0; other_row < row_count; other_row++){
      if (other_row != row)
      {
        float factor = result(other_row, lead);
        for (int col = 0; col < col_count; col++)
        {
          result(other_row, col) -=
              factor * result(row, col);
        }
      }
    }
    lead++;
  }
  return result;
}


/**
 *Calculates the sum of all the elements in the matrix.
 */

float Matrix::sum ()const
{
  float res = 0;
  for (int i = 0; i < rows * cols; i++)
  {
    res += this->matrix[i];
  }
  return res;
}






/**
 *Overloads the = operator to allow assignment of a matrix to a matrix.
 */

Matrix& Matrix:: operator=(const Matrix& matrix_1)
{
  if(this == &matrix_1)
  {
    return *this;
  }
    delete[] this->matrix;  //delete the old matrix
    this->rows = matrix_1.rows;
    this->cols = matrix_1.cols;
    this->matrix = new(std::nothrow) float [rows * cols]();
    if (this->matrix == nullptr)
    {
      throw;
    }
    std::copy(matrix_1.matrix,
              matrix_1.matrix + rows*cols, this->matrix);
  return *this;
}




/**
 *Overloads the += operator to allow addition of a matrix to a matrix.
 */

Matrix& Matrix:: operator+=(const Matrix& matrix_1)
{
    if (this->rows != matrix_1.rows || this->cols != matrix_1.cols)
    {
        throw std::exception();
    }
    for (int i = 0; i < rows*cols; i++)
    {
        matrix[i] += matrix_1[i];
    }
    return *this;
}





/**
 *Overloads the [] operator to allow access to the matrix elements.
 */
float& Matrix:: operator[](int index)const
{
  if(index >= this->cols * this->rows || index < 0)
  {
    throw std::exception();
  }
  return matrix[index];
}




Matrix Matrix::operator+(const Matrix& matrix_1) const
{
  if(this->rows != matrix_1.rows || this->cols != matrix_1.cols)
  {
    throw std::exception();
  }
  Matrix new_matrix(this->rows, this->cols);
  for(int i = 0; i< this->rows* this->cols;i++)
  {
    new_matrix.matrix[i]= this->matrix[i]+matrix_1.matrix[i];
  }
  return new_matrix;

}







/**
 *Overloads the * operator to allow multiplication of a matrix by a matrix.
 */

Matrix Matrix::operator*(const Matrix& matrix_1)const
{

  if (cols!= matrix_1.rows)
  {
    throw std::exception();
  }
  Matrix mult_matrix(rows, matrix_1.cols);

  for(int row = 0; row< mult_matrix.rows;row++)
  {
    for(int col = 0;col< mult_matrix.cols;col++)
    {
      float cord_ij = 0;
      for(int k = 0; k< cols;k++)
          {
            cord_ij+=((*this)(row,k)
                * matrix_1(k,col));
          }
        mult_matrix(row,col) = cord_ij;
    }
  }
  return mult_matrix;

}






/**
 *Overloads the () operator to allow access to the matrix elements.
 */

//float Matrix:: operator()(int index_row, int index_cols)const
//{
//  if(index_row >=this->rows || index_cols >this->cols|| index_row <0
//  ||index_cols<0 )
//  {
//    throw std::exception();
//  }
//
//  return (*this)[index_row * this->cols + index_cols];
//}



/**
 *Overloads the () operator to allow access to the matrix elements.
 */

float & Matrix:: operator()(int index_row, int index_cols)const
{
  if(index_row >=this->rows || index_cols >this->cols|| index_row <0
     ||index_cols<0 )
  {
    throw std::exception();
  }

  return (*this)[index_row * this->cols + index_cols];
}



/**
 *Overloads the * operator to allow multiplication
 * of a matrix by a scalar from the left.
 */
Matrix operator*(const Matrix& m_left,const float x)
{
  Matrix new_m(m_left);
  for (int i = 0; i < new_m.get_rows()*new_m.get_cols(); ++i)
  {
    new_m[i] = new_m[i] * x;
  }
  return new_m;
}

/**
 *Overloads the * operator to allow multiplication of a
 * matrix by a scalar from the right.
 */

Matrix operator*( float x, const Matrix& m_left)
{
  return m_left * x;

}


/**
 *Overloads the << operator to allow printing the matrix to an output stream.
 */
std::ostream& operator<<(std::ostream& s, const Matrix& m)
{
  for (int i=0; i<m.rows; i++){
    for (int j=0; j < m.cols; j++){
      if (m(i,j) > MIN){
        s << "**";
      }
      else{
        s << "  ";
      }
    }
    s << std::endl;
  }
  return s;
}



/**
 *Overloads the << operator to allow reading the matrix from an input stream.
 */
std::istream& operator>>(std::istream& is, Matrix& m)
{
   unsigned long int bytes_size_mat = m.get_cols()*m.get_rows() * sizeof
       (float);

  is.seekg (0, std::istream ::end);
  unsigned long int length = is.tellg();
  if(length < bytes_size_mat)
  {
    throw std::exception();
  }
  is.seekg (0, std::istream ::beg);

   char *buffer = new char [bytes_size_mat];
  if(!is.read (buffer,(long)bytes_size_mat))
  {
    delete[] buffer;
    throw std::exception();
  }
  delete [] m.matrix;
  m.matrix = (float *) buffer;
  return is;
}









