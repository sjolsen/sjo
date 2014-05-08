#ifndef SJO_LIFT_HH
#define SJO_LIFT_HH

#include <utility>

#define LIFT(member) \
[] (auto&& obj) -> decltype (auto) \
{ \
	return std::forward <decltype (obj)> (obj).member; \
}

#define MFLIFT(member) \
[] (auto&& obj, auto&&... args) -> decltype (auto) \
{ \
	return std::forward <decltype (obj)> (obj).member (std::forward <decltype (args)> (args)...); \
}

#define FLIFT(fname) \
[] (auto&&... args) -> decltype (auto) \
{ \
	return fname (std::forward <decltype (args)> (args)...); \
}

#define UOPLIFT(sym) \
[] (auto&& arg) -> decltype (auto) \
{ \
	return sym (std::forward <decltype (arg)> (arg)); \
}

#define BOPLIFT(sym) \
[] (auto&& arg1, auto&& arg2) -> decltype (auto) \
{ \
	return (std::forward <decltype (arg1)> (arg1)) sym (std::forward <decltype (arg2)> (arg2)); \
}

template <typename Func>
inline constexpr
auto ordered_by (Func&& f)
{
	return [f = std::forward <Func> (f)] (auto&& a, auto&& b)
	{ return f (std::forward <decltype (a)> (a)) < f (std::forward <decltype (b)> (b)); };
}

#define FNOT(fname) FLIFT (!fname)

#endif
