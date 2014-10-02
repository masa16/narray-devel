#include "xint_macro.h"

#define m_abs(x)     ((x<0)?-x:x)

static inline dtype int_inverse(dtype x) {
    switch (x) {
    case 1:
        return 1;
    case -1:
        return -1;
    case 0:
        rb_raise(rb_eZeroDivError, "divided by 0");
    default:
        return 0;
    }
}

static dtype pow_int(dtype x, int p)
{
    dtype r = m_one;
    switch(p) {
    case 0: return 1;
    case 1: return x;
    case 2: return x*x;
    case 3: return x*x*x;
    }
    if (p<0) return 0;
    while (p) {
        if (p&1) r *= x;
        x *= x;
        p >>= 1;
    }
    return r;
}
