#ifndef SJO_ALGORITHM_IMPL_ADAPTOR_MACROS_HEADER
#define SJO_ALGORITHM_IMPL_ADAPTOR_MACROS_HEADER

#define SJO_ALGORITHM_IRANGE_UNARY_ADAPTOR(NAME_)                               \
/* Range overload */                                                            \
template <class InputIterator, class Predicate = sjo::is_true>                  \
inline bool                                                                     \
NAME_ (sjo::range_wrapper_type <InputIterator> _range,                          \
       Predicate _pred = Predicate {})                                          \
{                                                                               \
	return sjo::NAME_ (_range.begin (), _range.end (), std::move (_pred));  \
}                                                                               \
                                                                                \
/* Container overload */                                                        \
template <class Container, class Predicate = sjo::is_true>                      \
inline bool                                                                     \
NAME_ (const Container& _container, Predicate _pred = Predicate {})             \
{                                                                               \
	return sjo::NAME_ (sjo::range (_container), std::move (_pred));         \
}                                                                               \
                                                                                \
/* Initializer list overload */                                                 \
template <class T, class Predicate = sjo::is_true>                              \
inline bool                                                                     \
NAME_ (const std::initializer_list <T>& _list, Predicate _pred = Predicate {})  \
{                                                                               \
	return sjo::NAME_ (sjo::range (_list), std::move (_pred));              \
}



#define SJO_ALGORITHM_IRANGE_OITER_UNARY_COPY_ADAPTOR(NAME_)                    \
/* Range overload */                                                            \
template <typename InputIterator, typename OutputIterator,                      \
          typename UnaryPredicate = sjo::is_true>                               \
inline std::pair <InputIterator, OutputIterator>                                \
NAME_ (sjo::range_wrapper_type <InputIterator> in_range,                        \
            OutputIterator out_begin,                                           \
            UnaryPredicate is_delimiter = UnaryPredicate {})                    \
{                                                                               \
	return sjo::NAME_ (in_range.begin (), in_range.end (),                  \
	                   std::move (out_begin),                               \
	                   std::move (is_delimiter));                           \
}                                                                               \
                                                                                \
/* Container overload */                                                        \
template <typename Container, typename OutputIterator,                          \
          typename UnaryPredicate = sjo::is_true>                               \
inline std::pair <typename Container::const_iterator, OutputIterator>           \
NAME_ (const Container& in_container,                                           \
            OutputIterator out_begin,                                           \
            UnaryPredicate is_delimiter = UnaryPredicate {})                    \
{                                                                               \
	return sjo::NAME_ (sjo::range (in_container),                           \
	                   std::move (out_begin),                               \
	                   std::move (is_delimiter));                           \
}                                                                               \
                                                                                \
/* Initializer list overload */                                                 \
template <typename T, typename OutputIterator,                                  \
          typename UnaryPredicate = sjo::is_true>                               \
inline std::pair <typename std::initializer_list <T>::const_iterator,           \
                  OutputIterator>                                               \
NAME_ (const std::initializer_list <T>& in_list,                                \
            OutputIterator out_begin,                                           \
            UnaryPredicate is_delimiter = UnaryPredicate {})                    \
{                                                                               \
	return sjo::NAME_ (sjo::range (in_list),                                \
	                   std::move (out_begin),                               \
	                   std::move (is_delimiter));                           \
}

#define SJO_ALGORITHM_IRANGE_OITER_UNARY_COMPARATOR_ADAPTOR(NAME_)              \
/* Range overload */                                                            \
template <typename InputIterator, typename OutputIterator, typename Delimiter>  \
inline std::pair <InputIterator, OutputIterator>                                \
NAME_ (sjo::range_wrapper_type <InputIterator> in_range,                        \
       OutputIterator out_begin,                                                \
       const Delimiter& delimiter)                                              \
{                                                                               \
	return sjo::NAME_ (in_range.begin (), in_range.end (),                  \
	                   std::move (out_begin),                               \
	                   sjo::make_comparator (delimiter));                   \
}                                                                               \
                                                                                \
/* Container overload */                                                        \
template <typename Container, typename OutputIterator, typename Delimiter>      \
inline std::pair <typename Container::const_iterator, OutputIterator>           \
NAME_ (const Container& in_container,                                           \
       OutputIterator out_begin,                                                \
       const Delimiter& delimiter)                                              \
{                                                                               \
	return sjo::NAME_ (sjo::range (in_container),                           \
	                   std::move (out_begin),                               \
	                   sjo::make_comparator (delimiter));                   \
}                                                                               \
                                                                                \
/* Initializer list overload */                                                 \
template <typename T, typename OutputIterator, typename U>                      \
inline std::pair <typename std::initializer_list <T>::const_iterator,           \
                  OutputIterator>                                               \
NAME_ (const std::initializer_list <T>& in_list,                                \
       OutputIterator out_begin,                                                \
       const U& delimiter)                                                      \
{                                                                               \
	return sjo::NAME_ (sjo::range (in_list),                                \
	                   std::move (out_begin),                               \
	                   sjo::make_comparator (delimiter));                   \
}


#endif // SJO_ALGORITHM_IMPL_ADAPTOR_MACROS_HEADER
