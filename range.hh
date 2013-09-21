#ifndef SJO_RANGE_HEADER
#define SJO_RANGE_HEADER

#include <sjo/range/range_wrapper.hh>
#include <sjo/range/int_range.hh>

namespace sjo
{

template <typename Container>
inline sjo::range_wrapper_type <typename Container::iterator>
range (Container& _container)
{
	using std::begin;
	using std::end;
	return {begin (_container), end (_container)};
}

template <typename Container>
inline sjo::range_wrapper_type <typename Container::const_iterator>
range (const Container& _container)
{
	using std::begin;
	using std::end;
	return {begin (_container), end (_container)};
}

template <typename T>
inline sjo::range_wrapper_type <typename std::initializer_list <T>::iterator>
range (const std::initializer_list <T>& _list)
{
	return {_list.begin (), _list.end ()};
}



// Overload for std::istream et al.
template <typename T, typename CharT>
inline sjo::range_wrapper_type <std::istream_iterator <T>>
range (std::basic_istream <CharT>& is)
{
	return {std::istream_iterator <T> (is), {}};
}

template <typename CharT>
inline sjo::range_wrapper_type <std::istreambuf_iterator <CharT>>
range (std::basic_istream <CharT>& is)
{
	return {std::istreambuf_iterator <CharT> (is), {}};
}

} // namespace sjo

#endif // SJO_RANGE_HEADER
