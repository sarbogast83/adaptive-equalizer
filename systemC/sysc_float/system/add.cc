// add.cc
#include "add.h"

/* floating point add */

void add::do_add () 
{
	out.write( in1.read() + in2.read() );
}
