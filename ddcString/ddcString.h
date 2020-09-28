#ifndef __ddcString__
#define __ddcString__
#include <stdio.h>
#include <stdlib.h>

#include "ddcDef.h"

typedef struct ddString ddString;
ddString nddString(const char* _c);
void dddString(ddString* _d);
void dsres(ddString* _d, ddsize _nl);
void dscpy(ddString* _d, ddString* _s);
void dsadd(ddString* _d, ddString* _s);
bool dscmp(ddString* _d, ddString* _s);
ddString dsmul(const char* _c, ddsize _n);
void dsmulds(ddString* _d, ddsize _n);


void chlen(const char* _c, ddsize* _l);
void chcpy(char* _d, const char* _s, ddsize _len);
void chcpyos(char* _d, const char* _s, ddsize _do, ddsize _so, ddsize _l);
bool chcmp(const char* _d, const char* _s);


struct ddString
{
	char* cstr;
	ddsize length;
	ddsize capacity;
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



void dscpy(ddString* _d, ddString* _s)
{
	if (_d->length < _s->length)
		dsres(_d, _s->length);
	char* __d = _d->cstr;
	char* __s = _s->cstr;
	for (ddsize i = 0; i < _s->length; i++)
	{
		*__d = *__s;
		__d++;
		__s++;
	}
}
void dsres(ddString* _d, ddsize _nl)
{
	char* _t = make(char, _nl);
	chcpy(_t, _d->cstr, _d->length);

	dddString(_d);

	_d->length = _nl;
	_d->cstr = _t;
}

void dsadd(ddString* _d, ddString* _s)
{
	char* _n = make(char, _d->length + _s->length);
	chcpyos(_n, _d->cstr, 0, 0, _d->length);
	chcpyos(_n, _s->cstr, _d->length, 0, _s->length);

	dddString(_d);

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

/*
ddString dsmul(const char* _c, ddsize _n)
{
	ddsize _len;
	chlen(&_c, &_len);
	char* _t = make(char, _len*_n);
	for (ddsize i = 0; i < _n; i++)
		for (ddsize j = 0; j < _len; i++)
			_t[i+j] = _c[j];
	ddString out;
	out->length = _len*_n;
	out->cstr = _t;
	return out;
}
void dsmulds(ddString* _d, ddsize _n);

*/

ddString nddString(const char* _c)
{
	ddString _o;
	ddsize _len = 0;
	chlen(_c, &_len);

	_o.length = _len;
	_o.capacity = _len + __byinc;

	_o.cstr = make(char, _o.capacity);
	chcpy(_o.cstr, _c, _o.length);

	return _o;
}
void dddString(ddString* ds)
{
	raze(ds->cstr);
}


#endif
