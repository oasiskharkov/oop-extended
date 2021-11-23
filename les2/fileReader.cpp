#include "fileReader.h"

FileReader::FileReader(const std::string& filePath)
{
	std::ifstream in(filePath);
	if(in.is_open())
	{
		std::string word;
		while (in.good())
		{
			in >> word;
			std::transform(word.begin(), word.end(), word.begin(), std::tolower);
			m_words.emplace_back(std::move(word));
		}
		in.close();
	}
	else
	{
		throw std::logic_error("Can't open input file: " + filePath);
	}
}

int FileReader::CounFirst() const
{
	int sum = 0;
	for (const auto& word : m_words)
	{
		sum += std::count_if(word.begin(), word.end(), [this](char symbol) { return this->IsVowel(symbol); });
	}
	return sum;
}

int FileReader::CountSecond() const
{
	int sum = 0;
	for (const auto& word : m_words)
	{
		for (size_t i = 0; i < word.length(); ++i)
		{
			if (IsVowel(word[i]))
			{
				++sum;
			}
		}
	}
	return sum;
}

int FileReader::CountThird() const
{
	int sum = 0;
	for (const auto& word : m_words)
	{
		std::size_t pos = 0;
		while ((pos = word.find_first_of("aeiou", pos)) != std::string::npos)
		{
			++pos;
			++sum;
		}
	}
	return sum;
}

int FileReader::CountFourth(const std::string& filePath) const
{
	std::ifstream in(filePath);
	int sum = 0;
	if (in.is_open())
	{
		std::string line;
		while (getline(in, line))
		{
			std::size_t pos = 0;
			std::transform(line.begin(), line.end(), line.begin(), std::tolower);
			while ((pos = line.find_first_of("aeiou", pos)) != std::string::npos)
			{
				++pos;
				++sum;
			}
		}
		in.close();
		return sum;
	}
	else
	{
		throw std::logic_error("Can't open input file: " + filePath);
	}
}

bool FileReader::IsVowel(char symbol) const
{
	return m_vowels.find(symbol) != m_vowels.end();
}
