#include "phoneBook.h"

PhoneBook::PhoneBook(std::ifstream& in)
{
	if (in.is_open())
	{
		std::string surname;
		std::string name;
		std::string patronymic;

		int countryCode;
		int cityCode;
		std::string number;
		std::string addNumber;

		while (!in.eof())
		{
			in >> surname >> name >> patronymic >> countryCode >> cityCode >> number >> addNumber;
			std::optional <std::string> patr;
			if (patronymic != "-")
			{
				patr = patronymic;
			}
			std::optional <int> add;
			if (addNumber != "-")
			{
				add = std::stoi(addNumber);
			}

			m_phoneBook.emplace_back(Person{ surname, name, patr }, PhoneNumber{ countryCode, cityCode, number, add });
		}
		in.close();
	}
}

void PhoneBook::SortByName()
{
	std::sort(std::begin(m_phoneBook), std::end(m_phoneBook),
		[](const auto& a, const auto& b) { return a.first < b.first; });
}

void PhoneBook::SortByPhone()
{
	std::sort(std::begin(m_phoneBook), std::end(m_phoneBook),
		[](const auto& a, const auto& b) { return a.second < b.second; });
}

std::tuple<std::string, std::optional<PhoneNumber>> PhoneBook::GetPhoneNumber(const std::string& surname) const
{
	std::vector<std::pair<Person, PhoneNumber>> result;
	std::copy_if(std::begin(m_phoneBook), std::end(m_phoneBook), std::back_inserter(result),
		[surname](const auto& record) { return record.first.m_surname == surname; });
	
	if (0 == result.size())
	{
		return std::tie("not found", std::nullopt);
	}
	else if (1 == result.size())
	{
	    return std::tie("", result[0].second);
	}
	else
	{
		return std::tie("found more than 1", std::nullopt);
	}
}

void PhoneBook::ChangePhoneNumber(const Person& person, const PhoneNumber& number)
{
	auto it = std::find_if(std::begin(m_phoneBook), std::end(m_phoneBook),
		[person](const auto& record) { return record.first == person; });

	if (it != m_phoneBook.end())
	{
		it->second = number;
	}
}
