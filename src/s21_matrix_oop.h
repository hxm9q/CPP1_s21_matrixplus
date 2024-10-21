#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

using namespace std;

#define DEFAULT_MATRIX 2
#define ACCURACY 1e-7

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  void MemoryAllocation() {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
    }
  }

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int getRows() const;
  int getCols() const;
  void setRows(int rows);
  void setCols(int cols);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix Minor(int rows, int cols);
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int rows, int columns);

  double* operator[](int index) { return matrix_[index]; }
};

#endif