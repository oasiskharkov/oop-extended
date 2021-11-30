#pragma once

#include "iterator.h"

#include <memory>
#include <functional>

class Container
{
public:
    typedef Iterator<int> iterator;
    typedef Iterator<const int> const_iterator;

    Container(std::initializer_list<int> values);

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    int operator [] (const int index);
    size_t size() const;
private:
    const size_t m_size;
    std::unique_ptr<int[], std::function<void(int*)>> m_data;
};

