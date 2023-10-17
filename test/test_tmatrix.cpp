#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(5), c = m;
  EXPECT_EQ(m, c);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(5), c = m;
  EXPECT_NE(&m[0][0], &c[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  constexpr size_t size = 5;
  TDynamicMatrix<int> m(size);
  EXPECT_EQ(size, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(m[1][1] = 111);
  EXPECT_EQ(m[1][1], 111);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(5);
  EXPECT_ANY_THROW(m.at(0).at(-1) = 1);
  EXPECT_ANY_THROW(m.at(-1).at(0) = 1);
  EXPECT_ANY_THROW(m.at(-1).at(-1) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  constexpr size_t size = 5;
  TDynamicMatrix<int> m(size);
  EXPECT_ANY_THROW(m.at(0).at(size) = 1);
  EXPECT_ANY_THROW(m.at(size).at(0) = 1);
  EXPECT_ANY_THROW(m.at(size).at(size) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(5), m2;
  ASSERT_NO_THROW(m1 = m2);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  constexpr size_t size = 5;
  TDynamicMatrix<int> m1(size), m2(size + 1);
  m1 = m2;
  EXPECT_EQ((size + 1), m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  constexpr size_t size = 5;
  TDynamicMatrix<int> m1(size), m2(size + 1);
  ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(5);
  m1[0][0] = 1;
  m1[0][3] = 2;
  m1[3][0] = 3;
  auto m2 = TDynamicMatrix<int>(m1);

  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m1(5);
  m1[0][0] = 1;
  m1[0][3] = 2;
  m1[3][0] = 3;

  EXPECT_EQ(m1, m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  constexpr size_t size = 5;
  TDynamicMatrix<int> m1(size), m2(size + 1);
  EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  constexpr size_t size = 5;

  TDynamicMatrix<int> m1(size);
  m1[0][0] = 1;
  m1[1][1] = 2;
  m1[2][2] = 3;
  m1[3][3] = 4;
  m1[4][4] = 5;

  TDynamicMatrix<int> m2(size);
  m2[0][4] = 1;
  m2[1][3] = 2;
  m2[2][2] = 3;
  m2[3][1] = 4;
  m2[4][0] = 5;

  TDynamicMatrix<int> res;
  ASSERT_NO_THROW(res = m1 + m2);

  EXPECT_EQ(6, res[2][2]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  constexpr size_t size = 5;
  TDynamicMatrix<int> m1(size), m2(size + 1);
  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  constexpr size_t size = 5;

  TDynamicMatrix<int> m1(size);
  m1[0][0] = 1;
  m1[1][1] = 2;
  m1[2][2] = 50;
  m1[3][3] = 4;
  m1[4][4] = 5;

  TDynamicMatrix<int> m2(size);
  m2[0][4] = 1;
  m2[1][3] = 2;
  m2[2][2] = 55;
  m2[3][1] = 4;
  m2[4][0] = 5;

  TDynamicMatrix<int> res;
  ASSERT_NO_THROW(res = m1 - m2);

  EXPECT_EQ(-5, res[2][2]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  constexpr size_t size = 5;
  TDynamicMatrix<int> m1(size), m2(size + 1);
  ASSERT_ANY_THROW(m1 - m2);
}
