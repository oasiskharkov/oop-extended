#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <string_view>
#include <string>
#include <algorithm>
#include <set>

class FileReader
{
public:
	FileReader(const std::string& filePath);
	int CounFirst() const;
	int CountSecond() const;
	int CountThird() const;
	int CountFourth(const std::string& filePath) const;
	int CountFifth(const std::string& filePath) const;
	bool IsVowel(char symbol) const;
private:
	mutable std::stringstream m_ss;
	std::set<char> m_vowels{ 'a','e','i','o','u' };
};

