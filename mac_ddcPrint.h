#ifndef __ddcPrint__
#define __ddcPrint__

void __ddPrint(const char* _v, const ddsize _len)
{
	long write = 0x2000004;
	long stdout = 1;
	char* str = (char*)_v;
	unsigned long len = (unsigned long)_len;
	unsigned long ret = 0;
	__asm__		(
			 "movq %1, %%rax;\n"
			 "movq %2, %%rdi;\n"
			 "movq %3, %%rsi;\n"
			 "movq %4, %%rdx;\n"
			 "syscall;\n"
			 "movq %%rax, %0;\n"
			 : "=g"(ret)
			 :"g"(write), "g"(stdout), "g"(str), "g"(len)
			 :);

}

#endif
