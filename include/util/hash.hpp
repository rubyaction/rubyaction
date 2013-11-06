#ifndef __UTIL_HASH__
#define __UTIL_HASH__

#define H_GET_VALUE(hash, key) mrb_hash_get(mrb, hash, mrb_symbol_value(mrb_intern(mrb, key)))
#define H_GET_VALUE_DEF(hash, key, def) mrb_hash_fetch(mrb, hash, mrb_symbol_value(mrb_intern(mrb, key)), def)

#endif // __UTIL_HASH__
