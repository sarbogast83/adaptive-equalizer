// drive signals out of module

#include "driver.h"

void driver::do_drive()
{
    out_data.write(in_data.read());
};