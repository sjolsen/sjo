// -*- mode: c++; -*-

#ifndef SJO_ALGO_STD_ALGORITHM_IMPL_EQUAL_HEADER
#define SJO_ALGO_STD_ALGORITHM_IMPL_EQUAL_HEADER

#include "comp_ops"

namespace sjo
{

namespace impl
{

// This version of equal compares the common subset of the two ranges; it differs
// from std::equal in that it will not return false because of a size difference.
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool
equal (InputIterator1& _first1, const InputIterator1& _last1,
       InputIterator2& _first2, const InputIterator2& _last2,
       BinaryPredicate&& _pred)
{
	while (_first1 != _last1 && _first2 != _last2)
	{
		// Should we forward for operator () &&?
		if (!_pred (*_first1, *_first2))
			return false;
		else
		{
			++_first1;
			++_first2;
		}
	}
	return true;
}

template <class InputIterator1, class InputIterator2>
inline bool
equal (InputIterator1& _first1, const InputIterator1& _last1,
       InputIterator2& _first2, const InputIterator2& _last2)
{
	return sjo::impl::equal (_first1, _last1,
	                         _first2, _last2,
	                         sjo::impl::equal_to ());
}

} // namespace sjo::impl

} // namespace sjo

#endif // SJO_ALGO_STD_ALGORITHM_IMPL_EQUAL_HEADER
