#ifndef SJO_ALGORITHM_IMPL_ANY_OF_HEADER
#define SJO_ALGORITHM_IMPL_ANY_OF_HEADER

#include <sjo/impl/iterator_traits.hh>

namespace sjo
{

template <class InputIterator, class Predicate>
inline typename std::enable_if <sjo::impl::is_input_iterator <InputIterator>::value,
                                bool>::type
any_of (InputIterator _first, InputIterator _last, Predicate _pred)
{
	while (_first != _last)
	{
		if (_pred (*_first))
			return true;
		else
			++_first;
	}
	return false;
}

}

#endif // SJO_ALGORITHM_IMPL_ANY_OF_HEADER
