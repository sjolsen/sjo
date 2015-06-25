#ifndef SJO_LIFT_HH
#define SJO_LIFT_HH

#include <utility>

#define LIFT(fname) \
[] (auto&&... args) -> decltype (auto) \
{ \
	return fname (std::forward <decltype (args)> (args)...); \
}

#define MLIFT(mname) \
[] (auto&& obj) -> decltype (auto) \
{ \
	return std::forward <decltype (obj)> (obj).mname; \
}

#define MFLIFT(mfname) \
[] (auto&& obj, auto&&... args) -> decltype (auto) \
{ \
	return std::forward <decltype (obj)> (obj).mfname (std::forward <decltype (args)> (args)...); \
}

#define UNOP(sym) \
[] (auto&& arg) -> decltype (auto) \
{ \
	return sym (std::forward <decltype (arg)> (arg)); \
}

#define BINOP(sym) \
[] (auto&& arg1, auto&& arg2) -> decltype (auto) \
{ \
return (std::forward <decltype (arg1)> (arg1)) sym (std::forward <decltype (arg2)> (arg2)); \
}

#endif
