// -*- mode: c++; -*-

#ifndef SJO_ALGO_STD_ALGORITHM_FOR_EACH_HEADER
#define SJO_ALGO_STD_ALGORITHM_FOR_EACH_HEADER

#include <sjo/range>

namespace sjo
{

// Requires MoveConstructible {Function}
template <class InputIterator, class Function>
inline Function
for_each (InputIterator _first, InputIterator _last, Function _function)
{
	while (_first != _last)
	{
		_function (*_first);
		++_first;
	}
	return std::move (_function);
}

template <class InputIterator, class Function>
inline Function
for_each (sjo::range_wrapper_type <InputIterator> _range, Function _function)
{
	return sjo::for_each (_range.begin (), _range.end (), std::move (_function));
}

} // namespace sjo

#endif // SJO_ALGO_STD_ALGORITHM_FOR_EACH_HEADER\
