/**************************************
 * S Arbogast
 * 
 * CUcell.h
 * 
 * computationtion cell for adaptive filter coef update 
 * w(n+1) = w(n) + mu * u(n) * e(n)
 * 
 **************************************/

 #ifndef CU_CELL_H
 #define CU_CELL_H

 #include <systemc.h>
 #include "add.h"
 #include "mult.h"
 #include "dff.h"
 #include "driver.h"

 SC_MODULE(CUcell)
 {
    sc_in<bool> clock, reset;
    sc_in<double> un, en, mu;
    sc_out<double> wnp1;

    sc_signal<double> mk0, mk1, ak, akp1;

    //data members
    dff *U_dff;
    add *U_add;
    mult *U0_mult, *U1_mult;
    driver *U_driver;

    //constructor
    SC_CTOR(CUcell)
    {
        U_dff = new dff("U_dff");
        U_add = new add("U_add");
        U0_mult = new mult("U0_mult");
        U1_mult = new mult("U1_mult");
        U_driver = new driver("U_driver");

        //binding 
        U0_mult -> in1(mu);
        U0_mult -> in2(en);
        U0_mult -> out(mk0);

        U1_mult -> in1(mk0);
        U1_mult -> in2(un);
        U1_mult -> out(mk1);

        U_add -> in1(mk1);
        U_add -> in2(akp1);
        U_add -> out(ak);

        U_dff -> clock(clock);
        U_dff -> reset(reset);
        U_dff -> in_data(ak);
        U_dff -> out_q(akp1);

        U_driver -> in_data(akp1);
        U_driver -> out_data(wnp1);
    }

 };
 #endif