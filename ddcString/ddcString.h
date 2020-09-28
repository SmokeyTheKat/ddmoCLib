#ifndef __ddcString__
#define __ddcString__
#include <stdio.h>
#include <stdlib.h>

#include "ddcDef.h"

typedef struct ddString ddString;

ddString make_ddString(const char* _c);
ddString dsmul(const char* _c, ddsize _n);
void raze_ddString(ddString* _d);

void dsres(ddString* _d, ddsize _nl);
void dscpy(ddString* _d, const ddString* _s);
void dsadd(ddString* _d, ddString* _s);
bool dscmp(ddString* _d, ddString* _s);
void dsmulds(ddString* _d, ddsize _n);



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
		dsres(_d, _s->length + __byinc);
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

ddString dsmul(const char* _c, ddsize _n)
{
	ddsize _len;
	chlen(_c, &_len);
	char* _t = make(char, (_len*_n) + __byinc);
	for (ddsize i = 0; i < _n*_len; i += _len)
		for (ddsize j = 0; j < _len; j++)
			_t[i+j] = _c[j];
	ddString* out = make(ddString, 1);
	out->capacity = (_len*_n) + __byinc;
	out->length = _len*_n;
	out->cstr = _t;
	return *out;
}

ddString make_ddString(const char* _c)
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
void raze_ddString(ddString* ds)
{
	raze(ds->cstr);
}


#endif
