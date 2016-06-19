/*
  template.h
  Numerical Array Extension for Ruby
    (C) Copyright 1999-2003 by Masahiro TANAKA

  This program is free software.
  You can distribute/modify this program
  under the same terms as Ruby itself.
  NO WARRANTY.
*/
#ifndef TEMPLATE_H
#define TEMPLATE_H

#define INIT_COUNTER( lp, c )                   \
    {   c = (lp)->n[0]; }

#define NDL_CNT(lp) ((lp)->n[0])
#define NDL_PTR(lp,i) (((lp)->args[i]).ptr + ((lp)->args[i].iter[0]).pos)
#define NDL_STP(lp,i) (((lp)->args[i].iter[0]).step)
#define NDL_IDX(lp,i) (((lp)->args[i].iter[0]).idx)
#define NDL_ESZ(lp,i) (((lp)->args[i]).elmsz)

#define INIT_PTR( lp, i, pt, st )                               \
    {                                                           \
        pt = ((lp)->args[i]).ptr + ((lp)->args[i].iter[0]).pos;         \
        st = ((lp)->args[i].iter[0]).step;                              \
    }

#define INIT_PTR_IDX( lp, i, pt, st, id )                       \
    {                                                           \
        pt = ((lp)->args[i]).ptr + ((lp)->args[i].iter[0]).pos;         \
        st = ((lp)->args[i].iter[0]).step;                              \
        id = ((lp)->args[i].iter[0]).idx;                               \
    }

#define INIT_ELMSIZE( lp, i, es )                               \
    {                                                           \
        es = ((lp)->args[i]).elmsz;                             \
    }

#define INIT_PTR_BIT( lp, i, ad, ps, st )               \
    {                                                   \
        ps = ((lp)->args[i].iter[0]).pos;                       \
        ad = (BIT_DIGIT*)(((lp)->args[i]).ptr) + ps/NB; \
        ps %= NB;                                       \
        st = ((lp)->args[i].iter[0]).step;                      \
    }

#define INIT_PTR_BIT_IDX( lp, i, ad, ps, st, id )       \
    {                                                   \
        ps = ((lp)->args[i].iter[0]).pos;                       \
        ad = (BIT_DIGIT*)(((lp)->args[i]).ptr) + ps/NB; \
        ps %= NB;                                       \
        st = ((lp)->args[i].iter[0]).step;                      \
        id = ((lp)->args[i].iter[0]).idx;                       \
    }

#define GET_DATA( ptr, type, val )                 \
    {                                              \
        val = *(type*)(ptr);                       \
    }

#define SET_DATA( ptr, type, val )                 \
    {                                              \
        *(type*)(ptr) = val;                       \
    }

#define GET_DATA_STRIDE( ptr, step, type, val )    \
    {                                              \
        val = *(type*)(ptr);                       \
        ptr += step;                               \
    }

#define GET_DATA_INDEX( ptr, idx, type, val )     \
    {                                           \
        val = *(type*)(ptr + *idx);             \
        idx++;                                  \
    }

#define SET_DATA_STRIDE( ptr, step, type, val ) \
    {                                           \
        *(type*)(ptr) = val;                    \
        ptr += step;                            \
    }

#define SET_DATA_INDEX( ptr, idx, type, val )   \
    {                                           \
        *(type*)(ptr + *idx) = val;             \
        idx++;                                  \
    }

#define LOAD_BIT( adr, pos, val )                       \
    {                                                   \
        size_t dig = (pos) / NB;                        \
        int    bit = (pos) % NB;                        \
        val = (((BIT_DIGIT*)(adr))[dig]>>(bit)) & 1u;   \
    }

#define LOAD_BIT_STEP( adr, pos, step, idx, val )       \
    {                                                   \
        size_t dig; int bit;                            \
        if (idx) {                                      \
            dig = ((pos) + *(idx)) / NB;                \
            bit = ((pos) + *(idx)) % NB;                \
            idx++;                                      \
        } else {                                        \
            dig = (pos) / NB;                           \
            bit = (pos) % NB;                           \
            pos += step;                                \
        }                                               \
        val = (((BIT_DIGIT*)(adr))[dig]>>bit) & 1u;     \
    }

#define STORE_BIT(adr,pos,val)                  \
    {                                           \
        size_t dig = (pos) / NB;                \
        int    bit = (pos) % NB;                \
        ((BIT_DIGIT*)(adr))[dig] =              \
            (((BIT_DIGIT*)(adr))[dig] & ~(1u<<(bit))) | ((val)<<(bit)); \
    }
// val -> val&1 ??

#define STORE_BIT_STEP( adr, pos, step, idx, val )\
    {                                           \
        size_t dig; int bit;                    \
        if (idx) {                              \
            dig = ((pos) + *(idx)) / NB;        \
            bit = ((pos) + *(idx)) % NB;        \
            idx++;                              \
        } else {                                \
            dig = (pos) / NB;                   \
            bit = (pos) % NB;                   \
            pos += step;                        \
        }                                       \
        ((BIT_DIGIT*)(adr))[dig] =              \
            (((BIT_DIGIT*)(adr))[dig] & ~(1u<<(bit))) | ((val)<<(bit)); \
    }
// val -> val&1 ??

#endif /* ifndef NARRAY_H */
