// add32.cc
#include "add32.h"

/* 32 bit adder */

void add32::do_add () 
{
	out.write( in1.read() + in2.read() );
}
