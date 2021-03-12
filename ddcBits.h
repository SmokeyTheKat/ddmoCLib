#ifndef __ddclib_ddcBits_h__
#define __ddclib_ddcBits_h__

typedef unsigned char byte;

#define bit_get(x, p) ((x >> p) & 1)
#define bit_set(x, p) (x | (1 << p))
#define bit_unset(x, p) (x & (1 << p))
#define bit_tog(x, p) (x ^ (1 << p))
#define bit_setv(x, v, p) ((v == 1) ? bit_set(x, p) : bit_unset(x, p))

#define TB_to_B(x) (x*1000000000000)
#define B_to_TB(x) (x/1000000000000)
#define GB_to_B(x) (x*1000000000)
#define B_to_GB(x) (x/1000000000)
#define MB_to_B(x) (x*1000000)
#define B_to_MB(x) (x/1000000)
#define KB_to_B(x) (x*1000)
#define B_to_KB(x) (x/1000)

#endif
