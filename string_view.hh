#ifndef STRING_VIEW_HH
#define STRING_VIEW_HH

#include <string>
#include <limits>
#include <stdexcept>

#ifdef __GLIBCXX__
# include <bits/stl_algobase.h> // min, max
#else
# include <algorithm>
#endif



namespace sjo
{

template <typename charT>
constexpr inline
std::size_t strlen (const charT* str)
{
	std::size_t len = 0;
	while (*str != '\0')
		++len, ++str;
	return len;
}


// [basic.string.view], basic_string_view:

template <typename charT,
          typename traits = std::char_traits <charT> >
class basic_string_view
{
public:
	// types
	using value_type             = charT;
	using pointer                = const charT*;
	using const_pointer          = const charT*;
	using reference              = const charT&;
	using const_reference        = const charT&;
	using iterator               = const charT*;
	using const_iterator         = const charT*;
	using reverse_iterator       = std::reverse_iterator <const_iterator>;
	using const_reverse_iterator = std::reverse_iterator <const_iterator>;
	using size_type              = std::size_t;
	using difference_type        = std::ptrdiff_t;

	static constexpr
	size_type npos = size_type {0} - 1;

private:
	pointer _begin;
	pointer _end;

protected:
	constexpr
	basic_string_view _substr (size_type pos, size_type n) const noexcept
	{
		return {_begin + pos, std::min (pos + n, this->length ())};
	}

	constexpr
	basic_string_view _substr (size_type pos) const noexcept
	{
		return _substr (pos, this->size () - pos);
	}

	constexpr
	bool _equal (basic_string_view str, size_type distance) const noexcept
	{
		return traits::compare (_begin, str._begin, distance) == 0;
	}

	constexpr
	bool _equal (basic_string_view str) const noexcept
	{
		return _equal (str, str.size ());
	}

public:

	// [string.view.cons], construct/copy
	constexpr
	basic_string_view (const basic_string_view& other) noexcept
		: _begin {other._begin},
		  _end   {other._end}
	{
	}

	constexpr
	basic_string_view& operator = (const basic_string_view& other) noexcept
	{
		_begin = other._begin;
		_end   = other._end;
		return *this;
	}

	constexpr
	basic_string_view () noexcept
		: _begin {nullptr},
		  _end   {nullptr}
	{
	}

	constexpr
	basic_string_view (const charT* str)
		: _begin {str},
		  _end   {str + strlen (str)}
	{
	}

	constexpr
	basic_string_view (const charT* str, size_type len)
		: _begin {str},
		  _end   {str + len}
	{
	}

	template <typename S_char, typename S_traits, typename S_alloc>
	basic_string_view (const std::basic_string <S_char, S_traits, S_alloc>& s) noexcept
		: _begin {s.begin ()},
		  _end   {s.end ()}
	{
	}

	// [string.view.iterators], iterators
	#define DEFINE_STRING_VIEW_GETTER(name, member)                         \
	constexpr                                                               \
	const_iterator name () const noexcept                                   \
	{                                                                       \
		return {member};                                                \
	}

	DEFINE_STRING_VIEW_GETTER (begin, _begin);
	DEFINE_STRING_VIEW_GETTER (cbegin, _begin);
	DEFINE_STRING_VIEW_GETTER (rbegin, _begin);
	DEFINE_STRING_VIEW_GETTER (crbegin, _begin);

	DEFINE_STRING_VIEW_GETTER (end, _end);
	DEFINE_STRING_VIEW_GETTER (cend, _end);
	DEFINE_STRING_VIEW_GETTER (rend, _end);
	DEFINE_STRING_VIEW_GETTER (crend, _end);

	#undef DEFINE_STRING_VIEW_GETTER

	// [string.view.capacity], capacity
	constexpr
	size_type size () const noexcept
	{
		return _end - _begin;
	}

	constexpr
	size_type length () const noexcept
	{
		return _end - _begin;
	}

	constexpr
	size_type max_size () const noexcept
	{
		return std::numeric_limits <decltype (_end)>::max () - std::numeric_limits <decltype (_begin)>::min ();
	}

	constexpr
	bool empty () const noexcept
	{
		return _begin == _end;
	}

	// [string.view.access], element access
	constexpr
	const charT& operator [] (size_type pos) const
	{
		return _begin [pos];
	}

	constexpr
	const charT& at (size_type pos) const
	{
		if (_begin == nullptr || _begin + pos >= _end)
			throw std::out_of_range ("basic_string_view");
		return _begin [pos];
	}

	constexpr
	const charT& front () const
	{
		return *_begin;
	}

	constexpr
	const charT& back () const
	{
		return *(_end - 1);
	}

	constexpr
	const charT* data () const noexcept
	{
		return _begin;
	}

	// [string.view.modifiers], modifiers:
	constexpr
	void clear () noexcept
	{
		_begin = _end = nullptr;
	}

	constexpr
	void remove_prefix (size_type n)
	{
		_begin += n;
	}

	constexpr
	void remove_suffix (size_type n)
	{
		_end -= n;
	}

	// [string.view.ops], string operations:
	constexpr
	basic_string_view substr (size_type pos, size_type n = npos) const
	{
		if (pos > this->size ())
			throw std::out_of_range ("basic_string_view");
		return _substr (pos, n);
	}

	constexpr
	int compare (basic_string_view s) const noexcept
	{
		auto rlen = std::min (this->size (), s.size ());

		int cmp = _equal (s, rlen);
		if (cmp != 0)
			return cmp;
		else
			return this->size () - s.size ();
	}

	constexpr
	int compare (const charT* s) const noexcept
	{
		return this->compare (basic_string_view {s});
	}

	constexpr
	bool starts_with (basic_string_view s) const noexcept
	{
		return this->size () >= s.size () && _equal (s);
	}

	constexpr
	bool starts_with (charT c) const noexcept
	{
		return traits::eq (this->front (), c);
	}

	constexpr
	bool starts_with (const charT* s) const noexcept
	{
		return this->starts_with (basic_string_view {s});
	}

	constexpr
	bool ends_with (basic_string_view s) const noexcept
	{
		return this->size () >= s.size () && _equal (_substr (this->size () - s.size ()), s);
	}

	constexpr
	bool ends_with (charT c) const noexcept
	{
		return traits::eq (this->back (), c);
	}

	constexpr
	bool ends_with (const charT* s) const noexcept
	{
		return this->ends_with (basic_string_view {s});
	}

	// find-like algorithms
	size_type find (basic_string_view s) const noexcept
	{
		for (size_type xpos = 0; xpos + s.size () <= this->size (); ++xpos)
			if (_substr (xpos).starts_with (s))
				return xpos;
		return npos;
	}

	size_type find (charT c) const noexcept
	{
		for (size_type xpos = 0; xpos < this->size (); ++xpos)
			if (traits::eq (_begin [xpos], c))
				return xpos;
		return npos;
	}

	size_type find (const charT* s) const noexcept
	{
		return this->find (basic_string_view {s});
	}

	size_type rfind (basic_string_view s) const noexcept
	{
		for (size_type xpos = this->size () - s.size (); xpos != npos; --xpos)
			if (_substr (xpos).starts_with (s))
				return xpos;
		return npos;
	}

	size_type rfind (charT c) const noexcept
	{
		for (size_type xpos = this->size () - 1; xpos != npos; --xpos)
			if (traits::eq (_begin [xpos], c))
				return xpos;
		return npos;
	}

	size_type rfind (const charT* s) const noexcept
	{
		return this->rfind (basic_string_view {s});
	}

	size_type find_first_of (basic_string_view s) const noexcept
	{
		for (size_type xpos = 0; xpos < this->size (); ++xpos)
			for (auto c : s)
				if (traits::eq (_begin [xpos], c))
					return xpos;
		return npos;
	}

	size_type find_first_of (charT c) const noexcept
	{
		return this->find (c);
	}

	size_type find_first_of (const charT* s) const noexcept
	{
		return this->find_first_of (basic_string_view {s});
	}

	size_type find_last_of (basic_string_view s) const noexcept
	{
		for (size_type xpos = this->size () - 1; xpos != npos; --xpos)
			for (auto c : s)
				if (traits::eq (_begin [xpos], c))
					return xpos;
		return npos;
	}

	size_type find_last_of (charT c) const noexcept
	{
		return this->rfind (c);
	}

	size_type find_last_of (const charT* s) const noexcept
	{
		return this->find_last_of (basic_string_view {s});
	}

	size_type find_first_not_of (basic_string_view s) const noexcept
	{
		for (size_type xpos = 0; xpos < this->size (); ++xpos)
		{
			for (auto c : s)
				if (traits::eq (_begin [xpos], c))
					goto next;
			return xpos;
		next:;
		}
		return npos;
	}

	size_type find_first_not_of (charT c) const noexcept
	{
		for (size_type xpos = 0; xpos < this->size (); ++xpos)
			if (!traits::eq (_begin [xpos], c))
				return xpos;
		return npos;
	}

	size_type find_first_not_of (const charT* s) const noexcept
	{
		return this->find_first_not_of (basic_string_view {s});
	}

	size_type find_last_not_of (basic_string_view s) const noexcept
	{
		for (size_type xpos = this->size () - 1; xpos != npos; --xpos)
		{
			for (auto c : s)
				if (traits::eq (_begin [xpos], c))
					goto next;
			return xpos;
		next:;
		}
		return npos;
	}

	size_type find_last_not_of (charT c) const noexcept
	{
		for (size_type xpos = this->size () - 1; xpos != npos; --xpos)
			if (!traits::eq (_begin [xpos], c))
				return xpos;
		return npos;
	}

	size_type find_last_not_of (const charT* s) const noexcept
	{
		return this->find_last_not_of (basic_string_view {s});
	}
};


// [string.view.comparison], non-member basic_string_view comparison functions

template <typename charT, typename traits>
constexpr inline
bool operator == (basic_string_view <charT, traits> x,
                  basic_string_view <charT, traits> y)
{
	return x.compare (y) == 0;
}

template <typename charT, typename traits>
constexpr inline
bool operator != (basic_string_view <charT, traits> x,
                  basic_string_view <charT, traits> y)
{
	return x.compare (y) != 0;
}

template <typename charT, typename traits>
constexpr inline
bool operator <  (basic_string_view <charT, traits> x,
                  basic_string_view <charT, traits> y)
{
	return x.compare (y) < 0;
}

template <typename charT, typename traits>
constexpr inline
bool operator >  (basic_string_view <charT, traits> x,
                  basic_string_view <charT, traits> y)
{
	return x.compare (y) > 0;
}

template <typename charT, typename traits>
constexpr inline
bool operator <= (basic_string_view <charT, traits> x,
                  basic_string_view <charT, traits> y)
{
	return x.compare (y) <= 0;
}

template <typename charT, typename traits>
constexpr inline
bool operator >= (basic_string_view <charT, traits> x,
                  basic_string_view <charT, traits> y)
{
	return x.compare (y) >= 0;
}


// [string.view.nonmem], other non-member basic_string_view functions

template <typename charT,
          typename traits    = std::char_traits <charT>,
          typename Allocator = std::allocator <charT> >
std::basic_string <charT, traits, Allocator>
to_string (basic_string_view <charT, traits> str,
           const Allocator& a = Allocator ())
{
	return {str.begin (), str.end (), a};
}

template <typename charT, typename traits>
std::basic_ostream <charT, traits>&
operator << (std::basic_ostream <charT, traits>& os,
             basic_string_view <charT,traits> str)
{
	return os.write (str.begin (), str.size ());
}


// basic_string_view typedef names
typedef basic_string_view <char>     string_view;
typedef basic_string_view <wchar_t>  wstring_view;
typedef basic_string_view <char16_t> u16string_view;
typedef basic_string_view <char32_t> u32string_view;


// basic_string_view conversion

#define STRING_VIEW_TO_INT_CONVERTER(rtype, name, strvw_t, cvt)                 \
inline rtype name (strvw_t str, std::size_t *idx = nullptr, int base = 10)      \
{                                                                               \
	return std::name (cvt (str), idx, base);                                \
}

#define STRING_VIEW_TO_FLOAT_CONVERTER(rtype, name, src_t, cvt)                 \
inline rtype name (src_t str, std::size_t *idx = nullptr)                       \
{                                                                               \
	return std::name (cvt (str), idx);                                      \
}

STRING_VIEW_TO_INT_CONVERTER   (int,                    stoi,   string_view, to_string);
STRING_VIEW_TO_INT_CONVERTER   (long int,               stol,   string_view, to_string);
STRING_VIEW_TO_INT_CONVERTER   (unsigned long int,      stoul,  string_view, to_string);
STRING_VIEW_TO_INT_CONVERTER   (long long int,          stoll,  string_view, to_string);
STRING_VIEW_TO_INT_CONVERTER   (unsigned long long int, stoull, string_view, to_string);
STRING_VIEW_TO_FLOAT_CONVERTER (float,                  stof,   string_view, to_string);
STRING_VIEW_TO_FLOAT_CONVERTER (double,                 stod,   string_view, to_string);
STRING_VIEW_TO_FLOAT_CONVERTER (long double,            stold,  string_view, to_string);

#undef STRING_VIEW_TO_INT_CONVERTER
#undef STRING_VIEW_TO_FLOAT_CONVERTER

}


// basic_string_view hash specializations

#ifdef __GLIBCXX__

namespace std
{

template <typename CharT, typename traits>
struct hash <sjo::basic_string_view <CharT, traits>>
	: __hash_base <size_t, sjo::basic_string_view <CharT, traits>>
{
	constexpr
	size_t operator () (const sjo::basic_string_view <CharT, traits>& sv) const noexcept
	{
		return std::_Hash_impl::hash (sv.data (), sv.length () * sizeof (sv [0]));
	}
};

}

#endif

#endif // STRING_VIEW_HH
