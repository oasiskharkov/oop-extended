#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <iterator>

template<typename ValueType>
class Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
    friend class Container;
private:
    Iterator(ValueType* p);
public:
    Iterator(const Iterator& it);

    bool operator != (Iterator const& other) const;
    bool operator == (Iterator const& other) const;

    typename Iterator::reference operator * () const
    {
        return *p;
    }
    Iterator& operator ++ ();
private:
    ValueType* p;
};

#include "iterator.cpp"

#endif // _ITERATOR_H_
