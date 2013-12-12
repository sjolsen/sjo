#ifndef SJO_STREAM_RANGE_HH
#define SJO_STREAM_RANGE_HH

#include <string>
#include <istream>
#include <iterator>

namespace sjo
{

template <typename, typename>
class basic_stream_range;

template <typename CharT, typename Traits, typename Stream, typename Buffer>
class basic_stream_range_iterator
	: std::iterator <std::random_access_iterator_tag,
	                 CharT,
	                 typename Buffer::difference_type,
	                 const CharT*,
	                 const CharT&>
{
public:
	using char_type       = CharT;
	using value_type      = char_type;
	using stream_type     = Stream;
	using buffer_type     = Buffer;

	using difference_type = typename buffer_type::difference_type;
	using pointer         = const value_type*;
	using reference       = const value_type&;

	static constexpr
	const difference_type max_pos = -1;

private:
	stream_type (*_stream) = nullptr;
	buffer_type (*_buffer) = nullptr;
	difference_type _pos   = max_pos;

protected:
	enum CONSTRUCT
	{
		CONSTRUCT_BEGIN,
		CONSTRUCT_END
	};

	using range_type = basic_stream_range <CharT, Traits>;
	friend range_type;

	basic_stream_range_iterator (stream_type& stream, buffer_type& buffer, CONSTRUCT where);

public:
	basic_stream_range_iterator () noexcept = default;
	basic_stream_range_iterator (const basic_stream_range_iterator&) = default;
	basic_stream_range_iterator (basic_stream_range_iterator&&) noexcept = default;

	basic_stream_range_iterator& operator = (const basic_stream_range_iterator& other);
	basic_stream_range_iterator& operator = (basic_stream_range_iterator&& other) noexcept;

	reference operator *() const;
	reference operator [] (difference_type offset) const;
	const basic_stream_range_iterator& operator->() const;

	basic_stream_range_iterator& operator ++();
	basic_stream_range_iterator operator++ (int);
	basic_stream_range_iterator& operator += (difference_type offset);
	basic_stream_range_iterator operator + (difference_type offset) const;

	basic_stream_range_iterator& operator --();
	basic_stream_range_iterator operator-- (int);
	basic_stream_range_iterator& operator -= (difference_type offset);
	basic_stream_range_iterator operator - (difference_type offset) const;

	difference_type operator - (const basic_stream_range_iterator& other) const;

	bool operator == (const basic_stream_range_iterator& other) const;
	bool operator != (const basic_stream_range_iterator& other) const;
	bool operator <= (const basic_stream_range_iterator& other) const;
	bool operator >= (const basic_stream_range_iterator& other) const;
	bool operator < (const basic_stream_range_iterator& other) const;
	bool operator > (const basic_stream_range_iterator& other) const;
};



template <typename CharT, typename Traits = std::char_traits <CharT>>
class basic_stream_range
{
public:
	using char_type   = CharT;
	using traits_type = Traits;
	using stream_type = std::basic_istream <char_type, traits_type>;
	using buffer_type = std::basic_string <char_type, traits_type>;

	using value_type      = char_type;
	using reference       = const char_type&;
	using const_reference = reference;
	using iterator        = basic_stream_range_iterator <char_type, traits_type, stream_type, buffer_type>;
	using const_iterator  = iterator;
	using difference_type = typename buffer_type::difference_type;
	using size_type       = typename buffer_type::size_type;

private:
	stream_type (*_stream) = nullptr;
	mutable buffer_type _buffer;

public:
	basic_stream_range (stream_type (*stream))
		: _stream (stream)
	{
	}

	basic_stream_range () = default;
	basic_stream_range (const basic_stream_range&) = delete;
	basic_stream_range (basic_stream_range&&) noexcept = default;

	basic_stream_range& operator = (const basic_stream_range&) = delete;
	basic_stream_range& operator = (basic_stream_range&& other) noexcept;

	const_iterator begin () const;
	const_iterator cbegin () const;
	const_iterator end () const;
	const_iterator cend () const;

	const_reference operator [] (difference_type offset) const;

	bool operator == (const basic_stream_range& other) const;
	bool operator != (const basic_stream_range& other) const;

	void swap (basic_stream_range& other) noexcept;
	void swap (basic_stream_range&& other) noexcept;

	size_type max_size () const;
	bool empty () const;

// The following functions empty the input buffer into the range buffer:

	const buffer_type& final_buffer () const;
	size_type size () const;
};

#define SJO_BSR_SWAP_DECLARATOR(REF1, REF2)\
template <typename CharT, typename Traits>\
void swap (basic_stream_range <CharT, Traits>REF1 a, basic_stream_range <CharT, Traits>REF2 b) noexcept;
SJO_BSR_SWAP_DECLARATOR (&,  &);
SJO_BSR_SWAP_DECLARATOR (&,  &&);
SJO_BSR_SWAP_DECLARATOR (&&, &);
SJO_BSR_SWAP_DECLARATOR (&&, &&);
#undef SJO_BSR_SWAP_DECLARATOR

} // namespace sjo

#include "stream_range.cc"

#endif
