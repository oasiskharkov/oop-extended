#pragma once

#include <iostream>
#include <chrono>

class Timer
{
public:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;
public:
	Timer() :
		Timer{ "" }
	{}

	Timer(const std::string& name) :
		m_name{ name },
		m_beg{ clock_t::now() }
	{}

	void start(const std::string& name)
	{
		m_name = name;
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}

	void print() const
	{
		std::cout << m_name << " = " << elapsed() * 1000 << " ms" << std::endl;
	}

private:
	std::string m_name;
	std::chrono::time_point<clock_t> m_beg;
};
