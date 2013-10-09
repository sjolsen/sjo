#ifndef ALLOC_PTR_HH
#define ALLOC_PTR_HH

#include <cstddef>     // std::nullptr_t
#include <utility>     // std::move
#include <memory>      // std::allocator_traits
#include <type_traits> // std::declval, std::enable_if

template <typename T, typename Alloc = std::allocator <T>>
class alloc_ptr
{
public:
	using element_type   = T;
	using allocator_type = Alloc;
	using pointer        = typename allocator_type::pointer;

private:
	pointer        _data  {};
	allocator_type _alloc {};

	template <typename, typename>
	friend class alloc_ptr;

protected:
	template <typename U, typename Other_alloc>
	Other_alloc _move_alloc_if (alloc_ptr <U, Other_alloc>&& other,
	                            bool propagate_allocator = std::allocator_traits <Other_alloc>::propagate_on_container_move_assignment::value)
	{
		if (propagate_allocator)
			return std::move (other._alloc);
		else
			return Other_alloc {};
	}

public:
	constexpr
	alloc_ptr () noexcept = default;

	constexpr
	alloc_ptr (std::nullptr_t) noexcept
	{
	}

	explicit
	alloc_ptr (pointer p) noexcept
		: _data (std::move (p))
	{
	}

	template <typename Alloc_arg>
	alloc_ptr (pointer p, Alloc_arg&& alloc) noexcept
		: _data (std::move (p)),
		  _alloc (std::forward <Alloc_arg> (alloc))
	{
	}

	template <typename U, typename Other_alloc>
	alloc_ptr (alloc_ptr <U, Other_alloc>&& other) noexcept
		: _data (std::move (other._data)),
		  _alloc (_move_alloc_if (std::move (other)))
	{
		other._data = typename alloc_ptr <U, Other_alloc>::pointer {};
	}

	//

	void reset (pointer p = pointer {}) noexcept
	{
		if (_data)
		{
			_alloc.destroy (_data);
			_alloc.deallocate (_data, 1);
		}
		_data = p;
	}

	pointer release () noexcept
	{
		// return std::exchange (_data, pointer {});
		auto temp = _data;
		_data = pointer {};
		return temp;
	}

	template <typename U, typename Other_alloc>
	void swap (alloc_ptr <U, Other_alloc>& other) noexcept
	{
		using std::swap;
		swap (_data, other._data);
		if (std::allocator_traits <allocator_type>::propagate_on_container_swap::value &&
		    std::allocator_traits <Other_alloc>   ::propagate_on_container_swap::value)
			swap (_alloc, other._alloc);
	}

	//

	pointer get () const noexcept
	{
		return _data;
	}

	allocator_type& get_allocator () noexcept
	{
		return _alloc;
	}

	const allocator_type& get_allocator () const noexcept
	{
		return _alloc;
	}

	explicit operator bool () const noexcept
	{
		return !(_data == pointer {});
	}

	//

	decltype (*std::declval <typename std::allocator_traits <allocator_type>::pointer> ())
	operator *() const
	{
		return *_data;
	}

	pointer operator -> () const
	{
		return _data;
	}

	//

	template <typename U, typename Other_alloc>
	alloc_ptr& operator = (alloc_ptr <U, Other_alloc>&& other) noexcept
	{
		this->reset (std::move (other._data));
		other._data = typename alloc_ptr <U, Other_alloc>::pointer {};
		_alloc = _move_alloc_if (std::move (other));
		return *this;
	}

	alloc_ptr& operator = (std::nullptr_t) noexcept
	{
		this->reset ();
	}

	//

	~alloc_ptr ()
	{
		this->reset ();
	}
};



template <typename T>
struct Alloc_ptr_comparable_impl
	: std::false_type
{
};

template <typename T, typename Alloc>
struct Alloc_ptr_comparable_impl <alloc_ptr <T, Alloc>>
	: std::true_type
{
};

template <>
struct Alloc_ptr_comparable_impl <std::nullptr_t>
	: std::true_type
{
};

template <typename T>
constexpr bool
Alloc_ptr_comparable ()
{
	return Alloc_ptr_comparable_impl <typename std::remove_reference <typename std::remove_cv <T>::type>::type>::value;
}

template <typename T, typename Alloc>
typename alloc_ptr <T, Alloc>::pointer
inline
get_pointer (const alloc_ptr <T, Alloc>& ptr) noexcept
{
	return ptr.get ();
}

inline constexpr
std::nullptr_t get_pointer (std::nullptr_t) noexcept
{
	return nullptr;
}



template <typename T1, typename T2,
          typename = typename std::enable_if <Alloc_ptr_comparable <T1> (), void>::type,
          typename = typename std::enable_if <Alloc_ptr_comparable <T2> (), void>::type>
bool operator == (T1&& t1, T2&& t2)
{
	return get_pointer (t1) == get_pointer (t2);
}

template <typename T1, typename T2,
          typename = typename std::enable_if <Alloc_ptr_comparable <T1> (), void>::type,
          typename = typename std::enable_if <Alloc_ptr_comparable <T2> (), void>::type>
bool operator != (T1&& t1, T2&& t2)
{
	return !(get_pointer (t1) == get_pointer (t2));
}

template <typename T1, typename T2,
          typename = typename std::enable_if <Alloc_ptr_comparable <T1> (), void>::type,
          typename = typename std::enable_if <Alloc_ptr_comparable <T2> (), void>::type>
bool operator < (T1&& t1, T2&& t2)
{
	return get_pointer (t1) < get_pointer (t2);
}

template <typename T1, typename T2,
          typename = typename std::enable_if <Alloc_ptr_comparable <T1> (), void>::type,
          typename = typename std::enable_if <Alloc_ptr_comparable <T2> (), void>::type>
bool operator <= (T1&& t1, T2&& t2)
{
	auto p1 = get_pointer (t1);
	auto p2 = get_pointer (t2);
	return p1 < p2 || p1 == p2;
}

template <typename T1, typename T2,
          typename = typename std::enable_if <Alloc_ptr_comparable <T1> (), void>::type,
          typename = typename std::enable_if <Alloc_ptr_comparable <T2> (), void>::type>
bool operator > (T1&& t1, T2&& t2)
{
	auto p1 = get_pointer (t1);
	auto p2 = get_pointer (t2);
	return !(p1 < p2 || p1 == p2);
}

template <typename T1, typename T2,
          typename = typename std::enable_if <Alloc_ptr_comparable <T1> (), void>::type,
          typename = typename std::enable_if <Alloc_ptr_comparable <T2> (), void>::type>
bool operator >= (T1&& t1, T2&& t2)
{
	return !(get_pointer (t1) < get_pointer (t2));
}

#endif
