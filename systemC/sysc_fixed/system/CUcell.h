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
 #include "add16.h"
 #include "mult16.h"
 #include "dff_gen_int.h"
 #include "driver.h"
 #include "scdl.h"

 SC_MODULE(CUcell)
 {
    sc_in<bool> clock, reset;
    sc_in<sc_int<16>> un, en;
    //sc_in<sc_uint<5>> mu_N;
    sc_out<sc_int<16>> wnp1;

    sc_signal<sc_int<16>> ak, akp1, mk16;
    sc_signal<sc_int<32>> mk32;
    sc_signal<sc_uint<5>> mu_N;

    //data members
    dff_gen_int<16> *U_dff;
    add16 *U_add;
    mult16 *U0_mult;
    driver *U_driver;
    scdl *U_shift;

    //constructor
    SC_CTOR(CUcell)
    {
        mu_N = 20;
        U_dff = new dff_gen_int<16>("U_dff");
        U_add = new add16("U_add");
        U0_mult = new mult16("U0_mult");
        U_driver = new driver("U_driver");
        U_shift = new scdl("U_shift");

        //binding 
        U0_mult -> in1(un);
        U0_mult -> in2(en);
        U0_mult -> out(mk32);

        U_shift -> in(mk32);
        U_shift -> out(mk16);
        U_shift -> lsb(mu_N);

        U_add -> in1(mk16);
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