#include "fileReader.h"

FileReader::FileReader(const std::string& filePath)
{
	std::ifstream in(filePath);
	if(in.is_open())
	{
		std::istream_iterator<std::string> start{ in };
		std::istream_iterator<std::string> end;
		std::copy(start, end, std::ostream_iterator<std::string>(m_ss));
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
	while (!m_ss.eof())
	{
		std::string word;
		m_ss >> word;
		sum += std::count_if(word.begin(), word.end(), [this](char symbol) { return this->IsVowel(std::tolower(symbol)); });
	}
	m_ss.seekg(0);
	return sum;
}

int FileReader::CountSecond() const
{
	int sum = 0;
	while (!m_ss.eof())
	{
		std::string word;
		m_ss >> word;
		for (size_t i = 0; i < word.length(); ++i)
		{
			if (IsVowel(std::tolower(word[i])))
			{
				++sum;
			}
		}
	}
	m_ss.seekg(0);
	return sum;
}

int FileReader::CountThird() const
{
	int sum = 0;
	while (!m_ss.eof())
	{
		std::string word;
		m_ss >> word;
		std::size_t pos = 0;
		std::transform(word.begin(), word.end(), word.begin(), std::tolower);
		while ((pos = word.find_first_of("aeiou", pos)) != std::string::npos)
		{
			++pos;
			++sum;
		}
	}
	m_ss.seekg(0);
	return sum;
}

int FileReader::CountFourth(const std::string& filePath) const
{
	std::ifstream in(filePath);
	int sum = 0;
	if (in.is_open())
	{
		std::string word;
		while (in.good())
		{
			in >> word;
			std::size_t pos = 0;
			std::transform(word.begin(), word.end(), word.begin(), std::tolower);
			while ((pos = word.find_first_of("aeiou", pos)) != std::string::npos)
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

int FileReader::CountFifth(const std::string& filePath) const
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
