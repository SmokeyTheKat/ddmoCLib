#include <ddcDef.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include <stdio.h>

#define hget(h, i, t) (*((t*)__hget(h, i)))
#define hset(h, i, t, v) __hset(h, i, __ddt##t, v)
#define hpush(h, t, v) __hpush(&h, __ddt##t, v)

typedef struct holder holder;
typedef enum type type;
enum type { __ddtint, __ddtbool, __ddtddString, __ddtchar, __ddtcharP, __ddtfloat, __ddtdouble, __ddtddsize };


holder make_holder(ddsize _len);
void raze_holder(holder* _h);

void __hset(holder h, ddsize i, type t, ...);
void __hpush(holder* h, type t, ...);
void* __hget(holder h, ddsize i);
type hgettype(holder h, ddsize i);


struct holder
{
	void** val;
	type* types;
	ddsize len;
	ddsize cap;
};

holder make_holder(ddsize _len)
{
	holder _o;
	_o.val = make(void, _len + __byinc);
	_o.types = make(type, _len + __byinc);
	_o.len = 0;
	_o.cap = _len + __byinc;
	return _o;
}
void raze_holder(holder* _h)
{
	raze(_h->val);
	raze(_h->types);
}
void __hset(holder h, ddsize i, type t, ...)
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
	}

	va_end(arg);
}
void __hpush(holder* h, type t, ...)
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
void* __hget(holder h, ddsize i)
{
	return h.val[i];
}
type hgettype(holder h, ddsize i)
{
	return h.types[i];
}
