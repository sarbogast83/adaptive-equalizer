// add32.h
/* 32 bit adder*/
#ifndef ADD32_H
#define ADD32_H
#include "systemc.h"

SC_MODULE (add32) 
{
	sc_out<sc_int<32>> out;
	sc_in<sc_int<32>> in1, in2;
	
	void do_add ();
	
	// Constructor
	SC_CTOR (add32) 
	{
		SC_METHOD (do_add);
		sensitive << in1 << in2;
	}
};
#endif