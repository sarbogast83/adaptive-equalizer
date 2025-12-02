/************************************
 * 
 * AE_FIR_DF.h
 * 
 * 12-tap adaptive fitler designed with DF FIR
 *
 * Requires: FIRcellDF
 * input:  
 * 		xn: data
 * 	    b: coef
 * 
 * output:
 * 		un: delayed xn
 * 		yn: filtered data
 * 
 ********************************************/
#ifndef AE_FIR_DF_H
#define AE_FIR_DF_H

#include "systemc.h"
#include "driver.h"
#include "FIRcellDF.h"

SC_MODULE (AE_FIR_DF) 
{
	sc_in<bool> clock, reset;
	
	sc_in<double> xn;
	sc_in<double> b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11;
	sc_in<double> grnd;
	
	sc_out<double> u0, u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11;
	sc_out<double> yn;
	
	//sc_signal<double> u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11;
	sc_signal<double> r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11;
	sc_signal<double> s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
	sc_signal<double> p1;

	// Create data members - pointers to instantiated modules
	FIRcellDF *FIRcellDF_U0, *FIRcellDF_U1, *FIRcellDF_U2, *FIRcellDF_U3, 
		*FIRcellDF_U4, *FIRcellDF_U5, *FIRcellDF_U6, *FIRcellDF_U7, 
		*FIRcellDF_U8, *FIRcellDF_U9, *FIRcellDF_U10, *FIRcellDF_U11;
	
	driver *Drive_U0, *Drive_U1, *Drive_U2, *Drive_U3, *Drive_U4
			, *Drive_U5, *Drive_U6, *Drive_U7, *Drive_U8, *Drive_U9
			, *Drive_U10, *Drive_U11;

	// Constructor
	SC_CTOR (AE_FIR_DF) 
	{
		// Create new instances of DFF and cells
		
		FIRcellDF_U0 = new FIRcellDF("FIRcellDF_U0");
		FIRcellDF_U1 = new FIRcellDF("FIRcellDF_U1");
		FIRcellDF_U2 = new FIRcellDF("FIRcellDF_U2");
		FIRcellDF_U3 = new FIRcellDF("FIRcellDF_U3");
		FIRcellDF_U4 = new FIRcellDF("FIRcellDF_U4");
		FIRcellDF_U5 = new FIRcellDF("FIRcellDF_U5");
		FIRcellDF_U6 = new FIRcellDF("FIRcellDF_U6");
		FIRcellDF_U7 = new FIRcellDF("FIRcellDF_U7");
		FIRcellDF_U8 = new FIRcellDF("FIRcellDF_U8");
		FIRcellDF_U9 = new FIRcellDF("FIRcellDF_U9");
		FIRcellDF_U10 = new FIRcellDF("FIRcellDF_U10");
		FIRcellDF_U11 = new FIRcellDF("FIRcellDF_U11");
		
		Drive_U0 = new driver("Drive_U0");
		Drive_U1 = new driver("Drive_U1");
		Drive_U2 = new driver("Drive_U2");
		Drive_U3 = new driver("Drive_U3");
		Drive_U4 = new driver("Drive_U4");
		Drive_U5 = new driver("Drive_U5");
		Drive_U6 = new driver("Drive_U6");
		Drive_U7 = new driver("Drive_U7");
		Drive_U8 = new driver("Drive_U8");	
		Drive_U9 = new driver("Drive_U9");
		Drive_U10 = new driver("Drive_U10");
		Drive_U11 = new driver("Drive_U11");
		
		FIRcellDF_U0 -> clock(clock);
		FIRcellDF_U0 -> reset(reset);
		FIRcellDF_U0 -> rk(xn);
		FIRcellDF_U0 -> sk(grnd);
		FIRcellDF_U0 -> bk(b0);
		FIRcellDF_U0 -> rkp1(r0);
		FIRcellDF_U0 -> skp1(s0);
		
		FIRcellDF_U1 -> clock(clock);
		FIRcellDF_U1 -> reset(reset);
		FIRcellDF_U1 -> rk(r0);
		FIRcellDF_U1 -> sk(s0);
		FIRcellDF_U1 -> bk(b1);
		FIRcellDF_U1 -> rkp1(r1);
		FIRcellDF_U1 -> skp1(s1);
		
		FIRcellDF_U2 -> clock(clock);
		FIRcellDF_U2 -> reset(reset);
		FIRcellDF_U2 -> rk(r1);
		FIRcellDF_U2 -> sk(s1);
		FIRcellDF_U2 -> bk(b2);
		FIRcellDF_U2 -> rkp1(r2);
		FIRcellDF_U2 -> skp1(s2);
		
		FIRcellDF_U3 -> clock(clock);
		FIRcellDF_U3 -> reset(reset);
		FIRcellDF_U3 -> rk(r2);
		FIRcellDF_U3 -> sk(s2);
		FIRcellDF_U3 -> bk(b3);
		FIRcellDF_U3 -> rkp1(r3);
		FIRcellDF_U3 -> skp1(s3);
		
		FIRcellDF_U4 -> clock(clock);
		FIRcellDF_U4 -> reset(reset);
		FIRcellDF_U4 -> rk(r3);
		FIRcellDF_U4 -> sk(s3);
		FIRcellDF_U4 -> bk(b4);
		FIRcellDF_U4 -> rkp1(r4);
		FIRcellDF_U4 -> skp1(s4);
		
		FIRcellDF_U5 -> clock(clock);
		FIRcellDF_U5 -> reset(reset);
		FIRcellDF_U5 -> rk(r4);
		FIRcellDF_U5 -> sk(s4);
		FIRcellDF_U5 -> bk(b5);
		FIRcellDF_U5 -> rkp1(r5);
		FIRcellDF_U5 -> skp1(s5);
		
		FIRcellDF_U6 -> clock(clock);
		FIRcellDF_U6 -> reset(reset);
		FIRcellDF_U6 -> rk(r5);
		FIRcellDF_U6 -> sk(s5);
		FIRcellDF_U6 -> bk(b6);
		FIRcellDF_U6 -> rkp1(r6);
		FIRcellDF_U6 -> skp1(s6);
		
		FIRcellDF_U7 -> clock(clock);
		FIRcellDF_U7 -> reset(reset);
		FIRcellDF_U7 -> rk(r6);
		FIRcellDF_U7 -> sk(s6);
		FIRcellDF_U7 -> bk(b7);
		FIRcellDF_U7 -> rkp1(r7);
		FIRcellDF_U7 -> skp1(s7);
		
		FIRcellDF_U8 -> clock(clock);
		FIRcellDF_U8 -> reset(reset);
		FIRcellDF_U8 -> rk(r7);
		FIRcellDF_U8 -> sk(s7);
		FIRcellDF_U8 -> bk(b8);
		FIRcellDF_U8 -> rkp1(r8);
		FIRcellDF_U8 -> skp1(s8);
		
		FIRcellDF_U9 -> clock(clock);
		FIRcellDF_U9 -> reset(reset);
		FIRcellDF_U9 -> rk(r8);
		FIRcellDF_U9 -> sk(s8);
		FIRcellDF_U9 -> bk(b9);
		FIRcellDF_U9 -> rkp1(r9);
		FIRcellDF_U9 -> skp1(s9);
		
		FIRcellDF_U10 -> clock(clock);
		FIRcellDF_U10 -> reset(reset);
		FIRcellDF_U10 -> rk(r9);
		FIRcellDF_U10 -> sk(s9);
		FIRcellDF_U10 -> bk(b10);
		FIRcellDF_U10 -> rkp1(r10);
		FIRcellDF_U10 -> skp1(s10);

		FIRcellDF_U11 -> clock(clock);
		FIRcellDF_U11 -> reset(reset);
		FIRcellDF_U11 -> rk(r10);
		FIRcellDF_U11 -> sk(s10);
		FIRcellDF_U11 -> bk(b11);
		FIRcellDF_U11 -> rkp1(r11);
		FIRcellDF_U11 -> skp1(yn);

		// passing data
		Drive_U0 -> in_data(xn);
		Drive_U0 -> out_data(u0);
		
		Drive_U1 -> in_data(r0);
		Drive_U1 -> out_data(u1);

		Drive_U2 -> in_data(r1);
		Drive_U2 -> out_data(u2);

		Drive_U3 -> in_data(r2);
		Drive_U3 -> out_data(u3);

		Drive_U4 -> in_data(r3);
		Drive_U4 -> out_data(u4);

		Drive_U5 -> in_data(r4);
		Drive_U5 -> out_data(u5);

		Drive_U6 -> in_data(r5);
		Drive_U6 -> out_data(u6);

		Drive_U7 -> in_data(r6);
		Drive_U7 -> out_data(u7);

		Drive_U8 -> in_data(r7);
		Drive_U8 -> out_data(u8);

		Drive_U9 -> in_data(r8);
		Drive_U9 -> out_data(u9);

		Drive_U10 -> in_data(r9);
		Drive_U10 -> out_data(u10);

		Drive_U11 -> in_data(r10);
		Drive_U11 -> out_data(u11);


	}
};
#endif