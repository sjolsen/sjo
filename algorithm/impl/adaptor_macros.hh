#ifndef SJO_ALGORITHM_IMPL_ADAPTOR_MACROS_HEADER
#define SJO_ALGORITHM_IMPL_ADAPTOR_MACROS_HEADER

#define SJO_ALGORITHM_IRANGE_UNARY_ADAPTOR(NAME_, RETTYPE_)                     \
template <class Rangeable, class Predicate = sjo::is_true>                      \
inline RETTYPE_                                                                 \
NAME_ (Rangeable _rangeable,                                                    \
       Predicate _pred = Predicate {})                                          \
{										\
	auto _range = sjo::range (_rangeable);                                  \
	return sjo::NAME_ (_range.begin (), _range.end (), std::move (_pred));  \
}                                                                               \
                                                                                \
/* Initializer list overload */                                                 \
template <class T, class Predicate = sjo::is_true>                              \
inline RETTYPE_                                                                 \
NAME_ (const std::initializer_list <T>& _list, Predicate _pred = Predicate {})  \
{                                                                               \
	return sjo::NAME_ (sjo::range (_list), std::move (_pred));              \
}



#define SJO_ALGORITHM_IRANGE_IRANGE_BINARY_ADAPTOR(NAME_, RETTYPE_)             \
/* Range overload */                                                            \
template <class InputIterator1, class InputIterator2,                           \
          class BinaryOperator = sjo::equal_to>                                 \
inline RETTYPE_                                                                 \
NAME_ (sjo::range_wrapper_type <InputIterator1> _range1,                        \
       sjo::range_wrapper_type <InputIterator2> _range2,                        \
       BinaryOperator _pred = BinaryOperator {})                                \
{                                                                               \
	return sjo::NAME_ (_range1.begin (), _range1.end (),                    \
	                   _range2.begin (), _range2.end (),                    \
	                   std::move (_pred));                                  \
}                                                                               \
                                                                                \
/* Container overload */                                                        \
template <class InputIterator1, class Container2,                               \
          class BinaryOperator = sjo::equal_to>                                 \
inline RETTYPE_                                                                 \
NAME_ (sjo::range_wrapper_type <InputIterator1> _range1,                        \
       const Container2& _container2,                                           \
       BinaryOperator _pred = BinaryOperator {})                                \
{                                                                               \
	return sjo::NAME_ (std::move (_range1),                                 \
	                   sjo::range (_container2),                            \
	                   std::move (_pred));                                  \
}                                                                               \
                                                                                \
template <class Container1, typename... Rest>                                   \
inline RETTYPE_                                                                 \
NAME_ (const Container1& _container1, Rest&&... _rest)                          \
{                                                                               \
	return sjo::NAME_ (sjo::range (_container1),                            \
	                   std::forward <Rest> (_rest)...);                     \
}                                                                               \
                                                                                \
/* Initializer list overload */                                                 \
template <class InputIterator1, class T2,                                       \
          class BinaryOperator = sjo::equal_to>                                 \
inline RETTYPE_                                                                 \
NAME_ (sjo::range_wrapper_type <InputIterator1> _range1,                        \
       const std::initializer_list <T2>& _list2,                                \
       BinaryOperator _pred = BinaryOperator {})                                \
{                                                                               \
	return sjo::NAME_ (std::move (_range1),                                 \
	                   sjo::range (_list2),                                 \
	                   std::move (_pred));                                  \
}                                                                               \
                                                                                \
template <class T1, typename... Rest>                                           \
inline RETTYPE_                                                                 \
NAME_ (const std::initializer_list <T1>& _list1, Rest&&... _rest)               \
{                                                                               \
	return sjo::NAME_ (sjo::range (_list1),                                 \
	                   std::forward <Rest> (_rest)...);                     \
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

#define SJO_ALGORITHM_IRANGE_OITER_COMPARATOR_COPY_ADAPTOR(NAME_)               \
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
