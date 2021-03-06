#pragma once

#include "person.h"
#include "phoneNumber.h"

class PhoneBook
{
public:
	PhoneBook(std::ifstream& in);
	friend std::ostream& operator << (std::ostream& out, const PhoneBook& book);
	void SortByName();
	void SortByPhone();
	std::tuple<std::string, std::optional<PhoneNumber>> GetPhoneNumber(const std::string& surname) const;
	void ChangePhoneNumber(const Person& person, const PhoneNumber& number);
	std::pair<Person, PhoneNumber> operator [] (int index) const;
private:
	std::vector<std::pair<Person, PhoneNumber>> m_phoneBook;
};

inline std::ostream& operator << (std::ostream& out, const PhoneBook& book)
{
	for (const auto& record : book.m_phoneBook)
	{
		out << record.first << '\t' << record.second << std::endl;
	}
	return out;
}