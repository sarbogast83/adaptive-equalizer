// mult.cc
#include "mult16.h"

/* floating point multiply */

void mult16::do_mult () 
{
	out.write( in1.read() * in2.read() );
}
