#ifndef SJO_LINSET_HH
#define SJO_LINSET_HH

#include "index_iterator.hh"
#include <deque>
#include <algorithm>

namespace sjo
{

template <typename Key, typename Compare = std::less <Key>, typename Container = std::deque <Key>>
class linset
{
public:
	using container_type         = Container;
	using key_type               = Key;
	using value_type             = Key;
	using size_type              = typename container_type::size_type;
	using difference_type        = typename container_type::difference_type;
	using key_compare            = Compare;
	using value_compare          = Compare;
	using allocator_type         = typename container_type::allocator_type;
	using reference              = value_type&;
	using const_reference        = const value_type&;
	using pointer                = typename std::allocator_traits <allocator_type>::pointer;
	using const_pointer          = typename std::allocator_traits <allocator_type>::const_pointer;
	using iterator               = sjo::index_iterator <container_type>;
	using const_iterator         = sjo::const_index_iterator <container_type>;
	using reverse_iterator       = std::reverse_iterator <iterator>;
	using const_reverse_iterator = std::reverse_iterator <const_iterator>;

private:
	container_type _data;
	mutable key_compare _compare;

protected:
	static constexpr
	const bool _nothrow_move_constructible =
		std::is_nothrow_move_constructible <container_type>::value &&
		std::is_nothrow_move_constructible <key_compare>::value;

	static constexpr
	const bool _nothrow_move_assignable =
		std::is_nothrow_move_assignable <container_type>::value &&
		std::is_nothrow_move_assignable <key_compare>::value;

	static constexpr
	const bool _nothrow_swappable =
		_nothrow_move_constructible &&
		_nothrow_move_assignable;

	bool _compare_equal (const key_type& a, const key_type& b) const noexcept
	{
		return !_compare (a, b) && !_compare (b, a);
	}

public:
	linset () = default;
	linset (const linset& other) = default;
	linset (linset&& other) noexcept (_nothrow_move_constructible) = default;

	linset (const linset& other, const allocator_type& alloc)
		: _data (other._data, alloc),
		  _compare (other._compare)
	{
	}

	linset (linset&& other, const allocator_type& alloc) noexcept (_nothrow_move_constructible)
		: _data (std::move (other._data), alloc),
		  _compare (std::move (other._compare))
	{
	}

	explicit linset (const key_compare& compare,
	                 const allocator_type& alloc = allocator_type ())
		: _data (alloc),
		  _compare (compare)
	{
	}

	explicit linset (const allocator_type& alloc)
		: _data (alloc)
	{
	}

	template <typename InputIt>
	linset (InputIt first, InputIt last,
	        const key_compare& compare = key_compare (),
	        const allocator_type& alloc = allocator_type ())
		: _data (alloc),
		  _compare (compare)
	{
		this->insert (first, last);
	}

	template <typename InputIt>
	linset (InputIt first, InputIt last,
	        const allocator_type& alloc = allocator_type ())
		: linset (first, last, key_compare (), alloc)
	{
	}

	linset (std::initializer_list <value_type> init,
	        const key_compare& compare = key_compare (),
	        const allocator_type& alloc = allocator_type ())
		: _data (alloc),
		  _compare (compare)
	{
		this->insert (init);
	}

	linset (std::initializer_list <value_type> init,
	        const allocator_type& alloc = allocator_type ())
		: linset (init, key_compare (), alloc)
	{
	}

	///

	linset& operator = (const linset& other)
	{
		_data = other._data;
		_compare = other._compare;
		return *this;
	}

	linset& operator = (linset&& other) noexcept (_nothrow_move_assignable)
	{
		_data = std::move (other._data);
		_compare = std::move (other._compare);
		return *this;
	}

	linset& operator = (std::initializer_list <value_type> ilist)
	{
		_data = ilist;
		return *this;
	}


	key_compare key_comp () const
	{
		return _compare;
	}

	value_compare value_comp () const
	{
		return _compare;
	}

	allocator_type get_allocator () const
	{
		return _data.get_allocator ();
	}


	iterator begin () noexcept
	{
		return iterator {_data, 0};
	}

	const_iterator begin () const noexcept
	{
		return const_iterator {_data, 0};
	}

	const_iterator cbegin () const noexcept
	{
		return const_iterator {_data, 0};
	}


	iterator end () noexcept
	{
		return iterator {_data, _data.size ()};
	}

	const_iterator end () const noexcept
	{
		return const_iterator {_data, _data.size ()};
	}

	const_iterator cend () const noexcept
	{
		return const_iterator {_data, _data.size ()};
	}


	reverse_iterator rbegin () noexcept
	{
		return reverse_iterator {this->begin ()};
	}

	const_reverse_iterator rbegin () const noexcept
	{
		return const_reverse_iterator {this->begin ()};
	}

	const_reverse_iterator crbegin () const noexcept
	{
		return const_reverse_iterator {this->cbegin ()};
	}


	reverse_iterator rend () noexcept
	{
		return reverse_iterator {this->end ()};
	}

	const_reverse_iterator rend () const noexcept
	{
		return const_reverse_iterator {this->end ()};
	}

	const_reverse_iterator crend () const noexcept
	{
		return const_reverse_iterator {this->cend ()};
	}


	bool empty () const noexcept
	{
		return _data.empty ();
	}

	size_type size () const noexcept
	{
		return _data.size ();
	}

	size_type max_size () const noexcept
	{
		return _data.max_size ();
	}


	void clear () noexcept
	{
		_data.clear ();
	}


	std::pair <iterator, bool> insert (const value_type& value)
	{
		return this->insert (value_type {value});
	}

	std::pair <iterator, bool> insert (value_type&& value)
	{
		auto pos = std::lower_bound (_data.begin (), _data.end (), value, _compare);
		size_type index = pos - _data.begin ();
		bool do_insert = (pos == _data.end ()) || !this->_compare_equal (*pos, value);

		if (do_insert)
			_data.insert (pos, std::move (value));
		return {iterator {_data, index}, do_insert};
	}

	iterator insert (const_iterator hint, const value_type& value)
	{
		return this->insert (value);
	}

	iterator insert (const_iterator hint, value_type&& value)
	{
		return this->insert (std::move (value));
	}

	template <typename InputIt>
	void insert (InputIt first, InputIt last)
	{
		while (first != last)
		{
			this->insert (*first);
			++first;
		}
	}

	void insert (std::initializer_list <value_type> ilist)
	{
		this->insert (ilist.begin (), ilist.end ());
	}


	template <typename... Args>
	std::pair <iterator, bool> emplace (Args&&... args)
	{
		return this->insert (value_type (std::forward <Args> (args)...));
	}

	template <typename... Args>
	std::pair <iterator, bool> emplace_hint (const_iterator hint, Args&&... args)
	{
		return this->insert (value_type (std::forward <Args> (args)...));
	}


	iterator erase (const_iterator pos)
	{
		return iterator {_data, _data.erase (pos.base ())};
	}

	iterator erase (const_iterator first, const_iterator last)
	{
		return iterator {_data, _data.erase (first.base (), last.base ())};
	}

	size_type erase (const key_type& key)
	{
		auto iter = this->find (key);
		if (iter == this->end ())
			return 0;
		_data.erase (iter.base ());
		return 1;
	}


	void swap (linset& other) noexcept (_nothrow_swappable)
	{
		using std::swap;
		swap (_data, other._data);
		swap (_compare, other._compare);
	}


	size_type count (const key_type& key) const
	{
		if (this->find (key) == this->end ())
			return 0;
		else
			return 1;
	}


	iterator find (const key_type& key)
	{
		return iterator {_data, std::find (_data.begin (), _data.end (), key)};
	}

	const_iterator find (const key_type& key) const
	{
		return const_iterator {_data, std::find (_data.begin (), _data.end (), key)};
	}


	std::pair <iterator, iterator> equal_range (const key_type& key)
	{
		return {this->lower_bound (), this->upper_bound ()};
	}

	std::pair <const_iterator, const_iterator> equal_range (const key_type& key) const
	{
		return {this->lower_bound (), this->upper_bound ()};
	}


	iterator lower_bound (const key_type& key)
	{
		return iterator {_data, std::lower_bound (_data.begin (), _data.end (), key)};
	}

	const_iterator lower_bound (const key_type& key) const
	{
		return const_iterator {_data, std::lower_bound (_data.begin (), _data.end (), key)};
	}

	iterator upper_bound (const key_type& key)
	{
		return iterator {_data, std::upper_bound (_data.begin (), _data.end (), key)};
	}

	const_iterator upper_bound (const key_type& key) const
	{
		return const_iterator {_data, std::upper_bound (_data.begin (), _data.end (), key)};
	}

	///

	friend bool operator == (const linset& a, const linset& b) noexcept
	{
		return a._data == b._data;
	}

	friend bool operator != (const linset& a, const linset& b) noexcept
	{
		return a._data != b._data;
	}

	friend bool operator <  (const linset& a, const linset& b) noexcept
	{
		return a._data < b._data;
	}

	friend bool operator <= (const linset& a, const linset& b) noexcept
	{
		return a._data <= b._data;
	}

	friend bool operator >  (const linset& a, const linset& b) noexcept
	{
		return a._data > b._data;
	}

	friend bool operator >= (const linset& a, const linset& b) noexcept
	{
		return a._data >= b._data;
	}
};

}

namespace std
{

	template <typename Key, typename Compare, typename Container>
	void swap (sjo::linset <Key, Compare, Container>& a,
	           sjo::linset <Key, Compare, Container>& b) noexcept (noexcept (a.swap (b)))
	{
		a.swap (b);
	}

}

#endif
