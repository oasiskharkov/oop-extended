#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <tuple>
#include <optional>

struct Person
{
	std::string m_surname;
	std::string m_name;
	std::optional <std::string> m_patronymic;

	bool operator < (const Person& person) const
	{
		auto self = std::tie(m_surname, m_name, m_patronymic);
		auto pers = std::tie(person.m_surname, person.m_name, person.m_patronymic);
		return self < pers;
	}

	bool operator == (const Person& person) const
	{
		return !(*this < person) && !(person < *this);
	}
};

inline std::ostream& operator << (std::ostream& out, const Person& person)
{
	out << std::setw(13) << person.m_surname << std::setw(13) << person.m_name << std::setw(16) << person.m_patronymic.value_or("");
	return out;
}