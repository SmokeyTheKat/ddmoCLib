#ifndef __ddcMath__
#define __ddcMath__

#include <ddcDef.h>
#include <math.h>



float ddsqrt(float n)
{ 
	float _t;
	float _s;

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

float sq2(float n)
{
	float o = 0;
	for (ddsize i = 0; i < 50; i++)
	{
		o += (pow((n-1),i))/(factt(i));
	}
	return o;
}

int ddabs(int _n)
{
	return (_n < 0) ? _n * -1 : _n;
}


#endif
