#ifndef SJO_IMPL_ITERATOR_TRAITS_HEADER
#define SJO_IMPL_ITERATOR_TRAITS_HEADER

#include <type_traits>
#include <iterator>

namespace sjo
{

namespace impl
{

template <typename T>
struct void_if_exists
{
	using type = void;
};

template <typename T, typename = void>
struct iterator_category_of
{
	using type = void;
};

template <typename T>
struct iterator_category_of <T, typename sjo::impl::void_if_exists <typename std::iterator_traits <T>::iterator_category>::type>
{
	using type = typename std::iterator_traits <T>::iterator_category;
};



template <typename T>
struct is_input_iterator
	: std::is_base_of <std::input_iterator_tag,
	                   typename sjo::impl::iterator_category_of <T>::type>
{
};

template <typename T>
struct is_output_iterator
	: std::is_base_of <std::output_iterator_tag,
	                   typename sjo::impl::iterator_category_of <T>::type>
{
};

template <typename T>
struct is_forward_iterator
	: std::is_base_of <std::forward_iterator_tag,
	                   typename sjo::impl::iterator_category_of <T>::type>
{
};

template <typename T>
struct is_bidirectional_iterator
	: std::is_base_of <std::bidirectional_iterator_tag,
	                   typename sjo::impl::iterator_category_of <T>::type>
{
};

template <typename T>
struct is_random_access_iterator
	: std::is_base_of <std::random_access_iterator_tag,
	                   typename sjo::impl::iterator_category_of <T>::type>
{
};

} // namespace sjo::impl

} // namespace sjo

#endif // SJO_IMPL_ITERATOR_TRAITS_HEADER
