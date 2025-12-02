/**********************************
 *  sub16.h
 *  S Arbogast
 * 
 *  subtractor unit
 *  Note: order matters 
 *  Minuend: The number from which another number is subtracted.
 *  Subtrahend: The number that is being subtracted from the minuend.
 *  Difference: The result of the subtraction.
 *
 *******************************/

#ifndef SUB16_H
#define SUB16_H

#include <systemc.h>

SC_MODULE(sub16)
{
  sc_out<sc_int<16>> diff;
  sc_in<sc_int<16>> minu, subt;

  void do_sub();

  SC_CTOR(sub16)
  {
    SC_METHOD (do_sub);
		sensitive << minu << subt;
  }
};
#endif