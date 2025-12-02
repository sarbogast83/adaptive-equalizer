//scdl.cc
#include "scdl.h"

void scdl::do_scd()
{
    sc_int<32> word = in.read();
    out.write(word >> lsb.read());
} 