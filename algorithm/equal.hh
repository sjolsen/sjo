// -*- mode: c++; -*-

#ifndef SJO_ALGO_STD_ALGORITHM_EQUAL_HEADER
#define SJO_ALGO_STD_ALGORITHM_EQUAL_HEADER

#include <sjo/range.hh>
#include <sjo/comp_ops.hh>
#include "impl/equal.hh"
#include "impl/adaptor_macros.hh"

namespace sjo
{

SJO_ALGORITHM_IRANGE_IRANGE_BINARY_ADAPTOR (equal, bool);

} // namespace sjo

#endif // SJO_ALGO_STD_ALGORITHM_EQUAL_HEADER
