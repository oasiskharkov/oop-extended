#include "container.h"

Container::Container(std::initializer_list<int> values) :
    m_size{ values.size() },
    m_data(new int[m_size], [](int* p) { delete[] p; })
{
    std::copy(values.begin(), values.end(), m_data.get());
}

Container::iterator Container::begin()
{
    return iterator(m_data.get());
}

Container::iterator Container::end()
{
    return iterator(m_data.get() + m_size);
}

Container::const_iterator Container::begin() const
{
    return const_iterator(m_data.get());
}

Container::const_iterator Container::end() const
{
    return const_iterator(m_data.get() + m_size);
}

int Container::operator[](const int index)
{
    return m_data[index];
}

size_t Container::size() const
{
    return m_size;
}

