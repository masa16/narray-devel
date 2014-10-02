static void
<%=c_iter%>(na_loop_t *const lp)
{
    size_t   i, n;
    char    *p1, *p2, *p3, *p4;
    ssize_t  s1, s2, s3, s4;
    dtype    x, y, a, b;
    INIT_COUNTER(lp, n);
    INIT_PTR(lp, 0, p1, s1);
    INIT_PTR(lp, 1, p2, s2);
    INIT_PTR(lp, 2, p3, s3);
    INIT_PTR(lp, 3, p4, s4);
    for (i=n; i--;) {
        GET_DATA_STRIDE(p1,s1,dtype,x);
        GET_DATA_STRIDE(p2,s2,dtype,y);
<% if is_int and %w[divmod].include? method %>
        if (y==0) {
            lp->err_type = rb_eZeroDivError;
            return;
        }
<% end %>
        m_<%=method%>(x,y,a,b);
        SET_DATA_STRIDE(p3,s3,dtype,a);
        SET_DATA_STRIDE(p4,s4,dtype,b);
    }
}

static VALUE
<%=c_func%>_self(VALUE self, VALUE other)
{
    ndfunc_arg_in_t ain[2] = {{cT,0},{cT,0}};
    ndfunc_arg_out_t aout[2] = {{cT,0},{cT,0}};
    ndfunc_t ndf = { <%=c_iter%>, STRIDE_LOOP, 2, 2, ain, aout };

    return na_ndloop(&ndf, 2, self, other);
}

/*
  Binary <%=method%>.
  @overload <%=op_map%> other
  @param [NArray,Numeric] other
  @return [NArray] <%=method%> of self and other.
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
        return rb_funcall(v, <%=id_op%>, 1, other);
    }
}
