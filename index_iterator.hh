#ifndef SJO_INDEX_ITERATOR_BASE_HH
#define SJO_INDEX_ITERATOR_BASE_HH

#include <iterator>
#include <memory>

namespace sjo
{

template <typename Container,
          typename Pointer = typename Container::pointer,
          typename Reference = typename Container::reference>
class index_iterator_base
	: std::iterator <std::random_access_iterator_tag,
	                 typename Container::value_type,
	                 typename Container::difference_type,
	                 Pointer,
	                 Reference>
{
public:
	using container_type  = Container;
	using size_type       = typename container_type::size_type;
	using value_type      = typename container_type::value_type;
	using difference_type = typename container_type::difference_type;
	using pointer         = Pointer;
	using reference       = Reference;

private:
	container_type (*_container) = nullptr;
	size_type _index = 0;

protected:
	template <typename Other>
	static constexpr
	bool _passignable ()
	{
		return std::is_convertible <Other*, container_type*>::value;
	}

public:
	index_iterator_base () noexcept = default;

	template <typename Other, typename = std::enable_if <_passignable <Other> (), void>>
	index_iterator_base (const index_iterator_base <Other>& other) noexcept
		: _container (other._container),
	          _index (other._index)
	{
	}

	explicit
	index_iterator_base (container_type& container, size_type index)
		: _container (&container),
		  _index (index)
	{
	}

	///

	template <typename Other, typename = std::enable_if <_passignable <Other> (), void>>
	index_iterator_base& operator = (const index_iterator_base <Other>& other)
	{
		_container = other._container;
		_index = other._index;
		return *this;
	}

	size_type base () const noexcept
	{
		return _index;
	}

	reference operator *() const
	{
		return (*_container) [_index];
	}

	pointer operator->() const
	{
		std::addressof (this->operator ());
	}

	reference operator [] (difference_type n) const
	{
		return (*_container) [_index + n];
	}

	///

	index_iterator_base& operator ++()
	{
		++_index;
		return *this;
	}

	index_iterator_base& operator --()
	{
		--_index;
		return *this;
	}

	index_iterator_base& operator++ (int)
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	index_iterator_base& operator-- (int)
	{
		auto tmp = *this;
		--*this;
		return tmp;
	}

	index_iterator_base& operator += (difference_type n)
	{
		_index += n;
		return *this;
	}

	index_iterator_base& operator -= (difference_type n)
	{
		_index -= n;
		return *this;
	}

	index_iterator_base operator + (difference_type n) const
	{
		return index_iterator_base (*this) += n;
	}

	index_iterator_base operator - (difference_type n) const
	{
		return index_iterator_base (*this) -= n;
	}

	///

	template <typename C1, typename C2>
	friend bool operator == (const index_iterator_base <C1>& a, const index_iterator_base <C2>& b) noexcept
	{
		return a._container == b._container && a._index == b._index;
	}

	template <typename C1, typename C2>
	friend bool operator != (const index_iterator_base <C1>& a, const index_iterator_base <C2>& b) noexcept
	{
		return !(a == b);
	}

	template <typename C1, typename C2>
	friend bool operator <  (const index_iterator_base <C1>& a, const index_iterator_base <C2>& b) noexcept
	{
		return a._index < b._index;
	}

	template <typename C1, typename C2>
	friend bool operator <= (const index_iterator_base <C1>& a, const index_iterator_base <C2>& b) noexcept
	{
		return a._index <= b._index;
	}

	template <typename C1, typename C2>
	friend bool operator >  (const index_iterator_base <C1>& a, const index_iterator_base <C2>& b) noexcept
	{
		return a._index > b._index;
	}

	template <typename C1, typename C2>
	friend bool operator >= (const index_iterator_base <C1>& a, const index_iterator_base <C2>& b) noexcept
	{
		return a._index >= b._index;
	}

	///

	friend index_iterator_base operator + (difference_type n, const index_iterator_base& iter)
	{
		return iter + n;
	}

	template <typename C1, typename C2>
	friend auto operator - (const index_iterator_base <C1>& a, const index_iterator_base <C2>& b)
	{
		return b._index - a._index;
	}
};

template <typename Container>
class index_iterator
	: public index_iterator_base <Container>
{
	using index_iterator_base <Container>::index_iterator_base;
};

template <typename Container>
class const_index_iterator
	: public index_iterator_base <Container,
	                              typename Container::const_pointer,
	                              typename Container::const_reference>
{
	using index_iterator_base <Container,
	                           typename Container::const_pointer,
	                           typename Container::const_reference>::index_iterator_base;
};

}

#endif
