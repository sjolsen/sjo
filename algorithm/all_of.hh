#ifndef SJO_ALGORITHM_ALL_OF_HEADER
#define SJO_ALGORITHM_ALL_OF_HEADER

#include <sjo/range.hh>
#include <sjo/comp_ops.hh>
#include "impl/all_of.hh"
#include "impl/adaptor_macros.hh"

namespace sjo
{

SJO_ALGORITHM_IRANGE_UNARY_ADAPTOR (all_of, bool);

} // namespace sjo

#endif // SJO_ALGORITHM_ALL_OF_HEADER
