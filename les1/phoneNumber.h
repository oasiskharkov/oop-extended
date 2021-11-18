#pragma once

#include "stdafx.h"

struct PhoneNumber
{
	int m_countryCode;
	int m_cityCode;
	std::string m_number;
	std::optional<int> m_addNumber;

	bool operator < (const PhoneNumber& number) const
	{
		auto self = std::tie(m_countryCode, m_cityCode, m_number, m_addNumber);
		auto other = std::tie(number.m_countryCode, number.m_cityCode, number.m_number, number.m_addNumber);
		return self < other;
	}

	bool operator == (const PhoneNumber& number) const
	{
		return !(*this < number) && !(number < *this);
	}
};

inline std::ostream& operator << (std::ostream& out, const PhoneNumber& number)
{
	out << "+" << number.m_countryCode << "(" << number.m_cityCode << ")" << number.m_number << " " << 
		(number.m_addNumber.has_value() ? std::to_string(number.m_addNumber.value()) : "");
	return out;
}