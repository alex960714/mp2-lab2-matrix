#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m(5);
	TMatrix<int> m1(m);

	EXPECT_EQ(m, m1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory) //???
{
	TMatrix<int> m(5);
	TMatrix<int> m1(m);

	EXPECT_NE(&m[0],&m1[0]);
}

TEST(TMatrix, can_get_size) 
{
	const int size = 5;
	TMatrix<int> m(size);

	EXPECT_EQ(size, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	const int size = 5;
	TMatrix<int> m(size);
	m[2][3] = 2;

	EXPECT_EQ(2, m[2][3]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(4);

	ASSERT_ANY_THROW(m[-2][3] = 3);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(4);

	ASSERT_ANY_THROW(m[2][5] = 1);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	const int size = 4;
	TMatrix<int> m(size);
	m[0][2] = 4;
	m[3][3] = 1;
	m = m;

	ASSERT_NO_THROW(m = m);
	EXPECT_NE(0, m[0][2]);
	EXPECT_NE(0, m[3][3]);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	const int size = 4;
	TMatrix<int> m(size),m1(size);
	for (int i = 0; i < size - 1; i++)
		m[i][i + 1] = 2;
	m1 = m;

	EXPECT_EQ(m, m1);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	const int size1 = 3, size2 = 5;
	TMatrix<int> m(size1), m1(size2);
	m[1][2] = 1;
	m[2][2] = 4;
	m1 = m;

	EXPECT_EQ(size1, m1.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	const int size1 = 3, size2 = 5;
	TMatrix<int> m(size1), m1(size2);
	m[1][2] = 1;
	m[2][2] = 4;
	m1 = m;

	EXPECT_NE(0, m1[1][2]);
	EXPECT_NE(0, m1[2][2]);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	const int size = 3;
	TMatrix<int> m(size), m1(size);
	m[1][2] = 1;
	m[2][2] = 4;
	m1 = m;

	EXPECT_EQ(true, m1 == m);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	const int size = 3;
	TMatrix<int> m(size);
	m[0][1] = 1;
	m[2][2] = 4;

	EXPECT_EQ(true, m == m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	const int size1 = 3, size2 = 5;
	TMatrix<int> m(size1), m1(size2);

	EXPECT_EQ(true, m1 != m);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	const int size = 3;
	TMatrix<int> m(size), m1(size), m2(size),m3(size);
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
		{
			m[i][j] = 1;
			m1[i][j] = 2;
			m2[i][j] = 3;
		}
	m3 = m + m1;

	EXPECT_EQ(m2, m3);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	const int size1 = 3, size2 = 5;
	TMatrix<int> m(size1), m1(size2);

	ASSERT_ANY_THROW(m + m1);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	const int size = 3;
	TMatrix<int> m(size), m1(size), m2(size), m3(size);
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
		{
			m[i][j] = 5;
			m1[i][j] = 2;
			m2[i][j] = 3;
		}
	m3 = m - m1;

	EXPECT_EQ(m2, m3);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	const int size1 = 3, size2 = 5;
	TMatrix<int> m(size1), m1(size2);

	ASSERT_ANY_THROW(m - m1);
}

