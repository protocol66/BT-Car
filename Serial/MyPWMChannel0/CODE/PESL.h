/* ================================================================================================================================= **
** ================================================================================================================================= **
** CONFIGURATION FILE FOR PESL LIBRARY                                                                                               **
** ================================================================================================================================= **
** ================================================================================================================================= */

#define  MC9S12A128_112   1
#define  MC9S12A128_80    2
#define  MC9S12A256_112   3
#define  MC9S12A256_80    4
#define  MC9S12A64_112    5
#define  MC9S12A64_80     6
#define  MC9S12C32_48     7
#define  MC9S12C32_52     8
#define  MC9S12C32_80     9
#define  MC9S12D64_112    10
#define  MC9S12D64_80     11
#define  MC9S12DB128_112  12
#define  MC9S12DG128_112  13
#define  MC9S12DG128_80   14
#define  MC9S12DG256_112  15
#define  MC9S12DJ128_112  16
#define  MC9S12DJ128_80   17
#define  MC9S12DJ256_112  18
#define  MC9S12DJ256_80   19
#define  MC9S12DJ64_112   20
#define  MC9S12DJ64_80    21
#define  MC9S12DP256_112  22
#define  MC9S12DT128_112  23
#define  MC9S12DT256_112  24
#define  MC9S12A32_80     25
#define  MC9S12D32_80     26
#define  MC9S12DP512_112  27
#define  MC9S12A512_112   28
#define  MC9S12E128_112   29
#define  MC9S12E128_80    30
#define  MC9S12E64_112    31


/* Selected target MCU */

#define CPUtype MC9S12DP256_112


/* PESL library */

#pragma MESSAGE DISABLE C4000 /* WARNING C4000: Condition is always TRUE */
#pragma MESSAGE DISABLE C4001 /* WARNING C4001: Condition is always FALSE */

#include "PESLlib.h"


