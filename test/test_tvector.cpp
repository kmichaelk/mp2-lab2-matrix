#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> v(5), c = v;
  EXPECT_EQ(v, c);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(5), c = v;
  EXPECT_NE(&v[0], &c[0]);
}

TEST(TDynamicVector, can_get_size)
{
  constexpr size_t size = 5;
  TDynamicVector<int> v(size);
  EXPECT_EQ(size, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(5);
  ASSERT_NO_THROW(v[1] = 111);
  EXPECT_EQ(v[1], 111);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(5);
  EXPECT_ANY_THROW(v.at(-1) = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  constexpr size_t size = 5;
  TDynamicVector<int> v(size);
  EXPECT_ANY_THROW(v.at(size) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(5);
  ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v1(5), v2;
  ASSERT_NO_THROW(v1 = v2);
  EXPECT_EQ(v1.size(), v2.size());
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  constexpr size_t size = 5;
  TDynamicVector<int> v1(size), v2(size + 1);
  v1 = v2;
  EXPECT_EQ((size + 1), v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  constexpr size_t size = 5;
  TDynamicVector<int> v1(size), v2(size + 1);
  ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v1(5);
  v1[0] = 1;
  v1[0] = 2;
  v1[3] = 3;
  auto v2 = TDynamicVector<int>(v1);

  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v1(5);
  v1[0] = 1;
  v1[0] = 2;
  v1[3] = 3;

  EXPECT_EQ(v1, v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  constexpr size_t size = 5;
  TDynamicVector<int> v1(size), v2(size + 1);
  EXPECT_NE(v1, v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  constexpr size_t size = 5;

  TDynamicVector<int> v1(size);
  v1[2] = 3;

  TDynamicVector<int> res;
  ASSERT_NO_THROW(res = v1 + 7);

  EXPECT_EQ(10, res[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  constexpr size_t size = 5;

  TDynamicVector<int> v1(size);
  v1[2] = 13;

  TDynamicVector<int> res;
  ASSERT_NO_THROW(res = v1 - 3);

  EXPECT_EQ(10, res[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  constexpr size_t size = 5;

  TDynamicVector<int> v(size);
  v[2] = 3;

  TDynamicVector<int> res;
  ASSERT_NO_THROW(res = v * 2);

  EXPECT_EQ(6, res[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  constexpr size_t size = 5;

  TDynamicVector<int> v1(size);
  v1[2] = 3;

  TDynamicVector<int> v2(size);
  v2[2] = 3;

  TDynamicVector<int> res;
  ASSERT_NO_THROW(res = v1 + v2);

  EXPECT_EQ(6, res[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  constexpr size_t size = 5;
  TDynamicVector<int> v1(size), v2(size + 1);
  ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  constexpr size_t size = 5;

  TDynamicVector<int> v1(size);
  v1[2] = 13;

  TDynamicVector<int> v2(size);
  v2[2] = 3;

  TDynamicVector<int> res;
  ASSERT_NO_THROW(res = v1 - v2);

  EXPECT_EQ(10, res[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  constexpr size_t size = 5;
  TDynamicVector<int> v1(size), v2(size + 1);
  ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  constexpr size_t size = 1;

  TDynamicVector<int> v1(size);
  v1[0] = 3;

  TDynamicVector<int> v2(size);
  v2[0] = 4;

  int res;
  ASSERT_NO_THROW(res = v1 * v2);

  EXPECT_EQ(12, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  constexpr size_t size = 5;
  TDynamicVector<int> v1(size), v2(size + 1);
  ASSERT_ANY_THROW(v1 * v2);
}
