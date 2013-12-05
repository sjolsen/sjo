#ifndef SJO_COPY_PTR_HH
#define SJO_COPY_PTR_HH

#include <memory>

namespace sjo
{

template <typename T, typename Deleter = std::default_delete <T> >
class copy_ptr
	: std::unique_ptr <T, Deleter>
{
	using _base_type = std::unique_ptr <T, Deleter>;

public:
	using pointer      = typename _base_type::pointer;
	using element_type = typename _base_type::element_type;
	using deleter_type = typename _base_type::deleter_type;

	using _base_type::_base_type;

	copy_ptr (const _base_type& other)
		: _base_type (new T (*other))
	{
	}

	copy_ptr (const copy_ptr& other)
		: copy_ptr (static_cast <const _base_type&> (other))
	{
	}

	copy_ptr (copy_ptr&& other)
		: copy_ptr (static_cast <_base_type&&> (other))
	{
	}
};

} // sjo

#endif
