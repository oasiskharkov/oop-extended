#ifdef _MATRIX_H_

template<typename T, size_t Size>
Matrix<T, Size>::Matrix()
{
	// invariant checking
	if (Size < minSize)
	{
		throw std::logic_error("Incorrect matrix size");
	}

	m_matrix.resize(Size * Size);
	std::generate(std::begin(m_matrix), std::end(m_matrix), []() { return rand() % 10; });
}

template<typename T, size_t Size>
void Matrix<T, Size>::print() const
{
	for (auto i = 0; i < Size; ++i)
	{
		for (auto j = 0; j < Size; ++j)
		{
			std::cout << std::setw(3) << m_matrix[i * Size + j];
		}
		std::cout << std::endl;
	}
}

template<typename T, size_t Size>
T Matrix<T, Size>::determinant() const
{
    return determinant_cross(m_matrix, Size);
}

template<typename T, size_t Size>
T Matrix<T, Size>::determinant_cross(const std::vector<T>& vec, const size_t size) const
{
	if (size == minSize)
	{
		return vec[0] * vec[3] - vec[1] * vec[2];
	}
	else
	{
		T det = 0;
		for (size_t j = 0; j < size; ++j)
		{
			std::vector<T> cross;
			for (size_t i = 1; i < size; ++i)
			{
				for (size_t k = 0; k < size; ++k)
				{
					if (k != j)
					{
						cross.emplace_back(vec[i * size + k]);
					}
				}
			}

			if (j % 2 == 0)
			{
				det += vec[j] * determinant_cross(cross, size - 1);
			}
			else
			{
				det -= vec[j] * determinant_cross(cross, size - 1);
			}
		}
		return det;
	}
}

#endif // _MATRIX_H_