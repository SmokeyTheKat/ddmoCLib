#ifndef __ddcNLoops__
#define __ddcNLoops__

#include <math.h>

typedef struct ddNLoop ddNLoop;

struct ddNLoop
{
	unsigned long loops;
	unsigned long totalLoops;
	unsigned long* loopLengths;
	unsigned long* itrs;
};



ddNLoop init_ddNLoop(unsigned long* _ll, unsigned long _loops);
void update_ddNLoop(ddNLoop _dnl, unsigned long _i);
void raze_ddNLoop(ddNLoop _dnl);

unsigned long _getPeak(unsigned long* xx, unsigned long i);
void _getItrs(unsigned long v, unsigned long* xx, unsigned long b, unsigned long y, unsigned long i, unsigned long* o);



ddNLoop init_ddNLoop(unsigned long* _ll, unsigned long _l)
{
	ddNLoop _o;
	_o.loops = _l;
	_o.loopLengths = _ll;
	_o.totalLoops = 1;
	for (unsigned long i = 0; i < _l; i++)
		_o.totalLoops *= _ll[i];
	_o.itrs = malloc(sizeof(unsigned long)*_l);
	for (unsigned long i = 0; i < _l; i++)
		_o.itrs[i] = 0;
	return _o;
}
void raze_ddNLoop(ddNLoop _dnl)
{
	free(_dnl.itrs);
	free(_dnl.loopLengths);
}
void update_ddNLoop(ddNLoop _dnl, unsigned long _i)
{
	_getItrs(_i, _dnl.loopLengths, 0, _i, _dnl.loops, _dnl.itrs);
}









unsigned long _getPeak(unsigned long* xx, unsigned long i)
{
	if (i-1 <= 1)
		return xx[0];
	int _t = 1;
	for (unsigned long j = 1; j < i; j++)
		_t *= xx[j];
	return _t;
}
void _getItrs(unsigned long v, unsigned long* xx, unsigned long b, unsigned long y, unsigned long i, unsigned long* o)
{
	if (i == 1)  b = y;
	else         b = floor(y/(_getPeak(xx, i)));

	o[i-1] = b;
	y = y - (b*(_getPeak(xx, i)));
	i -= 1;
	if (i < 1)  return;
	_getItrs(v, xx, b, y, i, o);
}



#endif
