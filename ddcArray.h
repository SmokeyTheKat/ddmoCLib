#ifndef __ddcArray__
#define __ddcArray__

#include <malloc.h>

typedef struct
{
	void* data;
	long len;
	long cap;
} ddArray;

#define make_ddArray(s, c) { \
		(s).data = malloc(c); \
		(s).len = 0; \
		(s).cap = c; \
	}
#define ddArray_push(s, v, t) { \
		if ((s).len + sizeof(t) + 1 >= (s).cap) \
		{ \
			(s).cap += 10*sizeof(t); \
			char* __new_v_data_l = malloc((s).cap); \
			for (long __vi_l = 0; __vi_l < (s).len; __vi_l++) \
				__new_v_data_l[__vi_l] = ((char*)(s).data)[__vi_l]; \
			free((s).data); \
			(s).data = __new_v_data_l; \
		} \
		*((t*)(&((char*)(s).data)[(s).len])) = (t)(v); \
		(s).len += sizeof(t); \
	}
#define ddArray_pop(s, o, t) { \
		*o = *(t*)(&(((char*)((s).data))[(s).len-sizeof(t)])); \
		(s).len -= sizeof(t); \
	}
#define ddArray_set(s, v, i, t) { \
		*(t*)(&(((char*)((s).data))[i*sizeof(t)])) = v; \
	}
#define ddArray_get(s, i, t) \
		(*(t*)(&(((char*)((s).data))[i*sizeof(t)])))
#define ddArray_length(s, t) \
		((s).len/sizeof(t))
#define ddArray_top(s, v, t) \
		(*(t*)(&(((char*)((s).data))[(s).len-sizeof(t)])))

#endif
