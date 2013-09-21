#ifndef SJO_ALGORITHM_IMPL_COPY_SPLIT_HEADER
#define SJO_ALGORITHM_IMPL_COPY_SPLIT_HEADER

#include <sjo/impl/iterator_traits.hh>
#include "copy_until.hh"

namespace sjo
{

template <typename InputIterator, typename OutputIterator, typename UnaryPredicate>
inline typename std::enable_if <sjo::impl::is_input_iterator <InputIterator>::value,
                                std::pair <InputIterator, OutputIterator>>::type
copy_split (InputIterator in_begin, InputIterator in_end, OutputIterator out_begin,
            UnaryPredicate is_delimiter)
{
	while (in_begin != in_end)
	{
		in_begin = sjo::copy_until (in_begin, in_end,
		                            *out_begin, is_delimiter).first;
		++out_begin;

		if (in_begin == in_end)
			return {std::move (in_begin), std::move (out_begin)};
		else
			++in_begin;
	}
}

} // namespace sjo

#endif // SJO_ALGORITHM_IMPL_COPY_SPLIT_HEADER
