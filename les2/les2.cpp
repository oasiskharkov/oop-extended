#include <iostream>
#include <vector>
#include <algorithm>

#include "fileReader.h"
#include "timer.h"

template <typename T>
void Swap(T*& left, T*& right)
{
	std::swap(left, right);
}

template <typename T>
void SortPointers(std::vector<T*>& vec)
{
	std::sort(std::begin(vec), std::end(vec), [](const auto& left, const auto& right) -> bool { return *left < *right; });
}

class A
{
private:
	int a;
public:
	A(int _a) : a{ _a } {}
	int get() const { return a; }
	bool operator < (const A& obj) const { return a < obj.a; }
};

std::ostream& operator << (std::ostream& out, const A& obj)
{
	out << obj.get();
	return out;
}

int main()
{
	// ====== TASK #1 ======
	int* a = new int{ 2 };
	int* b = new int{ 3 };
	std::cout << "a=" << *a << std::endl;
	std::cout << "b=" << *b << std::endl;

	Swap(a, b);

	std::cout << "a=" << *a << std::endl;
	std::cout << "b=" << *b << std::endl;

	delete a;
	delete b;

	A* a1 = new A { 10 };
	A* b1 = new A { 20 };

	std::cout << "a1=" << a1->get() << std::endl;
	std::cout << "b1=" << b1->get() << std::endl;

	Swap(a1, b1);

	std::cout << "a1=" << a1->get() << std::endl;
	std::cout << "b1=" << b1->get() << std::endl;

	delete a1;
	delete b1;

	// ====== TASK #2 ======
	int* x = new int{ 10 };
	int* y = new int{ 20 };
	int* z = new int{ 30 };
	int* w = new int{ 40 };
	int* v = new int{ 50 };

	std::vector<int*> vec{ x, v, w, z, y };

	for (const auto& elem : vec)
	{
		std::cout << *elem << ' ';
	}
	std::cout << std::endl;

	SortPointers(vec);

	for (const auto& elem : vec)
	{
		std::cout << *elem << ' ';
	}
	std::cout << std::endl;

	delete x;
	delete y;
	delete z;
	delete w;
	delete v;

	A* x1 = new A{ 1 };
	A* y1 = new A{ 2 };
	A* z1 = new A{ 3 };
	A* w1 = new A{ 4 };
	A* v1 = new A{ 5 };

	std::vector<A*> vec1{ x1, v1, w1, z1, y1 };

	for (const auto& elem : vec1)
	{
		std::cout << *elem << ' ';
	}
	std::cout << std::endl;

	SortPointers(vec1);

	for (const auto& elem : vec1)
	{
		std::cout << *elem << ' ';
	}
	std::cout << std::endl;

	delete x1;
	delete y1;
	delete z1;
	delete w1;
	delete v1;

	// ====== TASK #3 ======
	try
	{
		FileReader fr{ "War_and_Peace.txt" };

		Timer t("count_if");
		std::cout << "Vowels count = " << fr.CounFirst() << std::endl;
		t.print();

		t.start("for");
		std::cout << "Vowels count = " << fr.CountSecond() << std::endl;
		t.print();

		t.start("find_first_of");
		std::cout << "Vowels count = " << fr.CountThird() << std::endl;
		t.print();

		t.start("getline");
		std::cout << "Vowels count = " << fr.CountFourth("War_and_Peace.txt") << std::endl;
		t.print();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	
	return 0;
}


