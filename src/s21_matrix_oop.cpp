#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(DEFAULT_MATRIX), cols_(DEFAULT_MATRIX) {
  MemoryAllocation();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw invalid_argument("Invalid number of rows or columns\n");
  }
  MemoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  MemoryAllocation();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }

  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows < 1) {
    throw invalid_argument("Invalid number of rows\n");
  }

  S21Matrix temp(rows, cols_);
  int currentRowsCount = 0;
  if (rows_ < rows) {
    currentRowsCount = rows_;
  }

  for (int i = 0; i < currentRowsCount; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
}

void S21Matrix::setCols(int cols) {
  if (cols < 1) {
    throw invalid_argument("Invalid number of rows\n");
  }

  S21Matrix temp(rows_, cols);
  int currentColsCount = 0;
  if (cols_ < cols) {
    currentColsCount = cols_;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < currentColsCount; j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (matrix_ == nullptr || other.matrix_ == nullptr || rows_ != other.rows_ ||
      cols_ != other.cols_) {
    result = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (matrix_[i][j] - other.matrix_[i][j] > ACCURACY) result = false;
      }
    }
  }

  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw invalid_argument("Matrix dimensions do not match\n");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw invalid_argument("Matrix dimensions do not match\n");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw invalid_argument(
        "Matrix dimensions do not match for multiplication\n");
  } else {
    S21Matrix result(rows_, other.cols_);

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < result.cols_; j++) {
        for (int k = 0; k < cols_; k++)
          result[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw invalid_argument("Error. Matrix must be square\n");
  } else {
    S21Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix MinorMatrix = Minor(i, j);
        result(i, j) = MinorMatrix.Determinant();
        result.matrix_[i][j] *= pow(-1, i + j);
      }
    }

    return result;
  }
}

S21Matrix S21Matrix::Minor(int rows, int cols) {
  int excludeRow = 0;
  int excludeCol = 0;
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_ - 1; i++) {
    if (i == rows) excludeRow = 1;
    for (int j = 0; j < cols_ - 1; j++) {
      if (j == cols) excludeCol = 1;
      result.matrix_[i][j] = matrix_[i + excludeRow][j + excludeCol];
    }
  }

  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw invalid_argument("Error. Matrix must be square\n");
  } else if (rows_ == 1) {
    return matrix_[0][0];
  } else if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    double sign = 1.0, result = 0;
    for (int i = 0; i < cols_; i++) {
      S21Matrix MinorMatrix = Minor(0, i);
      result += sign * matrix_[0][i] * MinorMatrix.Determinant();
      sign = -sign;
    }

    return result;
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw invalid_argument("Error. Matrix must be square\n");
  }

  double det = Determinant();
  if (det == 0) {
    throw invalid_argument("Error. Determinant equals 0\n");
  }

  S21Matrix result(rows_, cols_);
  result = CalcComplements().Transpose();
  result.MulNumber(1.0 / det);

  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);

  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);

  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) {
    return *this;
  } else {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    rows_ = other.rows_;
    cols_ = other.cols_;

    MemoryAllocation();

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }

    return *this;
  }
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);

  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);

  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);

  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);

  return *this;
}

double &S21Matrix::operator()(int rows, int cols) {
  if (rows_ < 1 || cols_ < 1 || rows >= rows_ || cols >= cols_) {
    throw invalid_argument("Invalid number of rows or columns\n");
  }

  return matrix_[rows][cols];
}
