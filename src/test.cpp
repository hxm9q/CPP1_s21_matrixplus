#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(MatrixTest, InvalidArgumentConstructor) {
  EXPECT_THROW(S21Matrix matrix1(-1, -1), invalid_argument);
}

TEST(MatrixTest, InvalidArgumentConstructor2) {
  EXPECT_THROW(S21Matrix matrix1(-1, 3), invalid_argument);
}

TEST(MatrixTest, InvalidArgumentConstructor3) {
  EXPECT_THROW(S21Matrix matrix1(3, -3), invalid_argument);
}

TEST(MatrixTest, ConstructorBase) {
  S21Matrix matrix1;
  EXPECT_EQ(2, matrix1.getRows());
  EXPECT_EQ(2, matrix1.getCols());
}

TEST(MatrixTest, ConstructorParam) {
  S21Matrix matrix1(3, 5);
  EXPECT_EQ(3, matrix1.getRows());
  EXPECT_EQ(5, matrix1.getCols());
}

TEST(MatrixTest, ConstructorCopy) {
  S21Matrix matrix1(4, 6);
  S21Matrix matrix2(matrix1);
  EXPECT_EQ(4, matrix2.getRows());
  EXPECT_EQ(6, matrix2.getCols());
}

TEST(MatrixTest, ConstructorMove) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 5.0;
  S21Matrix copy(matrix1);
  S21Matrix matrix2(move(matrix1));
  EXPECT_EQ(2, matrix2.getRows());
  EXPECT_EQ(2, matrix2.getCols());
  EXPECT_TRUE(matrix2.EqMatrix(copy));
}

TEST(MatrixTest, ConstructorCopyValue) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1;
  matrix1(2, 2) = 2;
  matrix1(1, 1) = 3;
  S21Matrix copy(matrix1);
  ASSERT_EQ(matrix1.EqMatrix(copy), 1);
}

TEST(MatrixTest, InvalidArgumentsetRows) {
  S21Matrix matrix1;
  EXPECT_THROW(matrix1.setRows(-3), invalid_argument);
}

TEST(MatrixTest, InvalidArgumentSetCols) {
  S21Matrix matrix1;
  EXPECT_THROW(matrix1.setCols(-3), invalid_argument);
}

TEST(MatrixTest, EqMatrixRows) {
  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 5.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 6.0;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 5.0;
  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixCols) {
  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 5.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 6.0;
  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;
  matrix2(1, 2) = 6.0;
  matrix2(2, 0) = 7.0;
  matrix2(2, 1) = 8.0;
  matrix2(2, 2) = 9.0;
  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixRowsColsEmptyFalse) {
  S21Matrix matrix1(3, 5);
  S21Matrix matrix2(2, 4);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixEmptyTrue) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 2);
  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixUninitializedTrue) {
  S21Matrix matrix1, matrix2;
  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixTrue) {
  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 5.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 6.0;
  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 5.0;
  matrix2(2, 0) = 3.0;
  matrix2(2, 1) = 6.0;
  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixFalse) {
  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 5.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 6.0;
  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;
  matrix2(2, 0) = 5.0;
  matrix2(2, 1) = 6.0;
  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixAccuracyFalse) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1(0, 0) = 1.000001;
  matrix2(0, 0) = 1.;
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixAccuracyTrue) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1(0, 0) = 1.00000001;
  matrix2(0, 0) = 1.;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, SumMatrixInvalidArgumentRows) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 2);
  EXPECT_THROW(matrix1.SumMatrix(matrix2), invalid_argument);
}

TEST(MatrixTest, SumMatrixInvalidArgumentCols) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_THROW(matrix1.SumMatrix(matrix2), invalid_argument);
}

TEST(MatrixTest, SumMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 9.0;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 5.0;
  S21Matrix result(2, 2);
  result(0, 0) = 4.0;
  result(0, 1) = 10.0;
  result(1, 0) = 9.0;
  result(1, 1) = 14.0;
  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(result.EqMatrix(matrix1));
}

TEST(MatrixTest, SubMatrixInvalidArgumentRows) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 2);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), invalid_argument);
}

TEST(MatrixTest, SubMatrixInvalidArgumentCols) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), invalid_argument);
}

TEST(MatrixTest, SubMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 9.0;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 5.0;
  S21Matrix result(2, 2);
  result(0, 0) = 2.0;
  result(0, 1) = 2.0;
  result(1, 0) = 5.0;
  result(1, 1) = 4.0;
  matrix1.SubMatrix(matrix2);
  EXPECT_TRUE(result.EqMatrix(matrix1));
}

TEST(MatrixTest, MulNumber) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 9.0;
  S21Matrix result(2, 2);
  result(0, 0) = 7.5;
  result(0, 1) = 15.0;
  result(1, 0) = 17.5;
  result(1, 1) = 22.5;
  matrix1.MulNumber(2.5);
  EXPECT_TRUE(result.EqMatrix(matrix1));
}

TEST(MatrixTest, MulMatrixInvalidArgument) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 2);
  EXPECT_THROW(matrix1.MulMatrix(matrix2), invalid_argument);
}

TEST(MatrixTest, MultiplyMatrixIdentity) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double identity[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.getRows(); i++) {
    for (int j = 0; j < mat.getCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix identityMat = S21Matrix(3, 3);
  for (int i = 0; i < identityMat.getRows(); i++) {
    for (int j = 0; j < identityMat.getCols(); j++) {
      identityMat(i, j) = identity[i][j];
    }
  }

  mat.MulMatrix(identityMat);

  for (int i = 0; i < mat.getRows(); i++) {
    for (int j = 0; j < mat.getCols(); j++) {
      EXPECT_EQ(mat(i, j), matrix[i][j]);
    }
  }
}

TEST(MatrixTest, Transpose) {
  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 5.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 6.0;
  S21Matrix result(2, 3);
  result(0, 0) = 1.0;
  result(0, 1) = 2.0;
  result(0, 2) = 3.0;
  result(1, 0) = 4.0;
  result(1, 1) = 5.0;
  result(1, 2) = 6.0;
  S21Matrix matrix2 = matrix1.Transpose();
  EXPECT_TRUE(matrix2.EqMatrix(result));
}

TEST(MatrixTest, Transpos2) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  S21Matrix result(3, 2);
  result(0, 0) = 1.0;
  result(0, 1) = 4.0;
  result(1, 0) = 2.0;
  result(1, 1) = 5.0;
  result(2, 0) = 3.0;
  result(2, 1) = 6.0;
  S21Matrix matrix2 = matrix1.Transpose();
  EXPECT_TRUE(matrix2.EqMatrix(result));
}

TEST(MatrixTest, DeterminantInvalidArgumentCols) {
  S21Matrix matrix1(3, 2);
  EXPECT_THROW(matrix1.Determinant(), invalid_argument);
}

TEST(MatrixTest, DeterminantInvalidArgumentRows) {
  S21Matrix matrix1(2, 3);
  EXPECT_THROW(matrix1.Determinant(), invalid_argument);
}

TEST(MatrixTest, Determinant) {
  double corRes = -21;
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 8.0;
  matrix1(1, 1) = 9.0;
  double result = matrix1.Determinant();
  EXPECT_EQ(corRes, result);
}

TEST(MatrixTest, Determinant2) {
  double matrix[1][1] = {{5}};

  S21Matrix mat = S21Matrix(1, 1);
  mat(0, 0) = matrix[0][0];

  double determinant = mat.Determinant();

  EXPECT_EQ(determinant, matrix[0][0]);
}

TEST(MatrixTest, Determinant3) {
  double corRes = 3;
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 3;
  double result = matrix1.Determinant();
  EXPECT_EQ(corRes, result);
}

TEST(MatrixTest, Determinant4) {
  double corRes = 0.0;
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 0;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = 0;
  matrix1(1, 2) = 4;
  matrix1(2, 0) = 0;
  matrix1(2, 1) = 0;
  matrix1(2, 2) = 1.0;
  double result = matrix1.Determinant();
  EXPECT_EQ(corRes, result);
}

TEST(MatrixTest, Determinant5) {
  double corRes = 7;
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = -5;
  matrix1(0, 1) = -4;
  matrix1(1, 0) = -2;
  matrix1(1, 1) = -3;
  double result = matrix1.Determinant();
  ASSERT_DOUBLE_EQ(result, corRes);
}

TEST(MatrixTest, Determinant6) {
  S21Matrix matrix1(9, 9);
  double result = matrix1.Determinant();
  ASSERT_DOUBLE_EQ(result, 0);
}

TEST(MatrixTest, Determinant7) {
  double corRes = -292;
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 73;
  matrix1(0, 1) = 16;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = -4;
  double result = matrix1.Determinant();
  ASSERT_DOUBLE_EQ(result, corRes);
}

TEST(MatrixTest, CalcComplementsInvalidArgumentCols) {
  S21Matrix matrix1(3, 2);
  EXPECT_THROW(matrix1.CalcComplements(), invalid_argument);
}

TEST(MatrixTest, CalcComplementsInvalidArgumentRows) {
  S21Matrix matrix1(2, 3);
  EXPECT_THROW(matrix1.CalcComplements(), invalid_argument);
}

TEST(MatrixTest, CalcComplements) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.getRows(); i++) {
    for (int j = 0; j < mat.getCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  EXPECT_THROW(S21Matrix complements = mat.CalcComplements(), std::logic_error);
}

TEST(MatrixTest, CalcComplements2) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = -1.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 3.0;
  S21Matrix result(2, 2);
  result(0, 0) = 3.0;
  result(0, 1) = -2.0;
  result(1, 0) = 1.0;
  result(1, 1) = 1.0;
  S21Matrix matrix2 = matrix1.CalcComplements();
  EXPECT_TRUE(result.EqMatrix(matrix2));
}

TEST(MatrixTest, CalcComplements3) {
  S21Matrix matrix1(1, 1);
  EXPECT_THROW(matrix1.CalcComplements(), logic_error);
}

TEST(MatrixTest, CalcComplements4) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 3;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 20;
  matrix1(1, 1) = -2;
  S21Matrix result(2, 2);
  result(0, 0) = -2;
  result(0, 1) = -20;
  result(1, 0) = -1;
  result(1, 1) = 3;
  S21Matrix matrix2 = matrix1.CalcComplements();
  EXPECT_TRUE(matrix2.EqMatrix(result));
}

TEST(MatrixTest, InverseMatrixInvalidArgument) {
  S21Matrix matrix1(3, 2);
  EXPECT_THROW(matrix1.InverseMatrix(), invalid_argument);
}

TEST(MatrixTest, InverseMatrix2) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 2.0;
}
TEST(MatrixTest, OperatorPlusInvalidArgumentRows) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 2);
  EXPECT_THROW(matrix1 + matrix2, invalid_argument);
}

TEST(MatrixTest, OperatorPlusInvalidArgumentCols) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_THROW(matrix1 + matrix2, invalid_argument);
}

TEST(MatrixTest, OperatorPlus) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 9.0;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 5.0;
  S21Matrix result(2, 2);
  result(0, 0) = 4.0;
  result(0, 1) = 10.0;
  result(1, 0) = 9.0;
  result(1, 1) = 14.0;
  S21Matrix res = matrix1 + matrix2;
  EXPECT_TRUE(res.EqMatrix(result));
}

TEST(MatrixTest, OperatorPlus2) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.14;
  matrix1(0, 1) = 0.56;
  matrix1(1, 0) = -69.3;
  matrix1(1, 1) = 0;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = -78.14;
  matrix2(0, 1) = 0;
  matrix2(1, 0) = -0.3;
  matrix2(1, 1) = 2;
  S21Matrix result(2, 2);
  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  S21Matrix res = matrix1 + matrix2;
  EXPECT_TRUE(res.EqMatrix(result));
}

TEST(MatrixTest, OperatorMinusInvalidArgumentRows) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 2);
  EXPECT_THROW(matrix1 - matrix2, invalid_argument);
}

TEST(MatrixTest, OperatorMinusInvalidArgumentCols) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_THROW(matrix1 - matrix2, invalid_argument);
}

TEST(MatrixTest, OperatorMinus) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 9.0;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 5.0;
  S21Matrix result(2, 2);
  result(0, 0) = 2.0;
  result(0, 1) = 2.0;
  result(1, 0) = 5.0;
  result(1, 1) = 4.0;
  S21Matrix res = matrix1 - matrix2;
  EXPECT_TRUE(res.EqMatrix(result));
}

TEST(MatrixTest, OperatorMulMatrixInvalidArgument) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 2);
  EXPECT_THROW(matrix1 * matrix2, invalid_argument);
}

TEST(MatrixTest, OperatorMulMatrix2) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 3.0;
  matrix1(0, 1) = 27.0;
  matrix1(0, 2) = 18.0;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = 18.0;
  matrix1(1, 2) = 15.0;
  matrix1(2, 0) = 24.0;
  matrix1(2, 1) = 9.0;
  matrix1(2, 2) = 9.0;
  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 3.0;
  matrix2(0, 1) = 18.0;
  matrix2(0, 2) = 24.0;
  matrix2(1, 0) = 21.0;
  matrix2(1, 1) = 15.0;
  matrix2(1, 2) = 24.0;
  matrix2(2, 0) = 0;
  matrix2(2, 1) = 27.0;
  matrix2(2, 2) = 3.0;
  S21Matrix result(3, 3);
  result(0, 0) = 576.0;
  result(0, 1) = 945.0;
  result(0, 2) = 774.0;
  result(1, 0) = 378.0;
  result(1, 1) = 675.0;
  result(1, 2) = 477.0;
  result(2, 0) = 261.0;
  result(2, 1) = 810.0;
  result(2, 2) = 819.0;
  S21Matrix res = matrix1 * matrix2;
  EXPECT_TRUE(res.EqMatrix(result));
}

TEST(MatrixTest, MulNumberOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 9.0;
  S21Matrix result(2, 2);
  result(0, 0) = 7.5;
  result(0, 1) = 15.0;
  result(1, 0) = 17.5;
  result(1, 1) = 22.5;
  S21Matrix res = matrix1 * 2.5;
  EXPECT_TRUE(res.EqMatrix(result));
}

TEST(MatrixTest, OperatorEq) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1(0, 0) = 1.;
  matrix2(0, 0) = 1.;
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(MatrixTest, OperatorEq2) {
  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 5.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 6.0;
  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 5.0;
  matrix2(2, 0) = 3.0;
  matrix2(2, 1) = 6.0;
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(MatrixTest, OperatorEq3) {
  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 5.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 6.0;
  S21Matrix matrix2 = matrix1;
  EXPECT_TRUE(matrix2.EqMatrix(matrix1));
}

TEST(MatrixTest, OperatorPlusEq) {
  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 5.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 6.0;
  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 5.0;
  matrix2(2, 0) = 3.0;
  matrix2(2, 1) = 6.0;
  S21Matrix result(3, 2);
  result(0, 0) = 2.0;
  result(0, 1) = 8.0;
  result(1, 0) = 4.0;
  result(1, 1) = 10.0;
  result(2, 0) = 6.0;
  result(2, 1) = 12.0;
  EXPECT_TRUE(result.EqMatrix(matrix2 += matrix1));
}

TEST(MatrixTest, OperatorMinusEq) {
  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 5.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 6.0;
  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 5.0;
  matrix2(2, 0) = 3.0;
  matrix2(2, 1) = 6.0;
  S21Matrix result(3, 2);
  EXPECT_TRUE(result.EqMatrix(matrix2 -= matrix1));
}

TEST(MatrixTest, OperatorMulNumberEq) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 9.0;
  S21Matrix result(2, 2);
  result(0, 0) = 7.5;
  result(0, 1) = 15.0;
  result(1, 0) = 17.5;
  result(1, 1) = 22.5;
  EXPECT_TRUE(result.EqMatrix(matrix1 *= 2.5));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}