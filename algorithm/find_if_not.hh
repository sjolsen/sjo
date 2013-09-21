// -*- mode: c++; -*-

#ifndef SJO_ALGO_STD_ALGORITHM_FIND_IF_NOT_HEADER
#define SJO_ALGO_STD_ALGORITHM_FIND_IF_NOT_HEADER

#include <sjo/range>

namespace sjo
{

template <class InputIterator, class Predicate = sjo::impl::is_true>
inline InputIterator
find_if_not (InputIterator _first, InputIterator _last,
             Predicate _pred = Predicate {})
{
	while (_first != _last)
	{
		if (!_pred (*_first))
			return _first;
		else
			++_first;
	}
	return _first;
}

template <class InputIterator, class Predicate = sjo::impl::is_true>
inline InputIterator
find_if_not (sjo::range_wrapper_type <InputIterator> _range,
             Predicate _pred = Predicate {})
{
	return sjo::find_if_not (_range.begin (), _range.end (), std::move (_pred));
}

} // namespace sjo

#endif // SJO_ALGO_STD_ALGORITHM_FIND_IF_NOT_HEADER
