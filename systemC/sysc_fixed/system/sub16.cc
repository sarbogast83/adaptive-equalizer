// floating point subtraction 

#include <systemc.h>
#include "sub16.h"

void sub16::do_sub()
{
    diff.write( minu.read() - subt.read());
}