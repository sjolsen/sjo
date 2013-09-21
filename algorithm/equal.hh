// -*- mode: c++; -*-

#ifndef SJO_ALGO_STD_ALGORITHM_EQUAL_HEADER
#define SJO_ALGO_STD_ALGORITHM_EQUAL_HEADER

#include <sjo/range>
#include "impl/equal"
#include "impl/comp_ops"

namespace sjo
{

template <class InputIterator1, class InputIterator2,
          class BinaryOperator = sjo::impl::equal_to>
inline bool
equal (InputIterator1 _first1, InputIterator1 _last1,
       InputIterator2 _first2,
       BinaryOperator _pred = BinaryOperator {})
{
	while (_first1 != _last1)
	{
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



// FIXME: Optimize the case for random-access iterators
template <class InputIterator1, class InputIterator2,
          class BinaryOperator = sjo::impl::equal_to>
inline bool
equal (InputIterator1 _first1, InputIterator1 _last1,
       InputIterator2 _first2, InputIterator2 _last2,
       BinaryOperator _pred = BinaryOperator {})
{
	bool common_part_equal = sjo::impl::equal (_first1, _last1,
	                                           _first2, _last2,
	                                           std::move (_pred));
	if (!common_part_equal)
		return false;
	if (_first1 != _last1 || _first2 != _last2)
		return false;

	return true;
}

template <class InputIterator1, class InputIterator2,
          class BinaryOperator = sjo::impl::equal_to>
inline bool
equal (sjo::range_wrapper_type <InputIterator1> _range1,
       sjo::range_wrapper_type <InputIterator2> _range2,
       BinaryOperator _pred = BinaryOperator {})
{
	return sjo::equal (_range1.begin (), _range1.end (),
	                   _range2.begin (), _range2.end (),
	                   std::move (_pred));
}

} // namespace sjo

#endif // SJO_ALGO_STD_ALGORITHM_EQUAL_HEADER
