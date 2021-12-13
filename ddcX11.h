#ifndef __ddcX11__
#define __ddcX11__

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

static Display* __s_mdisplay;
static Window __s_mroot_window;

void ddX11_init(void)
{
	__s_mdisplay = XOpenDisplay(0);
	__s_mroot_window = XRootWindow(__s_mdisplay, 0);
}

void ddX11_pointer_left_down(void)
{
	XTestFakeButtonEvent(__s_mdisplay, Button1, true, 0);
	XFlush(__s_mdisplay);
}
void ddX11_pointer_left_up(void)
{
	XTestFakeButtonEvent(__s_mdisplay, Button1, false, 0);
	XFlush(__s_mdisplay);
}
void ddX11_pointer_click(void)
{
	ddX11_pointer_left_down();
	ddX11_pointer_left_up();
}

void ddX11_pointer_move_to(int x, int y)
{
	XSelectInput(__s_mdisplay, __s_mroot_window, KeyReleaseMask);
	XWarpPointer(__s_mdisplay, None, __s_mroot_window, 0, 0, 0, 0, x, y);
	XFlush(__s_mdisplay);
}
void ddX11_pointer_move(int x, int y)
{
	XSelectInput(__s_mdisplay, __s_mroot_window, KeyReleaseMask);
	XWarpPointer(__s_mdisplay, None, None, 0, 0, 0, 0, x, y);
	XFlush(__s_mdisplay);
}

void ddX11_pointer_get_pos(int* x, int* y)
{
	Window void_window;
	int void_int;
	unsigned int void_uint;
	XQueryPointer(__s_mdisplay, __s_mroot_window, &void_window, &void_window, x, y, &void_int, &void_int, &void_uint);
}


#endif
