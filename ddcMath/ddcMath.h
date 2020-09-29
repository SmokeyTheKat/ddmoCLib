#ifndef __ddcMath__
#define __ddcMath__

#include <ddcDef.h>



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

int ddabs(int _n)
{
	return (_n < 0) ? _n * -1 : _n;
}


#endif
