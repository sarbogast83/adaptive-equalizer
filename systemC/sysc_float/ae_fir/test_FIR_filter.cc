// test_FIR_filter.cc
#include "AE_FIR_DF.h"
#include <fstream>
#include <systemc.h>
#include <iomanip>


int sc_main (int argc , char *argv[]) {
  
	FILE *x_fp, *b_fp; // file pointers for data signal and coeffs.
	
	sc_signal<bool> reset, clock;
	sc_signal<double> xn;
	sc_signal<double> yn;
	sc_signal<double> u0;
	sc_signal<double> u1;
	sc_signal<double> u2;
	sc_signal<double> u3;
	sc_signal<double> u4;
	sc_signal<double> u5;
	sc_signal<double> u6;
	sc_signal<double> u7;
	sc_signal<double> u8;
	sc_signal<double> u9;
	sc_signal<double> u10;
	sc_signal<double> u11;
	sc_signal<double> grnd;
	
	int x_Len, y_Len, b_Len, i, j;
	double tmp_x, tmp_b;
	char s[300];
	
	// Opening the data and coefficient files
	x_fp = fopen("xn.txt","r");
	b_fp = fopen("bk.txt","r");
	
	// This format for writing to a file works for outputing
	// sc_signals. Use fout instead of fprintf
	ofstream fout_yn("yn.txt");
	ofstream fout_un("un.txt"); 
	
	// Reading in the size of the data samples and the coeffs
	// to determine the sizes of the arrays
	if (fgets(s,100,x_fp)!=NULL)
		sscanf(s,"%d", &x_Len);
	printf("x_Len = %d\n", x_Len);
	
	if (fgets(s,100,b_fp)!=NULL)
		sscanf(s,"%d", &b_Len);
	printf("b_Len = %d\n", b_Len);
	
	y_Len = x_Len + b_Len - 1; // Defining the length of the output
	
	grnd = 0.0;
	
	// Declaring the sizes of the data arrays.
	double x[x_Len];
	sc_signal<double> b[b_Len];
	
	/************** Binding *****************/
	// Binding by name. Order does not matter
	AE_FIR_DF U_FIR_DF( "U_FIR_DF");
	//in
	U_FIR_DF.clock(clock);
	U_FIR_DF.reset(reset);
	U_FIR_DF.xn(xn);
	U_FIR_DF.grnd(grnd);
	U_FIR_DF.b0(b[0]);
	U_FIR_DF.b1(b[1]);
	U_FIR_DF.b2(b[2]);
	U_FIR_DF.b3(b[3]);
	U_FIR_DF.b4(b[4]);
	U_FIR_DF.b5(b[5]);
	U_FIR_DF.b6(b[6]);
	U_FIR_DF.b7(b[7]);
	U_FIR_DF.b8(b[8]);
	U_FIR_DF.b9(b[9]);
	U_FIR_DF.b10(b[10]);
	U_FIR_DF.b11(b[11]);
	//out
	U_FIR_DF.yn(yn);
	U_FIR_DF.u0(u0);
	U_FIR_DF.u1(u1);
	U_FIR_DF.u2(u2);
	U_FIR_DF.u3(u3);
	U_FIR_DF.u4(u4);
	U_FIR_DF.u5(u5);
	U_FIR_DF.u6(u6);
	U_FIR_DF.u7(u7);
	U_FIR_DF.u8(u8);
	U_FIR_DF.u9(u9);
	U_FIR_DF.u10(u10);
	U_FIR_DF.u11(u11);

	/**************  End Binding **************/
	
	sc_start(SC_ZERO_TIME);
	
	/*************   Reading files    *********/
	// Reading in the data sequence
	i = 0;
	tmp_x = 0;
	while (fgets(s,100,x_fp)!=NULL)
	{
		sscanf(s,"%lf", &tmp_x);
		x[i] = tmp_x;
		i++;
	}
	
	// Reading in the coefficients sequence
  	i = 0;
  	tmp_b = 0;
	while (fgets(s,300,b_fp)!=NULL)
	{
		sscanf(s,"%lf", &tmp_b);
		b[i] = tmp_b;
		i++;
	}
	/************ End Reading files **********/
	
	// Resetting the entire system
	clock = 0;
	sc_start(5, SC_NS); // Default unit nanosecond
	clock = 1;
	sc_start(2, SC_NS);
	reset = 1;
	sc_start(3, SC_NS);
	clock = 0;
	sc_start(5, SC_NS);
	clock = 1;
	sc_start(5, SC_NS);
	clock = 0;
	sc_start(5, SC_NS);
	clock = 1;
	sc_start(5, SC_NS);
	reset = 0;
	clock = 0;
	
	// Experiment with sc_trace
	sc_trace_file* file = sc_create_vcd_trace_file("trace");
	sc_trace(file, clock, "clock");
	sc_trace(file, reset, "reset");
	
	/********* Begin Processing Loop *************/
	for (j = 0; j<y_Len+2 ; j++)
	{	
		reset = 0;
		
		clock = 0;
		sc_start(5, SC_NS);
		clock = 1;
		sc_start(2, SC_NS);
		
		if(j<x_Len)
			xn = x[j];
		else
			xn = 0;
		
		sc_start(3, SC_NS);
		
		cout << "xn = " << xn << "\tyn = " << yn << "\n";
		
		fout_yn << std::setprecision (3) << yn << "\n";
		fout_un << std::setprecision (3) << u0 << " " << u1 << " " << u2 << " " << u3 << " "
										 << u4 << " " << u5 << " " << u6 << " " << u7 << " "
										 << u8 << " " << u9 << " " << u10 << " " << u11 << "\n";
		

	
	}
	/********** End Processing Loop  ************/
	sc_close_vcd_trace_file(file);
	return 0;
};

