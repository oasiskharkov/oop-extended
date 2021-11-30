#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <string>
#include <fstream>
#include <map>

template <typename Iter, typename ValueType>
void print_uniques(Iter first, Iter last)
{
    std::set<ValueType> uniques(first, last);
    std::copy(uniques.begin(), uniques.end(), std::ostream_iterator<ValueType>(std::cout, " "));
    std::cout << std::endl;
}

int main()
{
    // ====== TASK #1 ======
    std::vector<std::string> words1{ "test", "check", "set", "iterator", "map", "iterator", "container", "test", "check", "test", "set", "unordered" };
    print_uniques<std::vector<std::string>::iterator, std::string>(words1.begin(), words1.end());
    print_uniques<std::vector<std::string>::const_iterator, std::string>(words1.cbegin(), words1.cend());
    print_uniques<std::vector<std::string>::reverse_iterator, std::string>(words1.rbegin(), words1.rend());
    print_uniques<std::vector<std::string>::const_reverse_iterator, std::string>(words1.crbegin(), words1.crend());

    std::string arr[12] = { "test", "check", "set", "iterator", "map", "iterator", "container", "test", "check", "test", "set", "unordered" };
    print_uniques<std::string*, std::string>(&arr[0], &arr[12]);
    print_uniques<const std::string*, std::string>(&arr[0], &arr[12]);

    // ====== TASK #2 ======
    std::string fileName{ "Text.txt" };
    std::ifstream in{fileName};

    std::multimap<size_t, std::string> dict;
    if (in.is_open())
    {
        std::string text{ std::istreambuf_iterator<char>{in}, {} };
        size_t start{ 0 };
        while ((start = text.find_first_not_of(" .!?\n\t", start)) != std::string::npos)
        {
            std::string sentence;
            size_t end = text.find_first_of(".!?", start);
            if (end == std::string::npos)
            {
                sentence = text.substr(start, text.length() - start);
            }
            else
            {
                sentence = text.substr(start, end - start);
            }
            start = end;
            dict.emplace(sentence.length(), sentence);
        }
        in.close();

        for (const auto& elem : dict)
        {
            std::cout << elem.second << std::endl;
        }
    }
    else
    {
        std::cerr << "Can't open file " + fileName << std::endl;
    }

    return 0;
}