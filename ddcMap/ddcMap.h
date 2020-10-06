#ifndef __ddcMap__
#define __ddcMap__

float ddMap(float _v, float _l1, float _h1, float _l2, float _h2);



float ddMap(float _v, float _l1, float _h1, float _l2, float _h2)
{
	return (_v-_l1) * ((_h2-_l2)/(_h1-_l1)) + _l2;
	//return (100) * (1000/100);
}


#endif
