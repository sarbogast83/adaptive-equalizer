/**************************************
 * 
 * test_AEtop.cc
 * 
 * 
 ************************************/

#include <fstream>
#include <systemc.h>
#include <iomanip>

#include "AE_top.h"

int sc_main (int argc , char *argv[]) 
{
  
	FILE *u_fp, *d_fp; // file pointers for data signal and coeffs.
	
	sc_signal<bool> reset, clock;
	sc_signal<double> dn, un, mu, grnd; //in
    sc_signal<double> dhatOut, enOut; //out
	sc_signal<double> wn0, wn1, wn2, wn3, wn4, wn5, wn6, wn7, wn8, wn9, wn10, wn11;
	
	int u_Len, d_Len, dhat_Len, i, j;
	double tmp_u, tmp_d;
	char s[300];
	
	// Opening the data and coefficient files
	u_fp = fopen("un.txt","r");
	d_fp = fopen("dn.txt","r");
	
	
	// This format for writing to a file works for outputing
	// sc_signals. Use fout instead of fprintf
	ofstream fout_w("w.txt");
    ofstream fout_en("en.txt");
    ofstream fout_dhat("dhatn.txt");

	
	// Reading in the size of the data samples and the coeffs
	// to determine the sizes of the arrays
	if (fgets(s,100,u_fp)!=NULL)
		sscanf(s,"%d", &u_Len);
	printf("u_Len = %d\n", u_Len);

	if (fgets(s,100,d_fp)!=NULL)
		sscanf(s,"%d", &d_Len);
	printf("d_Len = %d\n", d_Len);

	
	dhat_Len = d_Len; // Defining the length of the output
	
	
	// Declaring the sizes of the data arrays.
	double u[u_Len];
	double d[d_Len];
	
	/************** Binding *****************/
	// Binding by name. Order does not matter
	AE_top U_AEtop("U_AEtop");

    //in
	U_AEtop.clock(clock);
	U_AEtop.reset(reset);
	U_AEtop.dn(dn);
	U_AEtop.un(un);
	U_AEtop.mu(mu);
    U_AEtop.grnd(grnd);
    //out
    U_AEtop.dhatOut(dhatOut);
    U_AEtop.enOut(enOut);
	U_AEtop.wn0(wn0);
    U_AEtop.wn1(wn1);
    U_AEtop.wn2(wn2);
    U_AEtop.wn3(wn3);
    U_AEtop.wn4(wn4);
    U_AEtop.wn5(wn5);
    U_AEtop.wn6(wn6);
    U_AEtop.wn7(wn7);
    U_AEtop.wn8(wn8);
    U_AEtop.wn9(wn9);
    U_AEtop.wn10(wn10);
    U_AEtop.wn11(wn11);



	/**************  End Binding **************/
	
	sc_start(SC_ZERO_TIME);
	
	/*************   Reading files    *********/
    // Reading in the training sequence
  	i = 0;
  	tmp_d = 0;
	while (fgets(s,300,d_fp)!=NULL)
	{
		sscanf(s,"%lf", &tmp_d);
		d[i] = tmp_d;
		i++;
	}

	// Reading in the corrupted sequence
	mu = 0.03;
    grnd = 0.0;
	i = 0;
	tmp_u = 0;
	while (fgets(s,100,u_fp)!=NULL)
	{
		sscanf(s,"%lf", &tmp_u);
		u[i] = tmp_u;
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
	// sc_trace_file* file = sc_create_vcd_trace_file("trace");
	// sc_trace(file, clock, "clock");
	// sc_trace(file, reset, "reset");
	
	/********* Begin Processing Loop *************/
	for (j = 0; j<dhat_Len + 1 ; j++)
	{	
		reset = 0;
		
		clock = 0;
		sc_start(5, SC_NS);
		clock = 1;
		sc_start(2, SC_NS);
		
		if(j<d_Len){
			dn = d[j];
            un = u[j];
        }
		else{
            dn = 0;
            un = 0;
        }
		
		sc_start(3, SC_NS);
		if (j<50)
		    cout << "dn: " << dn << "\tun: " << un << "\tdhat:" << dhatOut << "\ten: " << enOut <<  "\n";
         		
		fout_dhat << std::setprecision (30) << dhatOut << "\n";
        fout_en << std::setprecision(30) << enOut << "\n";
        if(j == 1012) // 
            fout_w << std::setprecision (30) << wn0 << " " << wn1 << " " << wn2 << " " << wn3 << " "
                                         << wn4 << " " << wn5 << " " << wn6 << " " << wn7 << " "
                                         << wn8 << " " << wn9 << " " << wn10 << " " << wn11 << "\n";
	}
    
	return 0;
};