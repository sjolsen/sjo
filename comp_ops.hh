#ifndef SJO_COMP_OPS_HEADER
#define SJO_COMP_OPS_HEADER

#include <utility>

namespace sjo
{

template <typename T>
struct comparator
{
	const T& _t;

	comparator (const T& t)
		: _t (t)
	{
	}

	comparator (T&& t) = delete;

	template <typename U>
	inline bool
	operator () (U&& _u) const
	{
		return std::forward <U> (_u) == _t;
	}
};

template <typename T>
inline sjo::comparator <T>
make_comparator (const T& _t)
{
	return _t;
}



#define SJO_DEFINE_OPERATOR_FUNCTOR(NAME_, BINOP_)                      \
struct NAME_                                                            \
{                                                                       \
	template <typename T, typename U>                               \
	inline auto                                                     \
	operator () (T&& _t, U&& _u)                                    \
		-> decltype (std::forward <T> (_t) BINOP_               \
		             std::forward <U> (_u))                     \
	{                                                               \
		return std::forward <T> (_t) BINOP_                     \
		       std::forward <U> (_u);                           \
	}                                                               \
}

SJO_DEFINE_OPERATOR_FUNCTOR (equal_to,     ==);
SJO_DEFINE_OPERATOR_FUNCTOR (not_equal_to, !=);
SJO_DEFINE_OPERATOR_FUNCTOR (less,          <);



#define SJO_DEFINE_UNARY_OPERATOR_FUNCTOR(NAME_, UNOP_)                 \
struct NAME_                                                            \
{                                                                       \
	template <typename T>                                           \
	inline auto                                                     \
	operator () (T&& _t)                                            \
		-> decltype (UNOP_ std::forward <T> (_t))               \
	{                                                               \
		return UNOP_ std::forward <T> (_t);                     \
	}                                                               \
}

SJO_DEFINE_UNARY_OPERATOR_FUNCTOR (is_true,   (bool));
SJO_DEFINE_UNARY_OPERATOR_FUNCTOR (is_false, !(bool));

} // namespace sjo

#endif // SJO_COMP_OPS_HEADER
