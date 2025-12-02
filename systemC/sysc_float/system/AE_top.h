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
 #include "sub.h"
 #include "CUunit.h"

 SC_MODULE(AE_top)
 {
    sc_in<bool> clock, reset;
    sc_in<double> dn, un, mu, grnd;

    sc_out<double> dhatOut, enOut ;
    sc_out<double> wn0, wn1, wn2, wn3, wn4, wn5, wn6, wn7, wn8, wn9, wn10, wn11;

    sc_signal<double> dhat, en, dnp5;
    sc_signal<double> u0, u1, u2, u3, u4, u5, u6, u7, u8, u9,u10, u11;
    sc_signal<double> w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11;

    //data memebers
    delayBlock *delayline;
    AE_FIR_DF *AEfirBlock;
    sub *errorBlock;
    CUunit *updateBlock;
    driver *dhatDriver, *enDriver, *W0_Driver, *W1_Driver, *W2_Driver, *W3_Driver, 
                *W4_Driver, *W5_Driver, *W6_Driver, *W7_Driver, 
                *W8_Driver, *W9_Driver, *W10_Driver, *W11_Driver;

    SC_CTOR(AE_top)
    {

        //instance 
        delayline = new delayBlock("delayline");
        AEfirBlock = new AE_FIR_DF("AEfirBlock");
        errorBlock = new sub("errorBlock");
        updateBlock = new CUunit("updateBlock");
        dhatDriver = new driver("dhatDriver");
        enDriver = new driver("enDriver");
        W0_Driver = new driver("W0_Driver");
        W1_Driver = new driver("W1_Driver");
        W2_Driver = new driver("W2_Driver");
        W3_Driver = new driver("W3_Driver");
        W4_Driver = new driver("W4_Driver");
        W5_Driver = new driver("W5_Driver");
        W6_Driver = new driver("W6_Driver");
        W7_Driver = new driver("W7_Driver");
        W8_Driver = new driver("W8_Driver");
        W9_Driver = new driver("W9_Driver");
        W10_Driver = new driver("W10_Driver");
        W11_Driver = new driver("W11_Driver");

        //binding
        delayline -> clock(clock);
        delayline -> reset(reset);
        delayline -> rk(dn);
        delayline -> rkp5(dnp5);

        AEfirBlock -> clock(clock);
        AEfirBlock -> reset(reset);
        AEfirBlock -> xn(un);
        AEfirBlock -> grnd(grnd);
        AEfirBlock -> b0(w0);
        AEfirBlock -> b1(w1);
        AEfirBlock -> b2(w2);
        AEfirBlock -> b3(w3);
        AEfirBlock -> b4(w4);
        AEfirBlock -> b5(w5);
        AEfirBlock -> b6(w6);
        AEfirBlock -> b7(w7);
        AEfirBlock -> b8(w8);
        AEfirBlock -> b9(w9);
        AEfirBlock -> b10(w10);
        AEfirBlock -> b11(w11);
        AEfirBlock -> yn(dhat);
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

        errorBlock -> minu(dnp5);
        errorBlock -> subt(dhat);
        errorBlock -> diff(en);
 
        updateBlock -> clock(clock);
        updateBlock -> reset(reset);
        updateBlock -> mu(mu);
        updateBlock -> en(en);
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
        updateBlock -> w0(w0);
        updateBlock -> w1(w1);
        updateBlock -> w2(w2);
        updateBlock -> w3(w3);
        updateBlock -> w4(w4);
        updateBlock -> w5(w5);
        updateBlock -> w6(w6);
        updateBlock -> w7(w7);
        updateBlock -> w8(w8);
        updateBlock -> w9(w9);
        updateBlock -> w10(w10);
        updateBlock -> w11(w11);
        // end binding 

        //passing out internal signals for validation 
        dhatDriver -> in_data(dhat);
        dhatDriver -> out_data(dhatOut);

        enDriver -> in_data(en);
        enDriver -> out_data(enOut);

        W0_Driver -> in_data(w0);
        W0_Driver -> out_data(wn0);
        W1_Driver -> in_data(w1);
        W1_Driver -> out_data(wn1);
        W2_Driver -> in_data(w2);
        W2_Driver -> out_data(wn2);
        W3_Driver -> in_data(w3);
        W3_Driver -> out_data(wn3);
        W4_Driver -> in_data(w4);
        W4_Driver -> out_data(wn4);
        W5_Driver -> in_data(w5);
        W5_Driver -> out_data(wn5);
        W6_Driver -> in_data(w6);
        W6_Driver -> out_data(wn6);
        W7_Driver -> in_data(w7);
        W7_Driver -> out_data(wn7);
        W8_Driver -> in_data(w8);
        W8_Driver -> out_data(wn8);
        W9_Driver -> in_data(w9);
        W9_Driver -> out_data(wn9);
        W10_Driver -> in_data(w10);
        W10_Driver -> out_data(wn10);
        W11_Driver -> in_data(w11);
        W11_Driver -> out_data(wn11);




    }



 };
 #endif 