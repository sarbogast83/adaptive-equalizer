//test_CUunit.cc

#include <fstream>
#include <systemc.h>
#include <iomanip>

#include "CUunit.h"

int sc_main (int argc , char *argv[]) 
{
  
	FILE *u_fp, *e_fp; // file pointers for data signal and coeffs.
	
	sc_signal<bool> reset, clock;
	sc_signal<double> en, mu;
    sc_signal<double> u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11;
	sc_signal<double> w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11;
	
	int u_Len, y_Len, e_Len, i, j;
	double tmp_u, tmp_e;
	char s[300];
	
	// Opening the data and coefficient files
	u_fp = fopen("un.txt","r");
	e_fp = fopen("en.txt","r");
	
	
	// This format for writing to a file works for outputing
	// sc_signals. Use fout instead of fprintf
	ofstream fout_wn("wn.txt");
	
	
	// Reading in the size of the data samples and the coeffs
	// to determine the sizes of the arrays
	if (fgets(s,100,u_fp)!=NULL)
		sscanf(s,"%d", &u_Len);
	printf("u_Len = %d\n", u_Len);

	if (fgets(s,100,e_fp)!=NULL)
		sscanf(s,"%d", &e_Len);
	printf("e_Len = %d\n", e_Len);

	
	y_Len = u_Len + 6; // Defining the length of the output
	
	
	// Declaring the sizes of the data arrays.
	double u[u_Len];
	double e[e_Len];
	
	/************** Binding *****************/
	// Binding by name. Order does not matter
	CUunit U_CUunit("U_CUunit");

	U_CUunit.clock(clock);
	U_CUunit.reset(reset);
	U_CUunit.mu(mu);
	U_CUunit.en(en);
	U_CUunit.u0(u0);
    U_CUunit.u1(u1);
    U_CUunit.u2(u2);
    U_CUunit.u3(u3);
    U_CUunit.u4(u4);
    U_CUunit.u5(u5);
    U_CUunit.u6(u6);
    U_CUunit.u7(u7);
    U_CUunit.u8(u8);
    U_CUunit.u9(u9);
    U_CUunit.u10(u10);
    U_CUunit.u11(u11);
    //out
	U_CUunit.w0(w0);
    U_CUunit.w1(w1);
    U_CUunit.w2(w2);
    U_CUunit.w3(w3);
    U_CUunit.w4(w4);
    U_CUunit.w5(w5);
    U_CUunit.w6(w6);
    U_CUunit.w7(w7);
    U_CUunit.w8(w8);
    U_CUunit.w9(w9);
    U_CUunit.w10(w10);
    U_CUunit.w11(w11);



	/**************  End Binding **************/
	
	sc_start(SC_ZERO_TIME);
	
	/*************   Reading files    *********/
	// Reading in the data sequence
	mu = 0.03;
	i = 0;
	tmp_u = 0;
	while (fgets(s,100,u_fp)!=NULL)
	{
		sscanf(s,"%lf", &tmp_u);
		u[i] = tmp_u;
		i++;
	}

	
	// Reading in the coefficients sequence
  	i = 0;
  	tmp_e = 0;
	while (fgets(s,300,e_fp)!=NULL)
	{
		sscanf(s,"%lf", &tmp_e);
		e[i] = tmp_e;
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
		
		if(j<u_Len){
			u0 = u[j+11];
            u1 = u[j+10];
            u2 = u[j+9];
            u3 = u[j+8];
            u4 = u[j+7];
            u5 = u[j+6];
            u6 = u[j+5];
            u7 = u[j+4];
            u8 = u[j+3];
            u9 = u[j+2];
            u10 = u[j+1];
			u11 = u[j];
            en = e[j];}
		else{
			u0 = 0;
            u1 = 0;
            u2 = 0;
            u3 = 0;
            u4 = 0;
            u5 = 0;
            u6 = 0;
            u7 = 0;
            u8 = 0;
            u9 = 0;
            u10 = 0;
            u11 = 0;
			en = 0;}
		
		sc_start(3, SC_NS);
		
		cout << u0 << " " << u1 << " " << u2 << " " << u3 << " "
             << u4 << " " << u5 << " " << u6 << " " << u7 << " "
             << u8 << " " << u9 << " " << u10 << " " << u11 << "\n";
         		
		fout_wn << std::setprecision (5) << w0 << " " << w1 << " " << w2 << " " << w3 << " "
                                         << w4 << " " << w5 << " " << w6 << " " << w7 << " "
                                         << w8 << " " << w9 << " " << w10 << " " << w11 << "\n";
	
	
	}
	/********** End Processing Loop  ************/
	sc_close_vcd_trace_file(file);
	return 0;
};