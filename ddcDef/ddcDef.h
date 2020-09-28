#ifndef __ddcDef__
#define __ddcDef__


#include <stdlib.h>

#ifndef ddsize
	#define ddsize unsigned long long int
	#endif
#ifndef __byinc
	#define __byinc 10
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
#ifndef bool
	typedef char bool;
	#endif
#ifndef true
	#define true 1
	#endif
#ifndef false
	#define false 0
	#endif

#ifndef make
	#define make(t,s) ((t*)malloc(s*sizeof(t)))
	#endif
#ifndef raze
	#define raze(t) (free(t))
	#endif

#endif
