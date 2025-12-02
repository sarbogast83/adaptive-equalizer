/*************************************
 *  delayBlock.cc
 *  S Arbogast
 *  14 Nov 25
 * 
 *  requires: 
 *      dff_gen_int
 * 
 *  delay unit produces output at time T(6)
 * fixed point 16 bit    
 * 
 *************************************/

 #include "systemc.h"
 #include "dff_gen_int.h"

 SC_MODULE (delayBlock)
 {
    sc_in<bool> clock, reset;
    sc_in<sc_int<16>> rk;
    sc_out<sc_int<16>> rkp5;

    sc_signal<sc_int<16>> rkp1, rkp2, rkp3, rkp4;

    // data memebers
    dff_gen_int<16> *U0_dff, *U1_dff, *U2_dff, *U3_dff, *U4_dff;

    //constructor
    SC_CTOR (delayBlock)
    {
        U0_dff = new dff_gen_int<16>("U0_dff");
        U1_dff = new dff_gen_int<16>("U1_dff");
        U2_dff = new dff_gen_int<16>("U2_dff");
        U3_dff = new dff_gen_int<16>("U3_dff");
        U4_dff = new dff_gen_int<16>("U4_dff");
        

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
    }
 };