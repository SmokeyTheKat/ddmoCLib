#ifndef __ddcDef__
#define __ddcDef__

#include <stdlib.h>

#ifndef __ibmxl__
	typedef enum Ostatus Ostatus;
	enum Ostatus { inactive, active, deleted };
#else
	enum Ostatus { inactive, active, deleted };
#endif


void void__(void) { return; };


#ifndef lambda
	#define lambda(lambda$_ret, lambda$_args, lambda$_body)\
	({\
	lambda$_ret lambda$__anon$ lambda$_args\
	lambda$_body\
	&amp;lambda$__anon$;\
	})
	#endif

#ifndef run
	int __RUN_ERROR = 0;
	#define run __RUN_ERROR = -1;
	#define end(x) __EXIT_JMP_##x:if(__RUN_ERROR==x)
	#define leave(x) __RUN_ERROR=x;goto __EXIT_JMP_##x;
	#endif

#ifndef make(t,s)
	#define make(t,s) ((t*)malloc(s*sizeof(t)))
	#endif
#ifndef makea(t,s)
	#define makea(t,s) ((t*)malloc(s*sizeof(t)))
	#endif
#ifndef makep(t)
	#define makep(t) ((t*)malloc(sizeof(t)))
	#endif
#ifndef raze
	#define raze(t) (free(t))
	#endif



#ifndef __BYINC
	#define __BYINC 10
	#endif
#ifndef MAINF__
	#define MAINF__ int main(ddsize agsc, char** ags)
	#endif
#ifndef SET_DDARGS__
	#define SET_DDARGS__ ddArguments da = make_ddArguments(ags, agsc)
	#define SET_DDARGSV__(x) ddArguments x = make_ddArguments(ags, agsc)
	#endif
#ifndef oBLOCK
	#define oBLOCK {
	#define cBLOCK }
	#endif



#ifndef true
	#define true 1
	#endif
#ifndef false
	#define false 0
	#endif
#ifndef bool
	typedef char bool;
	#endif
#ifndef ddsize
	#define ddsize unsigned long long int
	#endif
#ifndef dnl
	#define dnl '\n'
	#endif
#ifndef NULL
	#define NULL 0
	#endif
#ifndef null
	#define null 0
	#endif
#ifndef nullptr
	#define nullptr 0x00000000
	#endif





#endif
