#ifndef __ddcColors__
#define __ddcColors__

#include <math.h>
#include <stdlib.h>

#define CRGB(r,g,b) "\x1b[38;2;" #r ";" #g ";" #b "m"

#define CWHITE "\x1b[38;2;255;255;255m"
#define CBLACK "\x1b[38;2;0;0;0m"
#define CRED "\x1b[38;2;255;0;0m"
#define CGREEN "\x1b[38;2;0;255;0m"
#define CBLUE "\x1b[38;2;0;0;255m"
#define CYELLOW "\x1b[38;2;255;255;0m"
#define CTEAL "\x1b[38;2;0;255;255m"
#define CPURPLE "\x1b[38;2;255;0;255m"

struct color
{
	union
	{
		struct { int r, g, b; };
		struct { int h, s, v; };
	};
};

struct color make_color(int r, int g, int b)
{
	struct color output;
	output.r = r;
	output.g = g;
	output.b = b;
	return output;
}

struct color HSVtoRGB(float h, float S,float V)
{
}



#endif
