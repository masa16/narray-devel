require 'rbconfig.rb'
require 'mkmf'
require "erb"

if RUBY_VERSION < "2.0.0"
  puts "Numo::NArray requires Ruby version 2.0 or later."
  exit(1)
end

rm_f 'numo/extconf.h'

#$CFLAGS="-g3 -O0 -Wall"
#$CFLAGS=" $(cflags) -O3 -m64 -msse2 -funroll-loops"
#$CFLAGS=" $(cflags) -O3"
$INCFLAGS = "-Itypes #$INCFLAGS"

$INSTALLFILES = Dir.glob(%w[numo/*.h numo/types/*.h]).map{|x| [x,'$(archdir)'] }
$INSTALLFILES << ['numo/extconf.h','$(archdir)']
if /cygwin|mingw/ =~ RUBY_PLATFORM
  $INSTALLFILES << ['libnarray.a', '$(archdir)']
end

if enable_config("gcov")
  $CFLAGS += " -coverage"
  $LDFLAGS += " -coverage"
end

srcs = %w(
narray
array
step
index
ndloop
data
types/bit
types/int8
types/int16
types/int32
types/int64
types/uint8
types/uint16
types/uint32
types/uint64
types/sfloat
types/dfloat
types/scomplex
types/dcomplex
types/robject
math
SFMT
struct
rand
)

if have_header("stdbool.h")
  stdbool = "stdbool.h"
else
  stdbool = nil
end

if have_header("stdint.h")
  stdint = "stdint.h"
elsif have_header("sys/types.h")
  stdint = "sys/types.h"
else
  stdint = nil
end

have_type("bool", stdbool)
unless have_type("u_int8_t", stdint)
  have_type("uint8_t",stdint)
end
unless have_type("u_int16_t", stdint)
  have_type("uint16_t",stdint)
end
have_type("int32_t", stdint)
unless have_type("u_int32_t", stdint)
  have_type("uint32_t",stdint)
end
have_type("int64_t", stdint)
unless have_type("u_int64_t", stdint)
  have_type("uint64_t", stdint)
end
have_func("exp10")

have_var("rb_cComplex")
have_var("rb_cFixnum")

$objs = srcs.collect{|i| i+".o"}

create_header('numo/extconf.h')

depend_path = File.join(__dir__, "depend")
File.open(depend_path, "w") do |depend|
  depend_erb_path = File.join(__dir__, "depend.erb")
  File.open(depend_erb_path, "r") do |depend_erb|
    erb = ERB.new(depend_erb.read)
    erb.filename = depend_erb_path
    depend.print(erb.result)
  end
end

create_makefile('numo/narray')
