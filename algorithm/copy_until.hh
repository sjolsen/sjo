#ifndef SJO_ALGORITHM_COPY_UNTIL_HEADER
#define SJO_ALGORITHM_COPY_UNTIL_HEADER

#include <sjo/comp_ops.hh>
#include <sjo/range.hh>
#include "impl/copy_until.hh"
#include "impl/adaptor_macros.hh"

namespace sjo
{

SJO_ALGORITHM_IRANGE_OITER_UNARY_COPY_ADAPTOR      (copy_until);
SJO_ALGORITHM_IRANGE_OITER_COMPARATOR_COPY_ADAPTOR (copy_until);

} // namespace sjo

#endif // SJO_ALGORITHM_COPY_UNTIL_HEADER
