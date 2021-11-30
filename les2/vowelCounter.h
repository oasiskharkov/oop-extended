#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

class VowelCounter 
{
public:
	VowelCounter(const std::string& filePath);
	int CounFirst() const;
	int CountSecond() const;
	int CountThird() const;
	int CountFourth(const std::string& filePath) const;
	bool IsVowel(char symbol) const;
private:
	std::vector<std::string> m_words;
	std::unordered_set<char> m_vowels{ 'a','e','i','o','u' };
};

