typedef u_int16_t dtype;
typedef u_int16_t rtype;
#define cT  cUInt16
#define cRT cT

#define m_num_to_data(x) ((dtype)NUM2UINT(x))
#define m_data_to_num(x) UINT2NUM((unsigned int)(x))
#define m_extract(x)     UINT2NUM((unsigned int)*(dtype*)(x))
#define m_sprintf(s,x)   sprintf(s,"%"INT32FMT"u",(u_int32_t)(x))
#define m_rand           ((dtype)gen_rand32())

#include "uint_macro.h"
