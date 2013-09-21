#ifndef SJO_RANGE_RANGE_WRAPPER_HEADER
#define SJO_RANGE_RANGE_WRAPPER_HEADER

#include <utility>

namespace sjo
{

template <typename Iterator>
struct range_wrapper_type
{
	Iterator _begin;
	Iterator _end;

	constexpr
	range_wrapper_type (Iterator first, Iterator last = Iterator {})
		: _begin (std::move (first)),
		  _end (std::move (last))
	{
	}

	constexpr
	Iterator begin () const
	{
		return _begin;
	}

	constexpr
	Iterator end () const
	{
		return _end;
	}
};

template <typename Iterator>
inline
range_wrapper_type <Iterator> range (Iterator first, Iterator last)
{
	return range_wrapper_type <Iterator> (std::move (first),
	                                      std::move (last));
}

} // namespace sjo

#endif // SJO_RANGE_RANGE_WRAPPER_HEADER
