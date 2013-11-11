#ifndef __UTIL_VALUES__
#define __UTIL_VALUES__

#define TO_FLOAT(value) mrb_float(mrb_Float(mrb, value))
#define TO_INT(value) mrb_fixnum(mrb_Integer(mrb, value))

#endif // __UTIL_VALUES__
