// dff.h
/* Rising-edge-triggered DFF */

#include "systemc.h"

SC_MODULE (dff) 
{
	sc_out<double> out_q;
	sc_in<double> in_data;
	sc_in<bool> clock, reset; // clock, reset port
	void do_dff_pos ();
	
	// Constructor
	SC_CTOR (dff) 
	{
		SC_METHOD (do_dff_pos);
		sensitive << reset;
		sensitive_pos << clock;
	}
};

