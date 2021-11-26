#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

namespace
{
	constexpr size_t minSize = 2;
}

template <typename T, size_t Size>
class Matrix
{
public:
	Matrix();
	void print() const;
	T determinant() const;
private:
	std::vector<T> m_matrix;
	T determinant_cross(const std::vector<T>& vec, const size_t size) const;
};

#include "matrix.cpp"

#endif // _MATRIX_H_