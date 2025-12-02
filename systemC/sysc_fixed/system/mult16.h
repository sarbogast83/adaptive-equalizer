// mult16.h
/* 16X16 bit mulit: out 32 bit*/
#ifndef MULIT16_H
#define MULIT16_H
#include "systemc.h"

SC_MODULE (mult16) 
{
	sc_out<sc_int<32>> out;
	sc_in<sc_int<16>> in1, in2;
	
	void do_mult ();
	
	// Constructor
	SC_CTOR (mult16) 
	{
		SC_METHOD (do_mult);
		sensitive << in1 << in2;
	}
};
#endif