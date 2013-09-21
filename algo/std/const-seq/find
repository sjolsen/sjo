// -*- mode: c++; -*-

#ifndef SJO_ALGO_STD_ALGORITHM_FIND_HEADER
#define SJO_ALGO_STD_ALGORITHM_FIND_HEADER

#include <sjo/range>

namespace sjo
{

template <class InputIterator, class T>
inline InputIterator
find (InputIterator _first, InputIterator _last, const T& _value)
{
	while (_first != _last)
	{
		if (*_first == _value)
			return _first;
		else
			++_first;
	}
	return _first;
}

template <class InputIterator, class T>
inline InputIterator
find (sjo::range_wrapper_type <InputIterator> _range, const T& _value)
{
	return sjo::find (_range.begin (), _range.end (), _value);
}

} // namespace sjo

#endif // SJO_ALGO_STD_ALGORITHM_FIND_HEADER
