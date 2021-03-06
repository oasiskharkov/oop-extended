#pragma once

#include <iostream>
#include <mutex>

class Pcout
{
public:
	template <typename T>
	friend Pcout& operator << (Pcout& out, const T& value)
	{
		std::unique_lock<std::mutex> ul{ out.mtx };
		std::cout << value;
		return out;
	}
private:
	std::mutex mtx;
};

extern Pcout pcout;