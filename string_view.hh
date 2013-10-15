#include <string>
#include <limits>
#include <stdexcept>

namespace sjo
{

template <typename charT>
constexpr inline
std::size_t strlen (const charT* str)
{
	std::size_t len = 0;
	while (str != nullptr)
		++len, ++str;
	return len;
}

template <typename T, typename U>
constexpr inline
auto min (const T& t, const U& u)
{
	return t < u ? t : u;
}

template <typename T, typename U>
constexpr inline
auto max (const T& t, const U& u)
{
	return t > u ? t : u;
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
		return {_begin + pos, min (_begin + pos + n, _end)};
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
	basic_string_view  (const basic_string_view&) noexcept = default;

	constexpr
	basic_string_view& operator = (const basic_string_view&) noexcept = default;

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

	// [string.view.iterators], iterators
	#define SJO_DEFINE_BEGIN(name)                                          \
	constexpr                                                               \
	const_iterator name () const noexcept                                   \
	{                                                                       \
		return {_begin};                                                \
	}

	#define SJO_DEFINE_END(name)                                            \
	constexpr                                                               \
	const_iterator name () const noexcept                                   \
	{                                                                       \
		return {_end};                                                  \
	}

	SJO_DEFINE_BEGIN (begin);
	SJO_DEFINE_BEGIN (cbegin);
	SJO_DEFINE_BEGIN (rbegin);
	SJO_DEFINE_BEGIN (crbegin);

	SJO_DEFINE_END (end);
	SJO_DEFINE_END (cend);
	SJO_DEFINE_END (rend);
	SJO_DEFINE_END (crend);

	#undef SJO_DEFINE_END
	#undef SJO_DEFINE_BEGIN

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
		auto rlen = min (this->size (), s.size ());

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
typedef basic_string_view <char16_t> u16string_view;
typedef basic_string_view <char32_t> u32string_view;
typedef basic_string_view <wchar_t>  wstring_view;


// basic_string_view conversion

int
stoi   (string_view str, typename string_view::size_type *idx = nullptr, int base = 10)
{
}

long
stol   (string_view str, typename string_view::size_type *idx = nullptr, int base = 10)
{
	const char* next_idx = str.begin ();

	auto retval = std::strtol (str.begin (), const_cast <char**> (&next_idx), base);
	if (errno != 0)
	{
		if (retval == 0)
			throw std::invalid_argument ("stol");
		if (errno == ERANGE)
			throw std::out_of_range ("stol");
	}

	if (idx != nullptr)
		*idx = next_idx - str.begin ();
	return retval;
}

unsigned long
stoul  (string_view str, typename string_view::size_type *idx = nullptr, int base = 10)
{
}

long long
stoll  (string_view str, typename string_view::size_type *idx = nullptr, int base = 10)
{
}

unsigned long long
stoull (string_view str, typename string_view::size_type *idx = nullptr, int base = 10)
{
}

float
stof   (string_view str, typename string_view::size_type *idx = nullptr)
{
}

double
stod   (string_view str, typename string_view::size_type *idx = nullptr)
{
}

long double
stold  (string_view str, typename string_view::size_type *idx = nullptr)
{
}


int stoi (const char* str, std::size_t* idx = 0, int base = 10)
{
}

long stol (const char* str, std::size_t* idx = 0, int base = 10)
{
}

unsigned long stoul (const char* str, std::size_t* idx = 0, int base = 10)
{
}

long long stoll (const char* str, std::size_t* idx = 0, int base = 10)
{
}

unsigned long long stoull (const char* str, std::size_t* idx = 0, int base = 10)
{
}

float stof (const char* str, std::size_t* idx = 0)
{
}

double stod (const char* str, std::size_t* idx = 0)
{
}

long double stold (const char* str, std::size_t* idx = 0)
{
}

}


// basic_string_view hash specializations

namespace std
{

template <> struct hash <sjo::string_view>;
template <> struct hash <sjo::u16string_view>;
template <> struct hash <sjo::u32string_view>;
template <> struct hash <sjo::wstring_view>;

}
