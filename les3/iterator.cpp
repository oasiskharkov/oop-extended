#ifdef _ITERATOR_H_

template<typename ValueType>
Iterator<ValueType>::Iterator(ValueType* p) :
    p{ p }
{

}

template<typename ValueType>
Iterator<ValueType>::Iterator(const Iterator& it) :
    p{ it.p }
{

}

template<typename ValueType>
bool Iterator<ValueType>::operator != (Iterator const& other) const
{
    return p != other.p;
}

template<typename ValueType>
bool Iterator<ValueType>::operator == (Iterator const& other) const
{
    return p == other.p;
}

template<typename ValueType>
Iterator<ValueType>& Iterator<ValueType>::operator ++ ()
{
    ++p;
    return *this;
}

#endif // _ITERATOR_H_

