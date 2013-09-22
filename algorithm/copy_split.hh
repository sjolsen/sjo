#ifndef SJO_ALGORITHM_COPY_SPLIT_HEADER
#define SJO_ALGORITHM_COPY_SPLIT_HEADER

#include <sjo/comp_ops.hh>
#include <sjo/range.hh>
#include "impl/copy_split.hh"
#include "impl/adaptor_macros.hh"

namespace sjo
{

SJO_ALGORITHM_IRANGE_OITER_UNARY_COPY_ADAPTOR      (copy_split);
SJO_ALGORITHM_IRANGE_OITER_COMPARATOR_COPY_ADAPTOR (copy_split);

} // namespace sjo

#endif // SJO_ALGORITHM_COPY_SPLIT_HEADER
