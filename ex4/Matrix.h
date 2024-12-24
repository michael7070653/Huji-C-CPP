// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>



// You don't have to use the struct. Can help you with MlpNetwork.h
typedef struct matrix_dims {
    int rows, cols;
}matrix_dims;



/**
 * A class representing a matrix.
 */

class Matrix
{
 private:
  int rows;
  int cols;

 public :
    float *matrix;
    int get_rows()const;
    int get_cols()const;


    /**
     * Constructor for the matrix.
     * @param rows
     * @param cols
     */
  explicit Matrix(int rows = 1 , int cols = 1);
/**
 * Copy constructor for the matrix.
 * @param matrix_1
 */

  Matrix(const Matrix& matrix_1);


  /**
   * Transposes the matrix.
   * @return reference to the transposed matrix
   */
    Matrix& transpose();


    Matrix& vectorize();

    /**
     * Prints the matrix to the console.
     */
    void plain_print() const;

    Matrix dot(const Matrix &matrix_1)const;

    float norm() const;

    Matrix rref();

    int argmax()const;

    float sum()const;

    Matrix &operator +=(const Matrix &matrix_1);

    Matrix operator +(const Matrix &matrix_1)const;

    Matrix &operator =(const Matrix &matrix_1);

    Matrix operator *(const Matrix &matrix_1) const;//matrix in matrix

    float& operator[](int index) const;

    friend Matrix operator*(const Matrix& m_left, float x);

    friend Matrix operator*( float x, const Matrix& r_left);

    float& operator ()(int index_row, int index_cols)const;
//    float & operator ()(int index_row, int index_cols);




  /**
*Overloads the << operator to allow printing the matrix to an output stream.
*/
  friend std::ostream& operator<<(std::ostream& s, const Matrix& m);

  /**
  *Overloads the >> operator to allow reading the matrix from an input stream
  */
  friend std::istream& operator>>(std::istream& is, Matrix& m);

  ~Matrix();


};





#endif //MATRIX_H