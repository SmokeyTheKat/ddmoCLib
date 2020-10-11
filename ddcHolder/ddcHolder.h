#include <ddcDef.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include <ddcLine.h>
#include <ddcShapes.h>
#include <stdio.h>

#define hget(h, i, t) (*((t*)__hget(h, i)))
#define hset(h, i, t, v) __hset(h, i, __ddt##t, v)
#define hpush(h, t, v) __hpush(&h, __ddt##t, v)

typedef struct ddHolder ddHolder;
typedef enum type type;
enum type { __ddtint, __ddtbool, __ddtddString, __ddtchar, __ddtcharP, __ddtfloat, __ddtdouble, __ddtddsize, __ddtddLine, __ddtddSquare };


ddHolder make_ddHolder(ddsize _len);
void raze_ddHolder(ddHolder* _h);

void __hset(ddHolder h, ddsize i, type t, ...);
void __hpush(ddHolder* h, type t, ...);
void* __hget(ddHolder h, ddsize i);
type hgetT(ddHolder h, ddsize i);


struct ddHolder
{
	void** val;
	type* types;
	ddsize len;
	ddsize cap;
};

ddHolder make_ddHolder(ddsize _len)
{
	ddHolder _o;
	_o.val = make(void, _len + __BYINC);
	_o.types = make(type, _len + __BYINC);
	_o.len = 0;
	_o.cap = _len + __BYINC;
	return _o;
}
void raze_ddHolder(ddHolder* _h)
{
	raze(_h->val);
	raze(_h->types);
}
void __hset(ddHolder h, ddsize i, type t, ...)
{
	va_list arg;
	va_start(arg, t);
	switch (t)
	{
		case __ddtint:
		{
			int v = va_arg(arg, int);
			h.val[i] = (void*)(&v);
			h.types[i] = t;
			break;
		}
		case __ddtbool:
		{
			bool v = (char)va_arg(arg, int);
			h.val[i] = (void*)(&v);
			h.types[i] = t;
			break;
		}
		case __ddtddString:
		{
			ddString v = va_arg(arg, ddString);
			h.val[i] = (void*)(&v);
			h.types[i] = t;
			break;
		}
		case __ddtddLine:
		{
			ddLine v = va_arg(arg, ddLine);
			h.val[i] = (void*)(&v);
			h.types[i] = t;
			break;
		}
		case __ddtddSquare:
		{
			ddSquare v = va_arg(arg, ddSquare);
			h.val[i] = (void*)(&v);
			h.types[i] = t;
			break;
		}
	}

	va_end(arg);
}
void __hpush(ddHolder* h, type t, ...)
{
	ddsize i = h->len;

	va_list arg;
	va_start(arg, t);
	switch (t)
	{
		case __ddtint:
		{
			int v = va_arg(arg, int);
			h->val[i] = (void*)(&v);
			h->types[i] = t;
			break;
		}
		case __ddtfloat:
		{
			float v = (float)va_arg(arg, double);
			h->val[i] = (void*)(&v);
			h->types[i] = t;
			break;
		}
		case __ddtdouble:
		{
			double v = va_arg(arg, double);
			h->val[i] = (void*)(&v);
			h->types[i] = t;
			break;
		}
		case __ddtddString:
		{
			ddString v = va_arg(arg, ddString);
			h->val[i] = (void*)(&v);
			h->types[i] = t;
			break;
		}
		case __ddtddLine:
		{
			ddLine v = va_arg(arg, ddLine);
			h->val[i] = (void*)(&v);
			h->types[i] = t;
			break;
		}
		case __ddtddSquare:
		{
			ddSquare v = va_arg(arg, ddSquare);
			h->val[i] = (void*)(&v);
			h->types[i] = t;
			break;
		}
		case __ddtbool:
		{
			bool v = (char)va_arg(arg, int);
			h->val[i] = (void*)(&v);
			h->types[i] = t;
			break;
		}
	}
	h->len++;

	va_end(arg);
}
void* __hget(ddHolder h, ddsize i)
{
	return h.val[i];
}
type hgetT(ddHolder h, ddsize i)
{
	return h.types[i];
}
