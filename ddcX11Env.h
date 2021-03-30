#ifndef __ddcX11Env__
#define __ddcX11Env__

#include <X11/Xlib.h>
#include <X11/keysym.h>

static Display* d;
static Window w;
static GC gc;
static XEvent e;
static int s;

unsigned long XRGB(int r, int g, int b)
{
    return b + (g<<8) + (r<<16);
}

int ddXE_get_width(void)
{
	XWindowAttributes xwa;
	XGetWindowAttributes(d, w, &xwa);
	return xwa.width;
}
int ddXE_get_height(void)
{
	XWindowAttributes xwa;
	XGetWindowAttributes(d, w, &xwa);
	return xwa.height;
}
void ddXE_set_color(int r, int g, int b)
{
	XSetForeground(d, gc, XRGB(r, g, b));
}
void ddXE_flush(void)
{
	XFlush(d);
}
void ddXE_set_pixel(int x, int y)
{
	XDrawPoint(d, w, gc, x, y);
}
void ddXE_draw_text(int x, int y, char* str, int length)
{
	XDrawString(d, w, gc, x, y, str, length);
}
void ddXE_draw_bitmap(int x, int y, char* filename)
{
	int width, height;
	int hx, hy;
	Pixmap pm;
	XReadBitmapFile(d, w, filename, &width, &height, &pm, &hx, &hy);
	XCopyArea(d, pm, w, gc, 0, 0, width, height, x, y);
}

int ddXE_start(void(*fdraw)(void), void(*fkeypress)(char), char* running)
{
	d = XOpenDisplay(NULL);
	if (d == NULL)
	{
		return 1;
	}
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
					BlackPixel(d, s), WhitePixel(d, s));
	gc = DefaultGC(d, s);
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XMapWindow(d, w);

	while (1)
	{
		if (!(*running)) break;
		XNextEvent(d, &e);
		if (e.type == Expose)
		{
			fdraw();
		}
		if (e.type == KeyPress)
		{
			fkeypress(XLookupKeysym(&(e.xkey), 0));
		}
	}

	XCloseDisplay(d);

	return 0;
}


#endif
