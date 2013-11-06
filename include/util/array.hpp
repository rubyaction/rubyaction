#ifndef __UTIL_ARRAY__
#define __UTIL_ARRAY__

#include "util/values.hpp"

#define A_GET_VALUE(array, idx) mrb_ary_ref(mrb, array, idx)
#define A_GET_FLOAT(array, idx) TO_FLOAT(A_GET_VALUE(array, idx))
#define A_GET_INT(array, idx) TO_INT(A_GET_VALUE(array, idx))

#endif // __UTIL_ARRAY__
