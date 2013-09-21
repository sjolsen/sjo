// -*- mode: c++; -*-

#ifndef SJO_ALGO_STD_ALGORITHM_NONE_OF_HEADER
#define SJO_ALGO_STD_ALGORITHM_NONE_OF_HEADER

#include <sjo/range>

namespace sjo
{

template <class InputIterator, class Predicate>
inline bool
none_of (InputIterator _first, InputIterator _last, Predicate _pred)
{
	while (_first != _last)
	{
		if (_pred (*_first))
			return false;
		else
			++_first;
	}
	return true;
}

template <class InputIterator, class Predicate>
inline bool
none_of (sjo::range_wrapper_type <InputIterator> _range, Predicate _pred)
{
	return sjo::none_of (_range.begin (), _range.end (), std::move (_pred));
}

} // namespace sjo

#endif // SJO_ALGO_STD_ALGORITHM_NONE_OF_HEADER
