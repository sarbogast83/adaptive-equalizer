// test_CUcell.cc
#include "CUcell.h"
#include <fstream>
#include <systemc.h>
#include <iomanip>


int sc_main (int argc , char *argv[]) 
{
  
	FILE *u_fp, *e_fp; // file pointers for data signal and coeffs.
	
	sc_signal<bool> reset, clock;
	sc_signal<double> xn, yn, un, en, mu;
	
	
	int u_Len, y_Len, e_Len, i, j;
	double tmp_u, tmp_e;
	char s[300];
	
	// Opening the data and coefficient files
	u_fp = fopen("un.txt","r");
	e_fp = fopen("en.txt","r");
	
	
	// This format for writing to a file works for outputing
	// sc_signals. Use fout instead of fprintf
	ofstream fout_yn("yn.txt");
	
	
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
	CUcell U_CUcell("U_CUcell");

	U_CUcell.clock(clock);
	U_CUcell.reset(reset);
	U_CUcell.mu(mu);
	U_CUcell.en(en);
	U_CUcell.un(un);
	U_CUcell.wnp1(yn);


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
			un = u[j];
			en = e[j];}
		else{
			un = 0;
			en = 0;}
		
		sc_start(3, SC_NS);
		
		cout << "un = " << un << "\ten = " << en <<  "\tyn" << yn << "\n";
		
		fout_yn << std::setprecision (5) << yn << "\n";
	
	
	}
	/********** End Processing Loop  ************/
	sc_close_vcd_trace_file(file);
	return 0;
};

