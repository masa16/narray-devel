typedef int32_t dtype;
typedef int32_t rtype;
#define cT  numo_cInt32
#define cRT cT

#define m_num_to_data(x) ((dtype)NUM2INT32(x))
#define m_data_to_num(x) INT322NUM((int32_t)(x))
#define m_extract(x)     INT322NUM((int32_t)*(dtype*)(x))
#define m_sprintf(s,x)   sprintf(s,"%"PRId32,(int32_t)(x))

#include "int_macro.h"
