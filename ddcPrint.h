#ifndef __ddcPrint__
#define __ddcPrint__

#include <stdlib.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <unistd.h>

void ddPrint(const void* vptr, const unsigned long length);
void ddPrintf(const char* _ch, ...);
void ddPrint_cstring(const char* cstr);
void ddPrint_char(char chr);
void ddPrint_int(long num);
void ddPrint_float(float flt);
void ddPrint_nl(void);

void ddError(const char* _ch);
void ddErrorf(const char* _ch, ...);

void draw_line(int x1, int y1, int x2, int y2, const char* chr);
void draw_line_half(int x1, int y1, int x2, int y2, const char* chr);
void draw_rect(int x1, int y1, int x2, int y2, const char* chr);
void draw_rect_outline(int x1, int y1, int x2, int y2, const char* chr);

int cursor_get_width(void);
int cursor_get_height(void);
void cursor_move(int x, int y);
void cursor_move_to(int x, int y);
void cursor_up(void);
void cursor_down(void);
void cursor_left(void);
void cursor_right(void);
void cursor_return(void);
void cursor_erase_line(void);
void cursor_clear(void);
void cursor_save(void);
void cursor_restore(void);
void cursor_home(void);
void cursor_up(void);
void cursor_down(void);
void cursor_left(void);
void cursor_right(void);
void cursor_style_bold(void);
void cursor_style_dim(void);
void cursor_style_italic(void);
void cursor_style_underline(void);
void cursor_style_slow_blink(void);
void cursor_style_fast_blink(void);
void cursor_style_invert(void);
void cursor_style_dashed(void);
void cursor_set_fg_color(int r, int g, int b);
void cursor_set_bg_color(int r, int g, int b);
void cursor_style_reset(void);

static unsigned long  __ddcPrint_int_get_length(long num)
{
	if (num < 10)
		return 1;
	else if (num < 100)
		return 2;
	else if (num < 1000)
		return 3;
	else if (num < 10000)
		return 4;
	else if (num < 100000)
		return 5;
	else if (num < 1000000)
		return 6;
	else if (num < 10000000)
		return 7;
	else if (num < 100000000)
		return 8;
	else if (num < 1000000000)
		return 9;
	else if (num < 10000000000)
		return 10;
	else if (num < 100000000000)
		return 11;
	else if (num < 1000000000000)
		return 12;
	return 13;
}

static long __ddcPrint_floatTCount(long n, long c)
{
    int _o = 1;
    while(c-- > 0)
        _o *= n;

    return _o;
}

static char* __ddcPrint_float_to_cstring(float flt, unsigned long* output_len)
{
	long l1;
	long l2;
	long i;
	long n1;
	long pos;
	long sign;
	long double n2;

	sign = -1;
	if (flt < 0)
	{
		sign = '-';
		flt *= -1;
	}

	n2 = flt;
	n1 = flt;
	l1 = 0;
	l2 = 0;

	while( (n2 - (float)n1) != 0.0 && !((n2 - (float)n1) < 0.0) )
	{
		n2 = flt * (__ddcPrint_floatTCount(10.0, l2 + 1));
		n1 = n2;
		l2++;
	}

	for (l1 = (flt > 1) ? 0 : 1; flt > 1; l1++)
		flt /= 10;

	pos = l1;
	l1 = l1 + 1 + l2;
	n1 = n2;
	if (sign == '-')
	{
		l1++;
		pos++;
	}
	
	char* _o = malloc(l1+1);

	for (i = l1; i >= 0 ; i--)
	{
		if (i == (l1))
			_o[i] = '\0';
		else if(i == (pos))
			_o[i] = '.';
		else if(sign == '-' && i == 0)
			_o[i] = '-';
		else
		{
			_o[i] = (n1 % 10) + '0';
			n1 /= 10;
		}
	}
	*output_len = l1;
/*
	if (_o.cstr[0] == '0' && _o.cstr[_o.length-1] == '.')
	{
		ddString_push_char_front(&_o, '1');
	}
*/
	return _o;
}
static char* __ddcPrint_int_to_cstring(long num, unsigned long* out_length)
{
	char sign = '+';
	if (num < 0)
	{
		sign = '-';
		num *= -1;
	}
	unsigned long length = __ddcPrint_int_get_length(num)+1;
	*out_length = length;
	unsigned long ptr = length;
	char* output = malloc(length+1);
	if (num == 0)
		output[1] = '0';
	while (num)
	{
		int digit = num % 10;
		num /= 10;
		output[--ptr] = '0' + digit;
	}
	if (sign == '-') output[0] = sign;
	else
	{
		length--;
		for (int i = 0; i < length; i++)
			output[i] = output[i+1];
	}
	output[length] = 0;
	return output;
}
static unsigned long __ddcPrint_str_len(const char* cstr)
{
	unsigned long len = 0;
	while (cstr[len++] != 0);
	return len;
}

void ddPrint(const void* vptr, const unsigned long length)
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
			 :"r"(vptr), "r"(length)
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
			 :"r"(vptr), "r"(length)
			 :"esi", "edx");
#endif

}

void ddPrints(const char* cstr)
{
	unsigned long length = __ddcPrint_str_len(cstr);
	ddPrint(cstr, length);
}
void ddPrint_cstring(const char* cstr)
{
	unsigned long length = __ddcPrint_str_len(cstr);
	ddPrint(cstr, length);
}
void ddPrint_char(char chr)
{
	ddPrint(&chr, 1);
}
void ddPrint_int(long num)
{ 
	unsigned long length;
	char* cstr = __ddcPrint_int_to_cstring(num, &length);
	ddPrint(cstr, length);
	free(cstr);
}
void ddPrint_float(float flt)
{
	unsigned long length;
	char* cstr = __ddcPrint_float_to_cstring(flt, &length);
	ddPrint(cstr, length);
}
void ddPrint_nl(void)
{
	char chr_nl = '\n';
	ddPrint(&chr_nl, 1);
}

void ddPrintf(const char* cstr, ...)
{
	va_list ap;
	va_start(ap, cstr);
	unsigned long len = __ddcPrint_str_len(cstr);
	for (int i = 0; i < len; i++)
	{
		switch (cstr[i])
		{
			case '%':
			{
				switch (cstr[i+1])
				{
					case 'f':
						ddPrint_float(va_arg(ap, double));
						i++;
						break;
					case 'd':
						ddPrint_int(va_arg(ap, long));
						i++;
						break;
					case 'c':
						ddPrint_char(va_arg(ap, long));
						i++;
						break;
					case 's':
						ddPrint_cstring(va_arg(ap, char*));
						i++;
						break;
				}
				break;
			}
			default: ddPrint_char(cstr[i]); break;
				
		}
	}
	va_end(ap);
}

void ddError(const char* cstr)
{
	ddPrints("\x1b[38;2;255;255;255m[\x1b[38;2;255;0;0mERROR\x1b[38;2;255;255;255m] ");
	ddPrints(cstr);
	ddPrint_nl();
}

void ddErrorf(const char* cstr, ...)
{
	ddPrints("\x1b[38;2;255;255;255m[\x1b[38;2;255;0;0mERROR\x1b[38;2;255;255;255m] ");
	va_list ap;
	va_start(ap, cstr);
	unsigned long len = __ddcPrint_str_len(cstr);
	for (int i = 0; i < len; i++)
	{
		switch (cstr[i])
		{
			case '%':
			{
				switch (cstr[i+1])
				{
					case 'f':
						ddPrint_float(va_arg(ap, double));
						i++;
						break;
					case 'd':
						ddPrint_int(va_arg(ap, long));
						i++;
						break;
					case 'c':
						ddPrint_char(va_arg(ap, long));
						i++;
						break;
					case 's':
						ddPrint_cstring(va_arg(ap, char*));
						i++;
						break;
				}
				break;
			}
			default: ddPrint_char(cstr[i]); break;
				
		}
	}
	ddPrint_nl();
	va_end(ap);
}

void draw_line_half(int x1, int y1, int x2, int y2, const char* chr)
{
	if (!(x1 == x2 && y1 == y2))
	{
		int xm = (x1+x2)/2;
		int ym = (y1+y2)/2;
		if ((xm == x1 && ym == y1) || (xm == x2 && ym == y2)) return;
		cursor_move_to(xm, ym);
		ddPrints(chr);
		draw_line_half(xm, ym, x2, y2, chr);
		draw_line_half(x1, y1, xm, ym, chr);
	}
}
void draw_line(int x1, int y1, int x2, int y2, const char* chr)
{
	cursor_move_to(x1, y1);
	ddPrints(chr);
	cursor_move_to(x2, y2);
	ddPrints(chr);
	draw_line_half(x1, y1, x2, y2, chr);
}

void draw_rect(int x1, int y1, int x2, int y2, const char* chr)
{
	for (int y = y1; y <= y2; y++)
	{
		cursor_move_to(x1, y);
		for (int x = x1; x <= x2; x++)
			ddPrints(chr);
	}
}
/*
void draw_rect_border(int x1, int y1, int x2, int y2, const char* pfx)
{
	ddString vb = make_format_ddString("%s\x1b[38;2;0;0;0m%s", pfx, "─");
	ddString hb = make_format_ddString("%s\x1b[38;2;0;0;0m%s", pfx, "│");

	draw_line(x1, y1, x2, y1, vb.cstr);
	draw_line(x1, y2, x2, y2, vb.cstr);

	draw_line(x1, y1, x1, y2, hb.cstr);
	draw_line(x2, y1, x2, y2, hb.cstr);

	cursor_move_to(x1, y1); ddPrintf("%s\x1b[38;2;0;0;0m", "┌");
	cursor_move_to(x2, y1); ddPrintf("%s\x1b[38;2;0;0;0m", "┐");
	cursor_move_to(x1, y2); ddPrintf("%s\x1b[38;2;0;0;0m", "└");
	cursor_move_to(x2, y2); ddPrintf("%s\x1b[38;2;0;0;0m", "┘");

	raze_ddString(&vb);
	raze_ddString(&hb);
}
*/
void draw_rect_outline(int x1, int y1, int x2, int y2, const char* chr)
{
	cursor_move_to(x1, y1);
	for (int x = x1; x <= x2; x++)
		ddPrints(chr);

	cursor_move_to(x1, y2);
	for (int x = x1; x <= x2; x++)
		ddPrints(chr);

	for (int y = y1; y <= y2; y++)
	{
		cursor_move_to(x1, y);
		ddPrints(chr);
	}
	for (int y = y1; y <= y2; y++)
	{
		cursor_move_to(x2, y);
		ddPrints(chr);
	}
}

int cursor_get_height(void)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_row;
}
int cursor_get_width(void)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}

void cursor_move(int x, int y)
{
	ddPrintf("\x1b[%dB\x1b[%dC", y, x);
}
void cursor_move_to(int x, int y)
{
	ddPrintf("\x1b[%d;%dH", y+1, x+1);
}
void cursor_return(void)
{
	ddPrint_char('\r');
}
void cursor_erase_line(void)
{
	ddPrint("\x1b[2K", 4);
}
void cursor_clear(void)
{
	ddPrint("\x1b[2J", 4);
}
void cursor_save(void)
{
	ddPrint("\x1b[s", 3);
}
void cursor_restore(void)
{
	ddPrint("\x1b[u", 3);
}
void cursor_home(void)
{
	cursor_move_to(0, 0);
}
void cursor_up(void)
{
	ddPrint("\x1b[A", 3);
}
void cursor_down(void)
{
	ddPrint("\x1b[B", 3);
}
void cursor_left(void)
{
	ddPrint("\x1b[D", 3);
}
void cursor_right(void)
{
	ddPrint("\x1b[C", 3);
}
void cursor_style_bold(void)
{
	ddPrint("\x1b[1m", 4);
}
void cursor_style_dim(void)
{
	ddPrint("\x1b[2m", 4);
}
void cursor_style_italic(void)
{
	ddPrint("\x1b[3m", 4);
}
void cursor_style_underline(void)
{
	ddPrint("\x1b[4m", 4);
}
void cursor_style_slow_blink(void)
{
	ddPrint("\x1b[5m", 4);
}
void cursor_style_fast_blink(void)
{
	ddPrint("\x1b[6m", 4);
}
void cursor_style_invert(void)
{
	ddPrint("\x1b[7m", 4);
}
void cursor_style_dashed(void)
{
	ddPrint("\x1b[9m", 4);
}
void cursor_set_fg_color(int r, int g, int b)
{
	ddPrintf("\x1b[38;2;%d;%d;%dm", r, g, b);
}
void cursor_set_bg_color(int r, int g, int b)
{
	ddPrintf("\x1b[48;2;%d;%d;%dm", r, g, b);
}
void cursor_style_reset(void)
{
	ddPrintf("\x1b[0m", 4);
}

#endif
