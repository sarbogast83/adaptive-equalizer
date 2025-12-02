// Direct Form Computational Cell

#ifndef FIR_CELL_DF_H
#define FIR_CELL_DF_H

#include "systemc.h"
#include "mult16.h"
#include "add32.h"
#include "dff_gen_int.h"

SC_MODULE (FIRcellDF) 
{ 
	
	sc_in<bool> clock, reset;
	sc_in<sc_int<16>> rk;
	sc_in<sc_int<16>> bk;
	sc_in<sc_int<32>> sk;
	sc_out<sc_int<16>> rkp1;
	sc_out<sc_int<32>> skp1;
	

	sc_signal<sc_int<32>> mk;
	
	// Create data members - 
	// pointers to instantiated modules
	dff_gen_int<16> *U_dff;
	mult16 *U_mult;
	add32 *U_add;
	
	// Constructor
	SC_CTOR (FIRcellDF) 
	{
		// Create new instances of dff, mult, and add modules
		U_dff = new dff_gen_int<16>("U_dff");
		U_mult = new mult16("U_mult");
		U_add = new add32("U_add");
		
		// Bind the signals and ports to the cell elements
		U_dff -> clock(clock);
		U_dff -> reset(reset);
		U_dff -> in_data(rk);
		U_dff -> out_q(rkp1);
		
		U_mult -> in1(rk);
		U_mult -> in2(bk);
		U_mult -> out(mk);
		
		U_add -> in1(sk);
		U_add -> in2(mk);
		U_add -> out(skp1);
	}
};
#endif
