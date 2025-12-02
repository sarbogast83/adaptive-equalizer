/***********************
 *  driver.h
 * 
 * pass signals out of module
 * 
 ****************************/

 #include <systemc.h>

 SC_MODULE(driver)
 {
    sc_in<double> in_data;
    sc_out<double> out_data;

    void do_drive();

    SC_CTOR(driver)
    {
        SC_METHOD(do_drive);
        sensitive << in_data;
    }

 };