// floating point subtraction 

#include <systemc.h>
#include "sub.h"

void sub::do_sub()
{
    diff.write( minu.read() - subt.read());
}