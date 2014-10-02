/*
  ndloop.h
  Numerical Array Extension for Ruby
    (C) Copyright 1999-2011 by Masahiro TANAKA

  This program is free software.
  You can distribute/modify this program
  under the same terms as Ruby itself.
  NO WARRANTY.
*/
#ifndef NDLOOP_H
#define NDLOOP_H

typedef struct NA_LOOP_ARGS {
    VALUE    value;
    ssize_t  elmsz;
    char    *ptr;
    size_t  *shape;
} na_loop_args_t;

typedef struct NA_LOOP_ITER {
    ssize_t    pos;
    ssize_t    step;
    size_t    *idx;
} na_loop_iter_t;

typedef struct NA_LOOP {
    int  narg;
    int  ndim;             // n of user dimention
    size_t *n;             // n of elements for each dim
    na_loop_args_t *args;  // for each arg
    na_loop_iter_t *iter;  // for each dim, each arg
    VALUE  option;
    void  *opt_ptr;
    VALUE  err_type;
} na_loop_t;



#define LITER(lp,idim,iarg) ((lp)->iter[(idim)*((lp)->narg)+(iarg)])

// ------------------ ndfunc -------------------------------------------

#define NDF_HAS_LOOP            (1<<0) // x[i]
#define NDF_STRIDE_LOOP         (1<<1) // *(x+stride*i)
#define NDF_INDEX_LOOP          (1<<2) // *(x+idx[i])
#define NDF_KEEP_DIM            (1<<3)
#define NDF_INPLACE             (1<<4)
#define NDF_ACCEPT_BYTESWAP     (1<<5)

#define NDF_HAS_REDUCE_DIM      (1<<6)

#define FULL_LOOP       (NDF_HAS_LOOP|NDF_STRIDE_LOOP|NDF_INDEX_LOOP|NDF_INPLACE)
#define FULL_LOOP_NIP   (NDF_HAS_LOOP|NDF_STRIDE_LOOP|NDF_INDEX_LOOP)
#define STRIDE_LOOP     (NDF_HAS_LOOP|NDF_STRIDE_LOOP|NDF_INPLACE)
#define STRIDE_LOOP_NIP (NDF_HAS_LOOP|NDF_STRIDE_LOOP)
#define NO_LOOP         0
#define HAS_REDUCE      NDF_HAS_REDUCE_DIM

#define NDF_TEST(nf,fl)  ((nf)->flag&(fl))
#define NDF_SET(nf,fl)  {(nf)->flag |= (fl);}

#define NDF_ARG_READ_ONLY   1
#define NDF_ARG_WRITE_ONLY  2
#define NDF_ARG_READ_WRITE  3

// type of user function
typedef void (*na_iter_func_t) _((na_loop_t *const));
typedef VALUE (*na_text_func_t) _((char *ptr, size_t pos, VALUE opt));
//typedef void (*) void (*loop_func)(ndfunc_t*, na_md_loop_t*))


typedef struct NDF_ARG_IN {
    VALUE   type;    // argument types
    int     dim;     // # of dimension of argument handled by user function
} ndfunc_arg_in_t;

typedef struct NDF_ARG_OUT {
    VALUE   type;    // argument types
    int     dim;     // # of dimension of argument handled by user function
    size_t *shape;
} ndfunc_arg_out_t;

// spec of user function
typedef struct NDFUNCTION {
    na_iter_func_t func;    // user function
    unsigned int flag;      // what kind of loop user function supports
    int nin;                // # of arguments
    int nout;               // # of results
    ndfunc_arg_in_t *ain;   // spec of input arguments
    ndfunc_arg_out_t *aout; // spec of output result
} ndfunc_t;


#define NDF_TEST(nf,fl)  ((nf)->flag&(fl))
#define NDF_SET(nf,fl)  {(nf)->flag |= (fl);}


// ------------------ na_md_loop_t ----------------------------------------

typedef struct NA_MD_LOOP {
    int  narg;
    int  nin;
    int  ndim;             // n of total dimention
    unsigned int copy_flag;
    size_t  *n;            // n of elements for each dim
    na_loop_args_t *args;  // for each arg
    na_loop_iter_t *iter;  // for each dim, each arg
    na_loop_t  user;       // loop in user function
    int    writeback;
    VALUE  vargs;
    VALUE  reduce;
    VALUE  loop_opt;
    ndfunc_t  *ndfunc;
    void (*loop_func)();
} na_md_loop_t;

#define OVERWRITE Qtrue
#define CASTABLE(t) (RTEST(t) && (t)!=OVERWRITE)

#endif /* NDLOOP_H */
