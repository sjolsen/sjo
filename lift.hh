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

#define FNOT(fname) FLIFT (!fname)

#endif
