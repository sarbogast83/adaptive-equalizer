/*************************************************
 *  test_delayBlock.cc
 *  
 * 
 **************************************************/

#include <fstream>
#include <systemc.h>
#include <iomanip>
#include "delayBlock.h"

int sc_main (int argc, char *argv[]) {

  FILE *x_fp;

  sc_signal<bool> clock, reset;
  sc_signal<double> xn, yn;

  int x_Len, y_Len, i, j;
  double tmp_x;
  char s[300];

  //open data file
  x_fp = fopen("xn.txt","r");

  //write to 
  ofstream fout("yn.txt");

  //read in data
  if (fgets(s,100,x_fp)!=NULL)
    sscanf(s,"%d",&x_Len);
  printf("x_Len = %d\n",x_Len);

  y_Len = x_Len + 6; // data plus delays

  double x[x_Len];

  //bind delay block 
  delayBlock U_DB("U_DB");

  U_DB.clock(clock);
  U_DB.reset(reset);
  U_DB.rk(xn);
  U_DB.rkp6(yn);

  // system
  sc_start(SC_ZERO_TIME);

  //read in data
  i = 0;
  tmp_x = 0;
  while(fgets(s,100,x_fp)!=NULL)
  {
    sscanf(s,"%lf",&tmp_x);
    x[i] = tmp_x;
    i++;
  }

  //reset system
  clock = 0;
  sc_start(5,SC_NS);
  clock = 1;
  sc_start(2,SC_NS);
  reset = 1;
  sc_start(3,SC_NS);
  clock = 0;
  sc_start(5,SC_NS);
  clock = 1;
  sc_start(5,SC_NS);
  clock = 0;
  sc_start(5,SC_NS);
  clock = 1;
  sc_start(5, SC_NS);
  clock = 0;
  reset = 0;

  // run system
  for (j = 0; j<y_Len; j++)
  {
    clock = 0;
    sc_start(5, SC_NS);
    clock = 1;
    sc_start(2, SC_NS);

    if(j<x_Len)
      xn = x[j];
    else
      xn = 0;

    sc_start(3,SC_NS);
    cout << "xn: "<< xn << "\tyn: " << yn << "\n";
    fout << std::setprecision (30) << yn << "\n";

  }
  return 0;
};