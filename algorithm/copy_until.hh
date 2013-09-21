#ifndef SJO_ALGORITHM_COPY_UNTIL_HEADER
#define SJO_ALGORITHM_COPY_UNTIL_HEADER

#include <sjo/comp_ops.hh>
#include <sjo/range.hh>

namespace sjo
{

template <typename InputIterator, typename OutputIterator,
          typename UnaryPredicate = sjo::is_true>
inline std::pair <InputIterator, OutputIterator>
copy_until (InputIterator in_begin, InputIterator in_end, OutputIterator out_begin,
            UnaryPredicate is_delimiter = UnaryPredicate {})
{
	while (in_begin != in_end && !is_delimiter (*in_begin))
		*out_begin++ = *in_begin++;
	return {in_begin, out_begin};
}

template <typename InputIterator, typename OutputIterator, typename Delimiter>
inline std::pair <InputIterator, OutputIterator>
copy_until (InputIterator in_begin, InputIterator in_end, OutputIterator out_begin,
            const Delimiter& delimiter)
{
	return sjo::copy_until (std::move (in_begin), std::move (in_end),
	                        std::move (out_begin),
	                        sjo::make_comparator (delimiter));
}



// Range overload
template <typename InputIterator, typename OutputIterator,
          typename UnaryPredicate = sjo::is_true>
inline std::pair <InputIterator, OutputIterator>
copy_until (sjo::range_wrapper_type <InputIterator> in_range,
            OutputIterator out_begin,
            UnaryPredicate is_delimiter = UnaryPredicate {})
{
	return sjo::copy_until (in_range.begin (), in_range.end (),
	                        std::move (out_begin),
	                        std::move (is_delimiter));
}

template <typename InputIterator, typename OutputIterator, typename Delimiter>
inline std::pair <InputIterator, OutputIterator>
copy_until (sjo::range_wrapper_type <InputIterator> in_range,
            OutputIterator out_begin,
            const Delimiter& delimiter)
{
	return sjo::copy_until (in_range.begin (), in_range.end (),
	                        std::move (out_begin),
	                        sjo::make_comparator (delimiter));
}

// Container overload
template <typename Container, typename OutputIterator,
          typename UnaryPredicate = sjo::is_true>
inline std::pair <typename Container::const_iterator, OutputIterator>
copy_until (const Container& in_container,
            OutputIterator out_begin,
            UnaryPredicate is_delimiter = UnaryPredicate {})
{
	return sjo::copy_until (sjo::range (in_container),
	                        std::move (out_begin),
	                        std::move (is_delimiter));
}

template <typename Container, typename OutputIterator, typename Delimiter>
inline std::pair <typename Container::const_iterator, OutputIterator>
copy_until (const Container& in_container,
            OutputIterator out_begin,
            const Delimiter& delimiter)
{
	return sjo::copy_until (sjo::range (in_container),
	                        std::move (out_begin),
	                        sjo::make_comparator (delimiter));
}

// Initializer list overload
template <typename T, typename OutputIterator,
          typename UnaryPredicate = sjo::is_true>
inline std::pair <typename std::initializer_list <T>::const_iterator, OutputIterator>
copy_until (const std::initializer_list <T>& in_list,
            OutputIterator out_begin,
            UnaryPredicate is_delimiter = UnaryPredicate {})
{
	return sjo::copy_until (sjo::range (in_list),
	                        std::move (out_begin),
	                        std::move (is_delimiter));
}

template <typename T, typename OutputIterator, typename U>
inline std::pair <typename std::initializer_list <T>::const_iterator, OutputIterator>
copy_until (const std::initializer_list <T>& in_list,
            OutputIterator out_begin,
            const U& delimiter)
{
	return sjo::copy_until (sjo::range (in_list),
	                        std::move (out_begin),
	                        sjo::make_comparator (delimiter));
}

} // namespace sjo

#endif // SJO_ALGORITHM_COPY_UNTIL_HEADER
