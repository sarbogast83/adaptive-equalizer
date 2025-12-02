// Direct Form Computational Cell
#ifndef FIR_CELL_DF_H
#define FIR_CELL_DF_H

#include "systemc.h"
#include "add.h"
#include "mult.h"
#include "dff.h"

SC_MODULE (FIRcellDF) 
{ 
	
	sc_in<bool> clock, reset;
	sc_in<double> rk;
	sc_in<double> bk;
	sc_in<double> sk;
	sc_out<double> rkp1;
	sc_out<double> skp1;
	

	sc_signal<double> mk;
	
	// Create data members - 
	// pointers to instantiated modules
	dff *U_dff;
	mult *U_mult;
	add *U_add;
	
	// Constructor
	SC_CTOR (FIRcellDF) 
	{
		// Create new instances of dff, mult, and add modules
		U_dff = new dff("U_dff");
		U_mult = new mult("U_mult");
		U_add = new add("U_add");
		
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
