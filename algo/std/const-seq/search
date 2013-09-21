// -*- mode: c++; -*-

#ifndef SJO_ALGO_STD_ALGORITHM_SEARCH_HEADER
#define SJO_ALGO_STD_ALGORITHM_SEARCH_HEADER

#include <sjo/range>
#include <sjo/algo/std/const-seq/equal>
#include "impl/comp_ops"

namespace sjo
{

// Searches for the first subsequence of [_first1, _last1) which is equal to the
// sequence [_first2, _last2).
template <class ForwardIterator1, class ForwardIterator2,
          class BinaryOperator = sjo::impl::equal_to>
inline ForwardIterator1
search (ForwardIterator1 _first1, ForwardIterator1 _last1,
        ForwardIterator2 _first2, ForwardIterator2 _last2,
        BinaryOperator _pred = BinaryOperator {})
{
	if (_first2 == _last2)
		return _first1;

	while (_first1 != _last1)
	{
		if (*_first1 != *_first2)
		{
			++_first1;
			continue;
		}

		auto _first1_local = _first1;
		auto _first2_local = _first2;
		auto common_part_equal = sjo::impl::equal (_first1_local, _last1,
		                                           _first2_local, _last2,
		                                           _pred);
		if (!common_part_equal)
		{
			++_first1;
			continue;
		}

		// If we hit _last1 without hitting _last2, we didn't match the
		// whole of [_first2, _last2), and cannot with a later _first1.
		if (_first1_local == _last1 && _first2_local != _last2)
			return _last1;

		// The common part is equal and we matched all of [_first2, _last2),
		// so we have found a matching subsequence of [_first1, _last1).
		return _first1_local;
	}

	// No match.
	return _last1;
}

template <class ForwardIterator1, class ForwardIterator2,
          class BinaryOperator = sjo::impl::equal_to>
inline ForwardIterator1
search (sjo::range_wrapper_type <ForwardIterator1> _range1,
        sjo::range_wrapper_type <ForwardIterator2> _range2,
        BinaryOperator _pred = BinaryOperator {})
{
	return sjo::search (_range1.begin (), _range1.end (),
	                    _range2.begin (), _range2.end (),
	                    std::move (_pred));
}

} // namespace sjo

#endif // SJO_ALGO_STD_ALGORITHM_SEARCH_HEADER
