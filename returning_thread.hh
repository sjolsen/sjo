#ifndef SJO_RETURNING_THREAD_HH
#define SJO_RETURNING_THREAD_HH

#include <thread>

namespace sjo
{

template <typename Ret, typename... Args, typename Func>
inline
auto threadable (Func&& f)
{
	return [f = std::forward <Func> (f)] (Ret& ret, Args... args) { ret = f (std::forward <Args> (args)...); };
}

template <typename Func, typename Ret, typename... Args>
inline
std::thread returning_thread (Func&& f, Ret& ret, Args&&... args)
{
	return std::thread (threadable <Ret, Args...> (std::forward <Func> (f)), std::ref (ret), std::forward <Args> (args)...);
}

}

#endif
