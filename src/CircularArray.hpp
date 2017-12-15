#ifndef _CIRCULAR_ARRAY_HPP
#define _CIRCULAR_ARRAY_HPP_

#include <stdint.h>
#include <vector>
#include <iterator>

#include <iostream>

template <class T>
class CircularArray
{
public:
	CircularArray();

	~CircularArray();

	void setSize(uint32_t _size);

	bool isFull();

	bool isValid(typename std::vector<T>::iterator _it);

	void setInvalid(typename std::vector<T>::iterator _it);

	typename std::vector<T>::iterator insert();

	typename std::vector<T>::iterator begin();

	typename std::vector<T>::iterator end();

private:
	uint32_t maxSize;
	uint32_t index;
	uint32_t n;
	std::vector<T> carray;
	std::vector<bool> valid;
};

template <class T>
CircularArray<T>::CircularArray()
{
}

template <class T>
CircularArray<T>::~CircularArray()
{
}

template <class T> void
CircularArray<T>::setSize(uint32_t _size)
{
	maxSize = _size;
	index = 0;
	n = 0;

	carray.resize(maxSize);
	valid.resize(maxSize);

	for (auto it = valid.begin(); it != valid.end(); ++it) {
		*it = false;
	}
}

template <class T> bool
CircularArray<T>::isFull() {
	return n == maxSize;
}

template <class T> bool 
CircularArray<T>::isValid(typename std::vector<T>::iterator _it)
{
	return valid[_it - carray.begin()];
}

template <class T> void 
CircularArray<T>::setInvalid(typename std::vector<T>::iterator _it)
{
	valid[_it - carray.begin()] = false;
	--n;
}

template <class T> typename std::vector<T>::iterator 
CircularArray<T>::insert()
{
	while (valid[index]) {
		index = (index + 1) % maxSize;
	}

	valid[index] = true;
	++n;

	return carray.begin() + index;
}

template <class T> typename std::vector<T>::iterator 
CircularArray<T>::begin()
{
	return carray.begin();
}

template <class T> typename std::vector<T>::iterator 
CircularArray<T>::end()
{
	return carray.end();
}

#endif
