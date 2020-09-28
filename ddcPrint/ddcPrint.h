#ifndef __ddcPrint__
#define __ddcPrint__


#include <ddcDef.h>
#include <stdarg.h>

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



void intPrint(int _v)
{
	ddString _ds = intTds(_v);
	dsPrint(_ds);
	raze_ddString(&_ds);
}
void fltPrint(float _v)
{
	ddString _ds = floatTds(_v);
	dsPrint(_ds);
	raze_ddString(&_ds);
}
void dblPrint(double _v)
{
	fltPrint((float)_v);
}





void chPrint(const char* _ch)
{
	ddsize _len;
	chlen(_ch, &_len);
	__ddPrint(_ch, _len);
}
void chPrintC(ddsize _l, ...)
{
	va_list arg;
	va_start(arg, _l);
	chPrint(va_arg(arg, const char*));
	for (ddsize i = 2; i < _l+1; i++)
		chPrint(va_arg(arg, const char*));
	va_end(arg);
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

void dsPrintC(ddsize _l, ...)
{
	va_list arg;
	va_start(arg, _l);
	dsPrint(va_arg(arg, ddString));
	for (ddsize i = 2; i < _l+1; i++)
		dsPrint(va_arg(arg, ddString));
	va_end(arg);
}

void dsPrintLine(const ddString _ds)
{
	dsPrint(_ds);
	cPrint(dnl);
}



#endif
