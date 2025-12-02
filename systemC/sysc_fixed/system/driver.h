/***********************
 *  driver.h
 * 
 * pass signals out of module
 * 
 ****************************/
#ifndef DRIVER_H
#define DRIVER_H

 #include <systemc.h>

 SC_MODULE(driver)
 {
    sc_in<sc_int<16>> in_data;
    sc_out<sc_int<16>> out_data;

    void do_drive();

    SC_CTOR(driver)
    {
        SC_METHOD(do_drive);
        sensitive << in_data;
    }

 };
 #endif