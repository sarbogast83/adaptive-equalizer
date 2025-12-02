/**********************************
 *  sub.h
 *  S Arbogast
 * 
 *  subtractor unit
 *  Note: order matters 
 *  Minuend: The number from which another number is subtracted.
 *  Subtrahend: The number that is being subtracted from the minuend.
 *  Difference: The result of the subtraction.
 *
 *******************************/

#ifndef SUB_H
#define SUB_H

#include <systemc.h>

SC_MODULE(sub)
{
  sc_out<double> diff;
  sc_in<double> minu, subt;

  void do_sub();

  SC_CTOR(sub)
  {
    SC_METHOD (do_sub);
		sensitive << minu << subt;
  }
};
#endif