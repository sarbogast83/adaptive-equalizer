/*************************************
 *  delayBlock.cc
 *  S Arbogast
 *  14 Nov 25
 * 
 *  requires: 
 *      dff
 * 
 *  delay unit produces output at time T(6)    
 * 
 *************************************/

 #include "systemc.h"
 #include "dff.h"

 SC_MODULE (delayBlock)
 {
    sc_in<bool> clock, reset;
    sc_in<double> rk;
    sc_out<double> rkp6;

    sc_signal<double> rkp1, rkp2, rkp3, rkp4, rkp5;

    // data memebers
    dff *U0_dff, *U1_dff, *U2_dff, *U3_dff, *U4_dff, *U5_dff;

    //constructor
    SC_CTOR (delayBlock)
    {
        U0_dff = new dff("U0_dff");
        U1_dff = new dff("U1_dff");
        U2_dff = new dff("U2_dff");
        U3_dff = new dff("U3_dff");
        U4_dff = new dff("U4_dff");
        U5_dff = new dff("U5_dff");

        U0_dff -> clock(clock);
        U0_dff -> reset(reset);
        U0_dff -> in_data(rk);
        U0_dff -> out_q(rkp1);

        U1_dff -> clock(clock);
        U1_dff -> reset(reset);
        U1_dff -> in_data(rkp1);
        U1_dff -> out_q(rkp2);

        U2_dff -> clock(clock);
        U2_dff -> reset(reset);
        U2_dff -> in_data(rkp2);
        U2_dff -> out_q(rkp3);

        U3_dff -> clock(clock);
        U3_dff -> reset(reset);
        U3_dff -> in_data(rkp3);
        U3_dff -> out_q(rkp4);

        U4_dff -> clock(clock);
        U4_dff -> reset(reset);
        U4_dff -> in_data(rkp4);
        U4_dff -> out_q(rkp5);

        U5_dff -> clock(clock);
        U5_dff -> reset(reset);
        U5_dff -> in_data(rkp5);
        U5_dff -> out_q(rkp6);
    }
 };