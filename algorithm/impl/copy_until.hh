#ifndef SJO_ALGORITHM_IMPL_COPY_UNTIL_HEADER
#define SJO_ALGORITHM_IMPL_COPY_UNTIL_HEADER

#include <sjo/impl/iterator_traits.hh>

namespace sjo
{

template <typename InputIterator, typename OutputIterator, typename UnaryPredicate>
inline typename std::enable_if <sjo::impl::is_input_iterator <InputIterator>::type,
                                std::pair <InputIterator, OutputIterator>>::type
copy_until (InputIterator in_begin, InputIterator in_end, OutputIterator out_begin,
            UnaryPredicate is_delimiter)
{
	while (in_begin != in_end)
	{
		if (is_delimiter (*in_begin))
			return {std::move (in_begin), std::move (out_begin)};
		else
		{
			*out_begin = *in_begin;
			++in_begin;
			++out_begin;
		}
	}
	return {std::move (in_begin), std::move (out_begin)};
}

} // namespace sjo

#endif // SJO_ALGORITHM_IMPL_COPY_UNTIL_HEADER
