/**************************************
 * 
 * AE_top.h
 * 
 * adaptive equalizer top level design
 * 12 tap adaptive equalizer using LSM 
 * 
 * requires:
 *      add.h
 *      mult.h
 *      dff.h
 *      driver.h
 *      sub.h
 *      AE_FIR.h
 *      CUcell.h
 *      CUunit.h
 *      
 ************************************/

 #ifndef AE_TOP_H
 #define AE_TOP_H

 #include "systemc.h"
 #include "delayBlock.h"
 #include "AE_FIR_DF.h"
 #include "sub16.h"
 #include "CUunit.h"
 #include "scdl.h"



 SC_MODULE(AE_top)
 {
    sc_in<bool> clock, reset;
    sc_in<sc_int<16>> dn, un;
    //sc_in<sc_uint<5>> mu_N, M;  hardcoded
    sc_in<sc_int<32>> grnd;

    sc_out<sc_int<16>> dhatOut, enOut;
    sc_out<sc_int<16>> wn0, wn1, wn2, wn3, wn4, wn5, wn6, wn7, wn8, wn9, wn10, wn11;
  
    sc_signal<sc_int<16>> dnp5;
    sc_signal<sc_int<32>> dhat32;
    sc_signal<sc_int<16>> u0, u1, u2, u3, u4, u5, u6, u7, u8, u9,u10, u11;
    sc_signal<sc_uint<5>> M;

    //data memebers
    delayBlock *delayline;
    AE_FIR_DF *AEfirBlock;
    sub16 *errorBlock;
    CUunit *updateBlock;
    scdl *M_shift;
 

    SC_CTOR(AE_top)
    {

        //instance 
        delayline = new delayBlock("delayline");
        AEfirBlock = new AE_FIR_DF("AEfirBlock");
        errorBlock = new sub16("errorBlock");
        updateBlock = new CUunit("updateBlock");
        M_shift = new scdl("M_shift");
           

        M = 14;

        //binding
        delayline -> clock(clock);
        delayline -> reset(reset);
        delayline -> rk(dn);
        delayline -> rkp5(dnp5);

        AEfirBlock -> clock(clock);
        AEfirBlock -> reset(reset);
        AEfirBlock -> xn(un);
        AEfirBlock -> grnd(grnd);
        AEfirBlock -> b0(wn0);
        AEfirBlock -> b1(wn1);
        AEfirBlock -> b2(wn2);
        AEfirBlock -> b3(wn3);
        AEfirBlock -> b4(wn4);
        AEfirBlock -> b5(wn5);
        AEfirBlock -> b6(wn6);
        AEfirBlock -> b7(wn7);
        AEfirBlock -> b8(wn8);
        AEfirBlock -> b9(wn9);
        AEfirBlock -> b10(wn10);
        AEfirBlock -> b11(wn11);
        AEfirBlock -> yn(dhat32);
        AEfirBlock -> u0(u0);
        AEfirBlock -> u1(u1);
        AEfirBlock -> u2(u2);
        AEfirBlock -> u3(u3);
        AEfirBlock -> u4(u4);
        AEfirBlock -> u5(u5);
        AEfirBlock -> u6(u6);
        AEfirBlock -> u7(u7);
        AEfirBlock -> u8(u8);
        AEfirBlock -> u9(u9);
        AEfirBlock -> u10(u10);
        AEfirBlock -> u11(u11);

        M_shift -> in(dhat32);
        M_shift -> out(dhatOut);
        M_shift -> lsb(M);

        errorBlock -> minu(dnp5);
        errorBlock -> subt(dhatOut);
        errorBlock -> diff(enOut);
 
        updateBlock -> clock(clock);
        updateBlock -> reset(reset);
        //updateBlock -> mu(mu); hardcoded 
        updateBlock -> en(enOut);
        updateBlock -> u0(u0);
        updateBlock -> u1(u1);
        updateBlock -> u2(u2);
        updateBlock -> u3(u3);
        updateBlock -> u4(u4);
        updateBlock -> u5(u5);
        updateBlock -> u6(u6);
        updateBlock -> u7(u7);
        updateBlock -> u8(u8);
        updateBlock -> u9(u9);
        updateBlock -> u10(u10);
        updateBlock -> u11(u11);
        updateBlock -> w0(wn0);
        updateBlock -> w1(wn1);
        updateBlock -> w2(wn2);
        updateBlock -> w3(wn3);
        updateBlock -> w4(wn4);
        updateBlock -> w5(wn5);
        updateBlock -> w6(wn6);
        updateBlock -> w7(wn7);
        updateBlock -> w8(wn8);
        updateBlock -> w9(wn9);
        updateBlock -> w10(wn10);
        updateBlock -> w11(wn11);
        // end binding 
  
    }
 };
 #endif 