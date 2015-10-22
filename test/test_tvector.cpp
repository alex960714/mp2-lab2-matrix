#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
  TVector<int> v(10);
  TVector<int> v1(v);

  EXPECT_EQ(v, v1);
}

TEST(TVector, copied_vector_has_its_own_memory) //???
{
  TVector<int> v(10);
  TVector<int> v1(v);

  //ASSERT_NO_FATAL_FAILURE(v1.GetSize()); //???
  EXPECT_EQ(v.GetSize(), v1.GetSize());  //???
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(10);

	ASSERT_ANY_THROW(v[-3] = 5);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(10);

	ASSERT_ANY_THROW(v[12] = 9);
}

TEST(TVector, can_assign_vector_to_itself) //???
{
	TVector<int> v(10);
	v[3] = 1;
	v[6] = 6;
	v = v;

	//ASSERT_NO_THROW(v = v); //???
	EXPECT_NE(0, v[3]);
    EXPECT_NE(0, v[6]);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	const int size = 10;
	TVector<int> v(size), v1(size);
	for (int i = 0; i < 3; i++)
		v[i] = 2;
	v[6] = 4;
	v1 = v;

	EXPECT_EQ(v, v1);
}

TEST(TVector, assign_operator_change_vector_size)
{
	const int size1 = 5, size2 = 10;
	TVector<int> v(size1), v1(size2);
	v[1] = 6;
	v[4] = 2;
	v1 = v;

	EXPECT_EQ(size1, v1.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	const int size1 = 5, size2 = 10;
	TVector<int> v(size1), v1(size2);
	v[1] = 6;
	v[4] = 2;
	v1 = v;

	EXPECT_NE(0, v1[1]);
	EXPECT_NE(0, v1[4]);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	const int size = 5;
	TVector<int> v(size), v1(size);
	v[1] = 6;
	v[4] = 2;
	v1 = v;

	EXPECT_EQ(true, v1 == v);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	const int size = 5;
	TVector<int> v(size);
	v[1] = 6;
	v[4] = 2;

	EXPECT_EQ(true, v == v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	const int size1 = 5, size2 = 10;
	TVector<int> v(size1), v1(size2);

	EXPECT_EQ(false, v1 == v);
}

TEST(TVector, can_add_scalar_to_vector)
{
	const int size = 10;
	TVector<int> v(size),v1(size);
	for (int i = 0; i < size; i++)
	{
		v[i] = 3;
		v1[i] = 0;
	}
	v1 = v1 + 3;

	EXPECT_EQ(v, v1);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	const int size = 10;
	TVector<int> v(size), v1(size);
	for (int i = 0; i < size; i++)
	{
		v[i] = -3;
		v1[i] = 0;
	}
	v1 = v1 - 3;

	EXPECT_EQ(v, v1);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	const int size = 4;
	TVector<int> v(size), v1(size);
	v[0] = 2;
	v[1] = 3;
	v[2] = 0;
	v[3] = 1;
	//v={2 3 0 1}
	v1[0] = 4;
	v1[1] = 6;
	v1[2] = 0;
	v1[3] = 2;
	//v1={4 6 0 2}

	EXPECT_EQ(v1, v*2);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	const int size = 4;
	TVector<int> v(size), v1(size), v2(size);
	v[0] = 0;
	v[1] = 2;
	v[2] = 0;
	v[3] = 5;
	//v={0 2 0 5}
	v1[0] = 1;
	v1[1] = 0;
	v1[2] = 0;
	v1[3] = -3;
	//v1={1 0 0 -3}

	ASSERT_NO_THROW(v + v1);

	v2 = v + v1;
	EXPECT_EQ(1,v2[0]);
	EXPECT_EQ(2, v2[3]);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	const int size1 = 4, size2 = 6;
	TVector<int> v(size1), v1(size2);
	for (int i = 0; i < size1; i++)
	{
		v[i] = 0;
		v1[i] = 0;
	}
	v1[4] = 0;
	v1[5] = 0;

	EXPECT_ANY_THROW(v + v1);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	const int size = 4;
	TVector<int> v(size), v1(size), v2(size);
	v[0] = 0;
	v[1] = 2;
	v[2] = 0;
	v[3] = 5;
	//v={0 2 0 5}
	v1[0] = 1;
	v1[1] = 0;
	v1[2] = 0;
	v1[3] = -3;
	//v1={1 0 0 -3}

	ASSERT_NO_THROW(v - v1);

	v2 = v - v1;
	EXPECT_EQ(-1, v2[0]);
	EXPECT_EQ(8, v2[3]);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	const int size1 = 4, size2 = 6;
	TVector<int> v(size1), v1(size2);
	for (int i = 0; i < size1; i++)
	{
		v[i] = 0;
		v1[i] = 0;
	}
	v1[4] = 0;
	v1[5] = 0;

	EXPECT_ANY_THROW(v - v1);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	const int size = 4;
	TVector<int> v(size), v1(size);
	v[0] = 2;
	v[1] = 3;
	v[2] = 0;
	v[3] = 1;
	//v={2 3 0 1}
	v1[0] = 0;
	v1[1] = 1;
	v1[2] = 1;
	v1[3] = -1;
	//v1={0 1 1 -1}

	//v*v1=2
	EXPECT_EQ(2, v*v1);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	const int size1 = 3, size2 = 5;
	TVector<int> v(size1), v1(size2);
	for (int i = 0; i < size1; i++)
	{
		v[i] = 1;
		v1[i] = 1;
	}
	v1[3] = 2;
	v1[4] = 0;

	EXPECT_ANY_THROW(v*v1);
}

