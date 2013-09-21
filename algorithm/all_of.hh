#ifndef SJO_ALGORITHM_ALL_OF_HEADER
#define SJO_ALGORITHM_ALL_OF_HEADER

#include <sjo/range.hh>
#include <sjo/comp_ops.hh>

namespace sjo
{

template <class InputIterator, class Predicate = sjo::is_true>
inline bool
all_of (InputIterator _first, InputIterator _last,
        Predicate _pred = Predicate {})
{
	while (_first != _last)
	{
		if (!_pred (*_first))
			return false;
		else
			++_first;
	}
	return true;
}



// Range overload
template <class InputIterator, class Predicate = sjo::is_true>
inline bool
all_of (sjo::range_wrapper_type <InputIterator> _range,
        Predicate _pred = Predicate {})
{
	return sjo::all_of (_range.begin (), _range.end (), std::move (_pred));
}

// Container overload
template <class Container, class Predicate = sjo::is_true>
inline bool
all_of (const Container& _container, Predicate _pred = Predicate {})
{
	return sjo::all_of (sjo::range (_container), std::move (_pred));
}

// Initializer list overload
template <class T, class Predicate = sjo::is_true>
inline bool
all_of (const std::initializer_list <T>& _list, Predicate _pred = Predicate {})
{
	return sjo::all_of (sjo::range (_list), std::move (_pred));
}

} // namespace sjo

#endif // SJO_ALGORITHM_ALL_OF_HEADER
