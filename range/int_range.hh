#ifndef SJO_RANGE_INT_RANGE_HEADER
#define SJO_RANGE_INT_RANGE_HEADER

#include <iterator>
#include "range_wrapper.hh"

namespace sjo
{

template <typename Integer>
struct int_iterator
	: std::iterator <std::input_iterator_tag,
	                 Integer,
	                 decltype (Integer {} - Integer {})>
{
	using iterator = std::iterator <std::input_iterator_tag,
	                 Integer,
                         decltype (Integer {} - Integer {})>;

	using typename iterator::value_type;
	using typename iterator::difference_type;
	using typename iterator::pointer;
	using typename iterator::reference;
	using typename iterator::iterator_category;

	value_type _value;

	constexpr
	int_iterator (value_type value)
		: _value (value)
	{
	}

	int_iterator& operator ++()
	{
		++_value;
		return *this;
	}

	constexpr
	value_type operator *()
	{
		return _value;
	}

	constexpr
	bool operator == (int_iterator other)
	{
		return _value == other._value;
	}

	constexpr
	bool operator != (int_iterator other)
	{
		return _value != other._value;
	}
};

// range_wrapper_type <int_iterator <Integral>>
// range (Integral first, Integral last)
// {
// 	return {first, last};
// }

#define SJO_DEFINE_RANGE_INT(type)                                              \
inline constexpr                                                                \
range_wrapper_type <int_iterator <type>> range (type first,                     \
                                                type last)                      \
{                                                                               \
	return {first, last};                                                   \
}

// Overload for all integral types
SJO_DEFINE_RANGE_INT (bool)

SJO_DEFINE_RANGE_INT (char)
SJO_DEFINE_RANGE_INT (signed char)
SJO_DEFINE_RANGE_INT (unsigned char)

SJO_DEFINE_RANGE_INT (wchar_t)
SJO_DEFINE_RANGE_INT (char16_t)
SJO_DEFINE_RANGE_INT (char32_t)

SJO_DEFINE_RANGE_INT (short int)
SJO_DEFINE_RANGE_INT (unsigned short int)

SJO_DEFINE_RANGE_INT (int)
SJO_DEFINE_RANGE_INT (unsigned int)

SJO_DEFINE_RANGE_INT (long int)
SJO_DEFINE_RANGE_INT (unsigned long int)

SJO_DEFINE_RANGE_INT (long long int)
SJO_DEFINE_RANGE_INT (unsigned long long int)

} // namespace sjo

#endif // SJO_RANGE_INT_RANGE_HEADER
