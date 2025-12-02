// mult.cc
#include "mult.h"

/* floating point multiply */

void mult::do_mult () 
{
	out.write( in1.read() * in2.read() );
}
