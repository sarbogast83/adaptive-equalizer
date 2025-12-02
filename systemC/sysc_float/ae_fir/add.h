// add.h
/* floating point add */

#include "systemc.h"

SC_MODULE (add) 
{
	sc_out<double> out;
	sc_in<double> in1, in2;
	
	void do_add ();
	
	// Constructor
	SC_CTOR (add) 
	{
		SC_METHOD (do_add);
		sensitive << in1 << in2;
	}
};
