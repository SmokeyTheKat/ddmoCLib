#ifndef __ddcArray__
#define __ddcArray__

typedef struct
{
	void* data;
	long len;
	long cap;
} ddArray;

#define make_ddArray(s, c) { \
		(s)->data = malloc(c); \
		(s)->len = 0; \
		(s)->cap = c; \
	}
#define ddArray_push(s, v, t) { \
		if ((s)->len + sizeof(t) >= (s)->cap) \
			realloc((s)->data, (s)->len+(2*sizeof(t))); \
		*((t*)(&((char*)(s)->data)[(s)->len])) = (t)(v); \
		(s)->len += sizeof(t); \
	}
#define ddArray_pop(s, o, t) { \
		*o = *(t*)(&(((char*)((s)->data))[(s)->len-sizeof(t)])); \
		(s)->len -= sizeof(t); \
	}
#define ddArray_set(s, v, i, t) { \
		*(t*)(&(((char*)((s)->data))[i*sizeof(t)])) = v; \
	}
#define ddArray_get(s, i, t) \
		(*(t*)(&(((char*)((s)->data))[i*sizeof(t)])))
#define ddArray_length(s, t) \
		((s)->len/sizeof(t))
#define ddArray_top(s, v, t) \
		(*(t*)(&(((char*)((s)->data))[(s)->len-sizeof(t)])))

#endif
