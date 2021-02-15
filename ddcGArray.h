#ifndef __ddcGArray_h__
#define __ddcGArray_h__

#define gArray_get(h, i, t) (*((t*)__gArray_get(h, i)))
#define gArray_get_pointer(h, i, t) ((t*)__gArray_get(h, i))
#define gArray_get_p(h, i, t) ((t*)__gArray_get(h, i))
#define gArray_set(h, v, i) __gArray_set(h, (void*)(&v), i)
#define gArray_push(h, v) __gArray_push(h, (void*)(&v))
#define gArray_pop(h, t) (*((t*)__gArray_pop(h)))

typedef struct gArray gArray;

gArray make_gArray(unsigned long _len);
void raze_gArray(gArray* _h);

bool __gArray_set(gArray* _h, void* _v, unsigned long _i);
bool __gArray_push(gArray* _h, void* _v);
void* __gArray_get(gArray _h, unsigned long _i);


struct gArray
{
	void** val;
	unsigned long length;
	unsigned long capacity;
};

gArray make_gArray(unsigned long _len)
{
	gArray _o;
	_o.val = malloc(sizeof(void*)*_len);
	_o.length = 0;
	_o.capacity = _len;
	return _o;
}
void raze_gArray(gArray* _h)
{
	free(_h->val);
}
bool __gArray_set(gArray* _h, void* _v, unsigned long _i)
{
	if (_i > _h->length)
		return 0;
	_h->val[_i] = _v;
	return 1;
}
bool __gArray_push(gArray* _h, void* _v)
{
	if (_h->length+1 > _h->capacity)
		return 0;
	_h->val[_h->length++] = _v;
	return 1;
}
void* __gArray_pop(gArray* _h)
{
	if (_h->length == 0)
		return (void*)0;
	return _h->val[--(_h->length)];
}
void* __gArray_get(gArray _h, unsigned long _i)
{
	return _h.val[_i];
}

#endif
