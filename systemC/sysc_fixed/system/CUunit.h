/********************************
 * CUunit -> h
 * 
 * adaptive filter coef update block 
 * combination of 12 CUcells
 * 
 *****************************/

 #ifndef CU_UNIT_H
 #define CU_UNIT_H
 
 #include <systemc.h>
 #include "CUcell.h"

 SC_MODULE(CUunit)
 {
    sc_in<bool> clock, reset;
    sc_in<sc_int<16>> en, u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11;
    //sc_in<sc_int<5>> mu_N;
    sc_out<sc_int<16>> w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11;

    //data members
    CUcell *U0_CUcell, *U1_CUcell, *U2_CUcell, *U3_CUcell,
            *U4_CUcell, *U5_CUcell, *U6_CUcell, *U7_CUcell,
            *U8_CUcell, *U9_CUcell, *U10_CUcell, *U11_CUcell;

    SC_CTOR(CUunit)
    {
        //instance 
        U0_CUcell = new CUcell("U0_CUcell");
        U1_CUcell = new CUcell("U1_CUcell");
        U2_CUcell = new CUcell("U2_CUcell");
        U3_CUcell = new CUcell("U3_CUcell");
        U4_CUcell = new CUcell("U4_CUcell");
        U5_CUcell = new CUcell("U5_CUcell");
        U6_CUcell = new CUcell("U6_CUcell");
        U7_CUcell = new CUcell("U7_CUcell");
        U8_CUcell = new CUcell("U8_CUcell");
        U9_CUcell = new CUcell("U9_CUcell");
        U10_CUcell = new CUcell("U10_CUcell");
        U11_CUcell = new CUcell("U11_CUcell");

        //binding
        U0_CUcell -> clock(clock);
        U0_CUcell -> reset(reset);
        //U0_CUcell -> mu(mu);
        U0_CUcell -> en(en);
        U0_CUcell -> un(u0);
        U0_CUcell -> wnp1(w0);

        U1_CUcell -> clock(clock);
        U1_CUcell -> reset(reset);
        //U1_CUcell -> mu(mu);
        U1_CUcell -> en(en);
        U1_CUcell -> un(u1);
        U1_CUcell -> wnp1(w1);

        U2_CUcell -> clock(clock);
        U2_CUcell -> reset(reset);
        //U2_CUcell -> mu(mu);
        U2_CUcell -> en(en);
        U2_CUcell -> un(u2);
        U2_CUcell -> wnp1(w2);

        U3_CUcell -> clock(clock);
        U3_CUcell -> reset(reset);
        //U3_CUcell -> mu(mu);
        U3_CUcell -> en(en);
        U3_CUcell -> un(u3);
        U3_CUcell -> wnp1(w3);

        U4_CUcell -> clock(clock);
        U4_CUcell -> reset(reset);
        //U4_CUcell -> mu(mu);
        U4_CUcell -> en(en);
        U4_CUcell -> un(u4);
        U4_CUcell -> wnp1(w4);


        U5_CUcell -> clock(clock);
        U5_CUcell -> reset(reset);
        //U5_CUcell -> mu(mu);
        U5_CUcell -> en(en);
        U5_CUcell -> un(u5);
        U5_CUcell -> wnp1(w5);

        U6_CUcell -> clock(clock);
        U6_CUcell -> reset(reset);
        //U6_CUcell -> mu(mu);
        U6_CUcell -> en(en);
        U6_CUcell -> un(u6);
        U6_CUcell -> wnp1(w6);

        U7_CUcell -> clock(clock);
        U7_CUcell -> reset(reset);
        //U7_CUcell -> mu(mu);
        U7_CUcell -> en(en);
        U7_CUcell -> un(u7);
        U7_CUcell -> wnp1(w7);

        U8_CUcell -> clock(clock);
        U8_CUcell -> reset(reset);
        //U8_CUcell -> mu(mu);
        U8_CUcell -> en(en);
        U8_CUcell -> un(u8);
        U8_CUcell -> wnp1(w8);

        U9_CUcell -> clock(clock);
        U9_CUcell -> reset(reset);
        //U9_CUcell -> mu(mu);
        U9_CUcell -> en(en);
        U9_CUcell -> un(u9);
        U9_CUcell -> wnp1(w9);

        U10_CUcell -> clock(clock);
        U10_CUcell -> reset(reset);
        //U10_CUcell -> mu(mu);
        U10_CUcell -> en(en);
        U10_CUcell -> un(u10);
        U10_CUcell -> wnp1(w10);

        U11_CUcell -> clock(clock);
        U11_CUcell -> reset(reset);
        //U11_CUcell -> mu(mu);
        U11_CUcell -> en(en);
        U11_CUcell -> un(u11);
        U11_CUcell -> wnp1(w11);
    }        

};
 #endif 