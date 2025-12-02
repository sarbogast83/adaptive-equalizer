// mult.h
/* floating point multiply */
#ifndef MULT_H
#define MULT_H

#include "systemc.h"

SC_MODULE (mult) 
{
	sc_out<double> out;
	sc_in<double> in1, in2;
	
	void do_mult ();
	
	// Constructor
	SC_CTOR (mult) 
	{
		SC_METHOD (do_mult);
		sensitive << in1 << in2;
	}
};
#endif