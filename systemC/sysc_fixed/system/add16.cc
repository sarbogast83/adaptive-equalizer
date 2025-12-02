// add16.cc
#include "add16.h"

/* 16 bit adder */

void add16::do_add () 
{
	out.write( in1.read() + in2.read() );
}
