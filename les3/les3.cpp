#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>

#include "matrix.h"
#include "container.h"

void push_back_avarage_to_list(std::list<float>& list)
{
    if (list.empty())
    {
        throw std::logic_error("List is empty.");
    }
    list.emplace_back(std::accumulate(std::begin(list), std::end(list), 0.f) / list.size());
}

int main()
{
    try
    {
		// ====== TASK #1 ======
		std::list<float> list{ 2.78f, 3.14f, 1.72f, 5.25f, 7.36f, 9.21f };
		push_back_avarage_to_list(list);

        std::copy(list.begin(), list.end(), std::ostream_iterator<float>(std::cout, " "));
        std::cout << std::endl;

		// ====== TASK #2 ======
		srand(static_cast<unsigned>(time(nullptr)));
    
        Matrix<int, 2> m2;
        m2.print();
        std::cout << "Determinant = " << m2.determinant() << std::endl;

        Matrix<int, 3> m3;
        m3.print();
        std::cout << "Determinant = " << m3.determinant() << std::endl;

        Matrix<int, 4> m4;
        m4.print();
        std::cout << "Determinant = " << m4.determinant() << std::endl;

        Matrix<int, 5> m5;
        m5.print();
        std::cout << "Determinant = " << m5.determinant() << std::endl;

        Matrix<int, 6> m6;
        m6.print();
        std::cout << "Determinant = " << m6.determinant() << std::endl;

        Matrix<int, 7> m7;
        m7.print();
        std::cout << "Determinant = " << m7.determinant() << std::endl;

        // ====== TASK #3 ======
        Container c{ 10, 2, 3, 4, 8, 5, 7, 6, 1, 0, 9 };
        std::copy(c.begin(), c.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}

