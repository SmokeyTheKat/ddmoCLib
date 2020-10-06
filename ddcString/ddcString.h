#ifndef __ddcString__
#define __ddcString__
#include <stdio.h>
#include <stdlib.h>

#include "ddcDef.h"

typedef struct ddString ddString;

ddString make_ddString(const char* _c);
ddString remake_ddString(ddString* _ds, const char* _c);
ddString intTds(int _v);
ddString floatTds(float _f);
ddString dsmul(const char* _c, ddsize _n);
void raze_ddString(ddString* _d);


void dsres(ddString* _d, ddsize _nl);
void dscpy(ddString* _d, const ddString* _s);
void dsadd(ddString* _d, ddString* _s);
bool dscmp(ddString* _d, ddString* _s);
void dsmulds(ddString* _d, ddsize _n);
void dsPushChBack(ddString* _d, const char* _ch);
void dsPushCBack(ddString* _d, const char _c);
void dsPushChFront(ddString* _d, const char* _ch);
void dsPushCFront(ddString* _d, const char _c);

static int __floatTdsCount(int number, int count);




void chlen(const char* _c, ddsize* _l);
void chcpy(char* _d, const char* _s, ddsize _len);
void chcpyos(char* _d, const char* _s, ddsize _do, ddsize _so, ddsize _l);
bool chcmp(const char* _d, const char* _s);



void _chcpy(char* _d, const char* _s, ddsize _len);
void _chcpyos(char* _d, const char* _s, ddsize _do, ddsize _so, ddsize _l);
bool _chcmp(const char* _d, const char* _s);


struct ddString
{
	char* cstr;
	ddsize length;
	ddsize capacity;
	Ostatus status;
};



void chlen(const char* _c, ddsize* _l)
{
	for (*_l = 0; _c[*_l] != '\0'; (*_l)++);
}
void chcpy(char* _d, const char* _s, ddsize _len)
{
	for (ddsize i = 0; i < _len; i++)
	{
		*_d = *_s;
		_d++;
		_s++;
	}
}
void chcpyos(char* _d, const char* _s, ddsize _do, ddsize _so, ddsize _l)
{
	_d += _do;
	_s += _so;
	for (ddsize i = 0; i < _l; i++)
	{
		*_d = *_s;
		_d++;
		_s++;
	}
}
bool chcmp(const char* _d, const char* _s)
{
	ddsize _dl;
	chlen(_d, &_dl);
	ddsize _sl;
	chlen(_s, &_sl);
	if (_sl != _dl)  return false;
	for (ddsize i = 0; i < _dl; i++)
	{
		if (_d[i] != _s[i])  return false;
	}
	return true;
}





void dscpy(ddString* _d, const ddString* _s)
{
	if (_d->capacity < _s->length)
		dsres(_d, _s->length + __BYINC);
	chcpy(_d->cstr, _s->cstr, _s->length);
}
void dsres(ddString* _d, ddsize _nl)
{
	char* _t = make(char, _nl);
	chcpy(_t, _d->cstr, _d->length);

	raze_ddString(_d);

	_d->capacity = _nl;
	_d->cstr = _t;
}

void dsadd(ddString* _d, ddString* _s)
{
	char* _n = make(char, _d->length + _s->length);
	chcpyos(_n, _d->cstr, 0, 0, _d->length);
	chcpyos(_n, _s->cstr, _d->length, 0, _s->length);

	raze_ddString(_d);

	_d->cstr = _n;
	_d->length += _s->length;
}

bool dscmp(ddString* _d, ddString* _s)
{
	if (_d->length != _s->length)
		return false;
	for (ddsize i = 0; i < _d->length; i++)
		if (_d->cstr[i] != _s->cstr[i])
			return false;
	return true;
}

void dsPushChBack(ddString* _d, const char* _ch)
{
	ddsize _clen;
	chlen(_ch, &_clen);
	if (_d->capacity < _d->length + _clen)
		dsres(_d, _d->length + _clen + __BYINC);
	chcpyos(_d->cstr, _ch, _d->length, 0, _clen);
	_d->length += _clen;
}
void dsPushCBack(ddString* _d, const char _c)
{
	if (_d->capacity < _d->length + 1)
		dsres(_d, _d->length + 1 + __BYINC);
	_d->cstr[_d->length] = _c;
	_d->length += 1;
}


void dsPushChFront(ddString* _d, const char* _ch)
{
	ddsize _clen;
	chlen(_ch, &_clen);
	if (_d->capacity < _d->length + _clen)
		dsres(_d, _d->length + _clen + __BYINC);
	char* _t = make(char, _d->length + _clen);
	chcpy(_t, _ch, _clen);
	chcpyos(_t, _d->cstr, _clen, 0, _d->length);
	raze_ddString(_d);
	_d->length += _clen;
	_d->cstr = _t;
}
void dsPushCFront(ddString* _d, const char _c)
{
	if (_d->capacity < _d->length + 1)
		dsres(_d, _d->length + 1 + __BYINC);
	char* _t = make(char, _d->length + 1);
	_t[0] = _c;
	chcpyos(_t, _d->cstr, 1, 0, _d->length);
	raze_ddString(_d);
	_d->length += 1;
	_d->cstr = _t;
}

ddString intTds(int _v)
{
	if (_v == 0) return make_ddString("0");
	char sign;
	if (_v < 0) 
	{
		sign = '-';
		_v *= -1;
	}
	ddString _o = make_ddString("");
	while (_v)
	{       
		ddsize x = _v % 10;
		_v /= 10; 
		dsPushCFront(&_o, (char)('0' + x));
	}
	if (_o.length == 0) remake_ddString(&_o, "0");
	if (sign == '-') dsPushCFront(&_o, sign);
	return _o;
}


static int __floatTdsCount(int n, int c)
{
    int _o = 1;
    while(c-- > 0)
        _o *= n;

    return _o;
}

ddString floatTds(float _f)
{
	long long int l1;
	long long int l2;
	long long int i;
	long long int n1;
	long long int pos;
	long long int sign;
	float n2;

	sign = -1;
	if (_f < 0)
	{
		sign = '-';
		_f *= -1;
	}

	n2 = _f;
	n1 = _f;
	l1 = 0;
	l2 = 0;

	while( (n2 - (float)n1) != 0.0 && !((n2 - (float)n1) < 0.0) )
	{
		n2 = _f * (__floatTdsCount(10.0, l2 + 1));
		n1 = n2;
		l2++;
	}

	for (l1 = (_f > 1) ? 0 : 1; _f > 1; l1++)
		_f /= 10;

	pos = l1;
	l1 = l1 + 1 + l2;
	n1 = n2;
	if (sign == '-')
	{
		l1++;
		pos++;
	}
	
	ddString _o = dsmul("0", l1);

	for (i = l1; i >= 0 ; i--)
	{
		if (i == (l1))
			_o.cstr[i] = '\0';
		else if(i == (pos))
			_o.cstr[i] = '.';
		else if(sign == '-' && i == 0)
			_o.cstr[i] = '-';
		else
		{
			_o.cstr[i] = (n1 % 10) + '0';
			n1 /= 10;
		}
	}
	if (_o.cstr[0] == '0' && _o.cstr[_o.length-1] == '.')
	{
		dsPushCFront(&_o, '1');
	}
	return _o;
}


ddString dsmul(const char* _c, ddsize _n)
{
	ddsize _len;
	chlen(_c, &_len);
	char* _t = make(char, (_len*_n) + __BYINC);
	for (ddsize i = 0; i < _n*_len; i += _len)
		for (ddsize j = 0; j < _len; j++)
			_t[i+j] = _c[j];
	ddString* out = make(ddString, 1);
	out->capacity = (_len*_n) + __BYINC;
	out->length = _len*_n;
	out->cstr = _t;
	return *out;
}

ddString remake_ddString(ddString* _ds, const char* _c)
{
	raze_ddString(_ds);
	*_ds = make_ddString(_c);
	_ds->status = active;
}
ddString make_ddString(const char* _c)
{
	ddString _o;
	ddsize _len = 0;
	chlen(_c, &_len);

	_o.length = _len;
	_o.capacity = _len + __BYINC;

	_o.status = active;

	_o.cstr = make(char, _o.capacity);
	chcpy(_o.cstr, _c, _o.length);

	return _o;
}
void raze_ddString(ddString* ds)
{
	raze(ds->cstr);
	ds->status = deleted;
}


#endif
