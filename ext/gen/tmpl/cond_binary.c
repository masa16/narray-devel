static void
<%=c_iter%>(na_loop_t *const lp)
{
    size_t  i;
    char   *p1, *p2;
    BIT_DIGIT *a3;
    size_t  p3;
    ssize_t s1, s2, s3;
    size_t *idx3;
    dtype   x, y;
    BIT_DIGIT b;
    INIT_COUNTER(lp, i);
    INIT_PTR(lp, 0, p1, s1);
    INIT_PTR(lp, 1, p2, s2);
    INIT_PTR_BIT(lp, 2, a3, p3, s3, idx3);
    for (; i--;) {
        GET_DATA_STRIDE(p1,s1,dtype,x);
        GET_DATA_STRIDE(p2,s2,dtype,y);
        b = (m_<%=method%>(x,y)) ? 1:0;
        STORE_BIT(a3,p3,b);
        p3+=s3;
    }
}

static VALUE
<%=c_func%>_self(VALUE self, VALUE other)
{
    ndfunc_arg_in_t ain[2] = {{cT,0},{cT,0}};
    ndfunc_arg_out_t aout[1] = {{cBit,0}};
    ndfunc_t ndf = { <%=c_iter%>, STRIDE_LOOP, 2, 1, ain, aout };

    return na_ndloop(&ndf, 2, self, other);
}

/*
  Comparison <%=method%> other.
  @overload <%=op_map%> other
  @param [NArray,Numeric] other
  @return [NArray::Bit] result of self <%=method%> other.
*/
static VALUE
<%=c_func%>(VALUE self, VALUE other)
{
    VALUE klass, v;
    klass = na_upcast(CLASS_OF(self),CLASS_OF(other));
    if (klass==cT) {
        return <%=c_func%>_self(self, other);
    } else {
        v = rb_funcall(klass, id_cast, 1, self);
        return rb_funcall(v, id_<%=method%>, 1, other);
    }
}
