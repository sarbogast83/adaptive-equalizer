// dff_gen_int.h
/* Rising-edge-triggered DFF */

#ifndef DFF_GEN_INT_H
#define DFF_GEN_INT_H

#include "systemc.h"


template<int word_size>
SC_MODULE (dff_gen_int) 
{
	sc_out<sc_int<word_size>> out_q;
	sc_in<sc_int<word_size>> in_data;
	sc_in<bool> clock, reset; // clock, reset port
	void do_dff_pos ();
	
	// Constructor
	SC_CTOR (dff_gen_int) 
	{
		SC_METHOD (do_dff_pos);
		sensitive << reset;
		sensitive_pos << clock;
	}
};

template<int word_size>
void dff_gen_int<word_size>::do_dff_pos () 
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
#endif