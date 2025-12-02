// add16.h
/* 16 bit adder*/
#ifndef ADD16_H
#define ADD16_H

#include "systemc.h"

SC_MODULE (add16) 
{
	sc_out<sc_int<16>> out;
	sc_in<sc_int<16>> in1, in2;
	
	void do_add ();
	
	// Constructor
	SC_CTOR (add16) 
	{
		SC_METHOD (do_add);
		sensitive << in1 << in2;
	}
};
#endif