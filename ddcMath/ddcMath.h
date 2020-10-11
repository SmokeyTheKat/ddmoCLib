#ifndef __ddcMath__
#define __ddcMath__

#include <ddcDef.h>
#include <ddcMap.h>
#include <math.h>

double ddabs(double n);
ddsize ddfact(ddsize n);
double ddsqrt(double n);
double ddsin(double n);

/*
double ddsin(double n)
{
	return n - ((n
}
*/

double ddsqrt(double n)
{ 
	double _t;
	double _s;

	_s = n / 2;

	while(_s != _t)
	{
		_t = _s;
		_s = (n / _t + _t) / 2;
	}
	return _s;
} 


ddsize factt(ddsize n)
{
	if (n == 0 || n == 1)
		return 1;
	else
		return n * factt(n-1);
}

double ddabs(double _n)
{
	return (_n < 0) ? _n * -1 : _n;
}


#endif
