#ifndef SJO_STREAM_RANGE_CC
#define SJO_STREAM_RANGE_CC

#include "stream_range.hh"
#include <stdexcept>

namespace sjo
{

namespace detail
{

// This function does all of the heavy lifting for stream_range
template <typename BSR_type>
typename BSR_type::difference_type
bsr_adjust_checked (typename BSR_type::stream_type& _stream,
                    typename BSR_type::buffer_type& _buffer,
                    typename BSR_type::difference_type _pos,
                    typename BSR_type::difference_type offset)
{
	if (_pos == BSR_type::max_pos)
		throw std::logic_error ("tried to adjust a past-the-end iterator");
	if (_pos + offset < 0)
		throw std::out_of_range ("stream_range underflow");

	while (true)
	{
		if (_pos + offset < _buffer.size ())
			return _pos + offset;

		if (_stream.eof ())
		{
		cond_eof:
			if (_pos + offset == _buffer.size ())
				return BSR_type::max_pos;
			else // _pos + offset > _buffer.size ()
				throw std::out_of_range ("stream_range overflow");
		}

		typename BSR_type::char_type c;
		_stream >> c;
		if (_stream.eof ())
			goto cond_eof;
		_buffer.push_back (c);
	}
}

}



#define SJO_BSR_ITERATOR_TPDECL template <typename CharT, typename Traits, typename Stream, typename Buffer> inline
#define SJO_BSR_ITERATOR basic_stream_range_iterator <CharT, Traits, Stream, Buffer>
#define SJO_BSR_ITERATOR_REFERENCE typename SJO_BSR_ITERATOR::reference
#define SJO_BSR_ITERATOR_DIFFERENCE_TYPE typename SJO_BSR_ITERATOR::difference_type

#ifdef SJO_DEBUG
# define SJO_BSR_ITERATOR_SOURCE_CHECK [&] {\
if (_buffer != other._buffer)\
	throw std::logic_error ("comparison between incomparable stream_range iterators");\
} ()
#else
# define SJO_BSR_ITERATOR_SOURCE_CHECK
#endif

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR&
SJO_BSR_ITERATOR::operator = (const SJO_BSR_ITERATOR& other)
{
	_stream = other._stream;
	_buffer = other._buffer;
	_pos    = other._pos;
	return *this;
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR&
SJO_BSR_ITERATOR::operator = (SJO_BSR_ITERATOR&& other) noexcept
{
	return *this = other;
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR_REFERENCE
SJO_BSR_ITERATOR::operator *() const
{
	return (*_buffer) [_pos];
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR_REFERENCE
SJO_BSR_ITERATOR::operator [] (SJO_BSR_ITERATOR_DIFFERENCE_TYPE offset) const
{
	return (*_buffer) [_pos + offset];
}

SJO_BSR_ITERATOR_TPDECL
const SJO_BSR_ITERATOR&
SJO_BSR_ITERATOR::operator->() const
{
	return *this;
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR&
SJO_BSR_ITERATOR::operator ++()
{
	return *this += 1;
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR
SJO_BSR_ITERATOR::operator++ (int)
{
	auto old = *this;
	++*this;
	return old;
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR&
SJO_BSR_ITERATOR::operator += (SJO_BSR_ITERATOR_DIFFERENCE_TYPE offset)
{
	_pos = sjo::detail::bsr_adjust_checked <decltype (*this)> (*_stream, *_buffer, _pos, offset);
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR
SJO_BSR_ITERATOR::operator + (SJO_BSR_ITERATOR_DIFFERENCE_TYPE offset) const
{
	auto tmp = *this;
	tmp += offset;
	return tmp;
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR&
SJO_BSR_ITERATOR::operator --()
{
	return *this -= 1;
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR
SJO_BSR_ITERATOR::operator-- (int)
{
	auto old = *this;
	--*this;
	return old;
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR&
SJO_BSR_ITERATOR::operator -= (SJO_BSR_ITERATOR_DIFFERENCE_TYPE offset)
{
	return *this += -offset;
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR
SJO_BSR_ITERATOR::operator - (SJO_BSR_ITERATOR_DIFFERENCE_TYPE offset) const
{
	auto tmp = *this;
	tmp -= offset;
	return tmp;
}

SJO_BSR_ITERATOR_TPDECL
SJO_BSR_ITERATOR_DIFFERENCE_TYPE
SJO_BSR_ITERATOR::operator - (const SJO_BSR_ITERATOR& other) const
{
	SJO_BSR_ITERATOR_SOURCE_CHECK;
	return _pos - other._pos;
}

#define SJO_BSR_ITERATOR_DEFINE_RELOP(OP)\
 SJO_BSR_ITERATOR_TPDECL\
 bool\
 SJO_BSR_ITERATOR::operator OP (const SJO_BSR_ITERATOR& other) const\
{\
	SJO_BSR_ITERATOR_SOURCE_CHECK;\
	return _pos OP other._pos;\
}

SJO_BSR_ITERATOR_DEFINE_RELOP (==);
SJO_BSR_ITERATOR_DEFINE_RELOP (!=);
SJO_BSR_ITERATOR_DEFINE_RELOP (<=);
SJO_BSR_ITERATOR_DEFINE_RELOP (>=);
SJO_BSR_ITERATOR_DEFINE_RELOP (<);
SJO_BSR_ITERATOR_DEFINE_RELOP (>);

#undef SJO_BSR_ITERATOR_DEFINE_RELOP
#undef SJO_BSR_ITERATOR_SOURCE_CHECK
#undef SJO_BSR_ITERATOR_DIFFERENCE_TYPE
#undef SJO_BSR_ITERATOR_REFERENCE
#undef SJO_BSR_ITERATOR
#undef SJO_BSR_ITERATOR_TPDECL



} // namespace sjo

#endif
