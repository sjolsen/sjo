// -*- mode: c++; -*-

#ifndef SJO_ALGO_STD_ALGORITHM_IMPL_EQUAL_HEADER
#define SJO_ALGO_STD_ALGORITHM_IMPL_EQUAL_HEADER

#include <sjo/impl/iterator_traits.hh>

namespace sjo
{

template <class InputIterator1, class InputIterator2, class BinaryOperator>
inline bool
equal_common (InputIterator1& _first1, const InputIterator1& _last1,
              InputIterator2& _first2, const InputIterator2& _last2,
              BinaryOperator& _pred)
{
	while (_first1 != _last1 && _first2 != _last2)
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

template <class InputIterator1, class InputIterator2, class BinaryOperator>
inline typename std::enable_if < sjo::impl::is_input_iterator         <InputIterator1>::value &&
                                !sjo::impl::is_random_access_iterator <InputIterator1>::value &&
                                 sjo::impl::is_input_iterator         <InputIterator2>::value &&
                                !sjo::impl::is_random_access_iterator <InputIterator2>::value,
                                bool>::type
equal (InputIterator1 _first1, InputIterator1 _last1,
       InputIterator2 _first2, InputIterator2 _last2,
       BinaryOperator _pred)
{
	bool common_part_equal = sjo::equal_common (_first1, _last1,
	                                            _first2, _last2,
	                                            _pred);
	return common_part_equal && _first1 == _last1 && _first2 == _last2;
}

template <class RandomAccessIterator1, class RandomAccessIterator2,
          class BinaryOperator>
inline typename std::enable_if <sjo::impl::is_random_access_iterator <RandomAccessIterator1>::value &&
                                sjo::impl::is_random_access_iterator <RandomAccessIterator2>::value,
                                bool>::type
equal (RandomAccessIterator1 _first1, RandomAccessIterator1 _last1,
       RandomAccessIterator2 _first2, RandomAccessIterator2 _last2,
       BinaryOperator _pred)
{
	if (_last1 - _first1 != _last2 - _first2)
		return false;
	return sjo::equal_common (_first1, _last1,
	                          _first2, _last2,
	                          _pred);
}

} // namespace sjo

#endif // SJO_ALGO_STD_ALGORITHM_IMPL_EQUAL_HEADER
