#ifndef __UTIL_VALUES__
#define __UTIL_VALUES__

#define CONVERT(value, type, method) type(mrb_funcall(mrb, value, method, 0))
#define TO_FLOAT(value) CONVERT(value, mrb_float, "to_f")
#define TO_INT(value) CONVERT(value, mrb_fixnum, "to_i")

#endif // __UTIL_VALUES__
