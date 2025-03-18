/* fnp(easy) ***/

#include <stdio.h>

#include "types.h"

void nests1(int i) {

  s32 nest2_internal_i;

  s32 inter_net(s32 arg_y) {
     return arg_y * 2;
  }

  s32 (*fnc_p0)(s32) = inter_net;

  printf("nests1: i = %d\n", i);

  nest2_internal_i = fnc_p0(i); /* 6, h. */
  printf("nests2(internal fp(): %d\n", nest2_internal_i);

}

int main()
{

  nests1(3);

  return 0;

}

/* // eoc ** ** ** // */
