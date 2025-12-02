// dff.cc
#include "dff.h"
/* Rising-edge-triggered DFF */

void dff::do_dff_pos () 
{
	if (reset.read())
	{
		out_q = 0;
	}
	else
	{
		out_q = in_data;
	}
}
