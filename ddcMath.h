#ifndef __ddcMath__
#define __ddcMath__

#include <math.h>

double ddMath_abs(double n);
long ddMath_factorial(long n);
double ddMath_sqrt(double n);
double ddMath_sin(double n);
double ddMath_map(double _v, double _l1, double _h1, double _l2, double _h2);
float ddMath_mapf(float _v, float _l1, float _h1, float _l2, float _h2);

/*
double ddsin(double n)
{
	return n - ((n
}
*/




double ddMath_map(double _v, double _l1, double _h1, double _l2, double _h2)
{
	return (_v-_l1) * ((_h2-_l2)/(_h1-_l1)) + _l2;
}
float ddMath_mapf(float _v, float _l1, float _h1, float _l2, float _h2)
{
	return (_v-_l1) * ((_h2-_l2)/(_h1-_l1)) + _l2;
}

double ddMath_sqrt(double n)
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


long ddMath_factorial(long n)
{
	if (n == 0 || n == 1)
		return 1;
	else
		return n * ddMath_factorial(n-1);
}

double ddMath_abs(double _n)
{
	return (_n < 0) ? _n * -1 : _n;
}


#endif
