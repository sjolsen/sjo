#ifndef SJO_RETURNING_THREAD_HH
#define SJO_RETURNING_THREAD_HH

#include <thread>

namespace sjo
{

namespace
{

template <typename F>
struct forward_function_impl
{
	using type = F;
};

template <typename Ret, typename... Args>
struct forward_function_impl <Ret (&) (Args...)>
{
	using type = Ret (*) (Args...);
};

template <typename... Args>
using forward_function = typename forward_function_impl <Args...>::type;

}

template <typename Ret, typename... Args, typename Func>
inline
auto threadable (Func&& f)
{
	return [f = forward_function <Func> (f)] (Ret& ret, Args... args) { ret = f (std::forward <Args> (args)...); };
}

template <typename Func, typename Ret, typename... Args>
inline
std::thread returning_thread (Func&& f, Ret& ret, Args&&... args)
{
	return std::thread (threadable <Ret, Args...> (std::forward <Func> (f)), std::ref (ret), std::forward <Args> (args)...);
}

}

#endif
