/*********************************************
 * // scdl.h
 * 
 * scale 32 bit to 16 bit with parameterized range location
 * 
 * ****************************************************** */
#ifndef SCDL_H
#define SCDL_H

#include "systemc.h"
#include <iostream>

SC_MODULE (scdl)
{
    sc_out< sc_int<16>> out;
    sc_in< sc_int<32>> in;
    sc_in< sc_uint<5>> lsb;

    void do_scd();

    //constructor
    SC_CTOR(scdl)
    {
        SC_METHOD(do_scd);
        sensitive << in << lsb;
    }
};
#endif

