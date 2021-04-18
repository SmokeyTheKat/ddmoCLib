#ifndef __ddcX11Env__
#define __ddcX11Env__

#include <X11/Xlib.h>
#include <X11/keysym.h>

struct ddXE_settings
{
	void(*start)(void);
	void(*draw)(void);
	void(*keypress)(unsigned char);
	void(*keyrelease)(unsigned char);
	void(*mousedown)(int, int, int);
	void(*mouseup)(int, int, int);
	void(*mousemove)(int, int);
	void(*mousedownmove)(int, int, int);
	char* running;
};

static Display* d;
static Window w;
static GC gc;
static XEvent e;
static int s;

unsigned long XRGB(int r, int g, int b)
{
    return b + (g<<8) + (r<<16);
}

void ddXE_get_mouse_pos(int* x, int* y)
{
	void* v;
	XQueryPointer(d, w, v, v, v, v, x, y, v);
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
void ddXE_clear(void)
{
	XClearWindow(d, w);
}
void ddXE_flush(void)
{
	XFlush(d);
}
void ddXE_set_pixel(int x, int y)
{
	XDrawPoint(d, w, gc, x, y);
}
void ddXE_draw_rect(int x1, int y1, int x2, int y2)
{
	XFillRectangle(d, w, gc, x1, y1, x2, y2);
}
void ddXE_draw_dot(int x, int y, int size)
{
	XFillArc(d, w, gc, x-(size/2), y-(size/2), size, size, 0, 360*64);
}
void ddXE_draw_line(int x1, int y1, int x2, int y2)
{
	XDrawLine(d, w, gc, x1, y1, x2, y2);
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

int ddXE_start(const struct ddXE_settings set)
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
	XSelectInput(d, w, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
	XMapWindow(d, w);

	bool lstarted = false;
	int cmousebut = -1;
	int cmousedown = 0;

	while (*set.running)
	{
		XNextEvent(d, &e);
		if (!lstarted)
		{
			if (set.start) set.start();
			lstarted = true;
		}
		switch (e.type)
		{
			case Expose:
				if (set.draw) set.draw();
				break;
			case KeyPress:
				if (set.keypress) set.keypress(XLookupKeysym(&(e.xkey), 0));
				break;
			case KeyRelease:
				if (set.keyrelease) set.keyrelease(XLookupKeysym(&(e.xkey), 0));
				break;
			case MotionNotify:
			{
				if (cmousedown)
				{
					if (set.mousedownmove) set.mousedownmove(cmousebut, e.xbutton.x, e.xbutton.y);
				}
				else
				{
					if (set.mousemove) set.mousemove(e.xbutton.x, e.xbutton.y);
				}
			} break;
			case ButtonPress:
			{
				cmousedown = 1;
				switch (e.xbutton.button)
				{
					case Button1:
						cmousebut = 1;
						if (set.mousedown) set.mousedown(1, e.xbutton.x, e.xbutton.y);
						break;
					case Button2:
						cmousebut = 2;
						if (set.mousedown) set.mousedown(2, e.xbutton.x, e.xbutton.y);
						break;
					case Button3:
						cmousebut = 3;
						if (set.mousedown) set.mousedown(3, e.xbutton.x, e.xbutton.y);
						break;
					default:
						cmousebut = -1;
						if (set.mousedown) set.mousedown(-1, e.xbutton.x, e.xbutton.y);
						break;
				}
			} break;
			case ButtonRelease:
			{
				cmousedown = 0;
				switch (e.xbutton.button)
				{
					case Button1:
						if (set.mouseup) set.mouseup(1, e.xbutton.x, e.xbutton.y);
						break;
					case Button2:
						if (set.mouseup) set.mouseup(2, e.xbutton.x, e.xbutton.y);
						break;
					case Button3:
						if (set.mouseup) set.mouseup(3, e.xbutton.x, e.xbutton.y);
						break;
					default:
						if (set.mouseup) set.mouseup(-1, e.xbutton.x, e.xbutton.y);
						break;
				}
			} break;
		}
	}

	XCloseDisplay(d);

	return 0;
}


#endif
