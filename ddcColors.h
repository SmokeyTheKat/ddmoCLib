#ifndef __ddcColors__
#define __ddcColors__

#include <math.h>
#include <stdlib.h>


struct color
{
	union
	{
		struct { int r, g, b; };
		struct { int h, s, v; };
	};
};

struct color HSVtoRGB(float h, float S,float V)
{
	if (h > 360 || h < 0 || S > 100 || S < 0 || V > 100 || V < 0)
		return (struct color){0};
	float s = S/100;
	float v = V/100;
	float C = s*v;
	float X = C * (1-abs(fmod(h/60.0, 2)-1));
	float m = v-C;
	float r,g,b;
	if (h >= 0 && h < 60)
	{
		r = C;
		g = X;
		b = 0;
	}
	else if (h >= 60 && h < 120)
	{
		r = X;
		g = C;
		b = 0;
	}
	else if (h >= 120 && h < 180)
	{
		r = 0;
		g = C;
		b = X;
	}
	else if (h >= 180 && h < 240)
	{
		r = 0;
		g = X;
		b = C;
	}
	else if (h >= 240 && h < 30
	{
		r = X;
		g = 0;
		b = C;
	}
	else
	{
		r = C;
		g = 0;
		b = X;
	}
	int R = (r+m)*255;
	int G = (g+m)*255;
	int B = (b+m)*255;
	struct color output;
	output.r = R;
	output.g = G;
	output.b = B;
	return output;
}



#endif
