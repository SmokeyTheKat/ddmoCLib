#ifndef __ddcPrint__
#define __ddcPrint__

#include <ddcDef.h>
#include <ddcString.h>


#ifndef chPrintL
	#define chPrintL chPrintLine
	#endif
#ifndef dsPrintL
	#define dsPrintL dsPrintLine
	#endif


void __ddPrint(const void* _v, const ddsize _len);
void chPrint(const char* _ch);
void chPrintLine(const char* _ch);
void cPrint(const char _c);
void dsPrint(const ddString _ds);
void dsPrintLine(const ddString _ds);


void __ddPrint(const void* _v, const ddsize _len)
{
#if __x86_64__
	__asm__		(".intel_syntax;"
			 "mov %%rsi, %0;"
			 "mov %%rdx, %1;"
			 "mov %%rax, 1;"
			 "mov %%rdi, 0;"
			 "syscall;"
			 ".att_syntax;"
			 :
			 :"r"(_v), "r"(_len)
			 :"rsi", "rdx");
#else
	__asm__		(".intel_syntax;"
			 "mov %%esi, %0;"
			 "mov %%edx, %1;"
			 "mov %%eax, 1;"
			 "mov %%edi, 0;"
			 "syscall;"
			 ".att_syntax;"
			 :
			 :"r"(_v), "r"(_len)
			 :"esi", "edx");
#endif

}

void chPrint(const char* _ch)
{
	ddsize _len;
	chlen(_ch, &_len);
	__ddPrint(_ch, _len);
}
void chPrintLine(const char* _ch)
{
	chPrint(_ch);
	cPrint(dnl);
}


void cPrint(const char _c)
{
	__ddPrint(&_c, 1);
}


void dsPrint(const ddString _ds)
{
	__ddPrint(_ds.cstr, _ds.length);
}
void dsPrintLine(const ddString _ds)
{
	dsPrint(_ds);
	cPrint(dnl);
}



#endif
