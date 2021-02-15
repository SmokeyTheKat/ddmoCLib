#ifndef __ddclib_ddcBits_h__
#define __ddclib_ddcBits_h__

typedef unsigned char byte;

#define bit_get(x, p) ((x >> p) & 1)
#define bit_set(x, p) (x | (1 << p))
#define bit_unset(x, p) (x & (1 << p))
#define bit_tog(x, p) (x ^ (1 << p))
#define bit_setv(x, v, p) ((v == 1) ? bit_set(x, p) : bit_unset(x, p))

#endif
