#ifndef __ddcApplications__
#define __ddcApplications__

#include "./ddcPrint.h"
#include "./ddcColors.h"
#include "./ddcChars.h"

#define DDAPP_PCOLOR(r) ddPrintf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm", r->fgc.r, r->fgc.g, r->fgc.b, r->bgc.r, r->bgc.g, r->bgc.b)

#define DDAPP_RECT_CONTENT	int x, y; \
				int width, height; \
				struct color bgc, fgc; \
				int border_type; \
				struct ddApp_rect* parent;

struct ddApp_rect
{
	DDAPP_RECT_CONTENT
};

struct ddApp_list
{
	DDAPP_RECT_CONTENT

	struct color item_fgc;
	struct color item_bgc;
	ddString* items;
	int item_count;
	int selected;
};

struct ddApp_input
{
	DDAPP_RECT_CONTENT

	ddString content;
	int pos;
};

struct ddApp_text_area
{
	DDAPP_RECT_CONTENT

	ddString content;
	int pos;
};

void ddApp_set_rect(void* vrect, int x, int y, int width, int height)
{
	struct ddApp_rect* rect = (struct ddApp_rect*)vrect;
	rect->x = x;
	rect->y = y;
	rect->width = width-1;
	rect->height = height-1;
	rect->bgc = (struct color){0};
	rect->fgc = (struct color){0};
	rect->border_type = 0;
	rect->parent = 0;
}
void ddApp_set_input(void* vinput)
{
	struct ddApp_input* input = (struct ddApp_input*)vinput;
	input->pos = 0;
}
void ddApp_set_text_area(void* vinput)
{
	struct ddApp_text_area* input = (struct ddApp_text_area*)vinput;
	input->pos = 0;
}
void ddApp_set_list(void* vlist, int item_count, struct color fgc, struct color bgc)
{
	struct ddApp_list* list = (struct ddApp_list*)vlist;
	list->item_count = item_count;
	list->items = malloc(sizeof(ddString) * list->item_count);
	list->selected = 0;
	list->item_fgc = fgc;
	list->item_bgc = bgc;
}

void ddApp_gpos(void* vrect, int* x, int* y)
{
	struct ddApp_rect* rect = (struct ddApp_rect*)vrect;
	if (rect->parent)
	{
		ddApp_gpos(rect->parent, x, y);
		*x += rect->x;
		*y += rect->y;
	}
	else
	{
		*x = rect->x;
		*y = rect->y;
	}
}

void ddApp_set_bgc(void* vrect, struct color col)
{
	struct ddApp_rect* rect = (struct ddApp_rect*)vrect;
	rect->bgc = col;
}
void ddApp_set_fgc(void* vrect, struct color col)
{
	struct ddApp_rect* rect = (struct ddApp_rect*)vrect;
	rect->fgc = col;
}
void ddApp_set_parent(void* vrect, void* vparent)
{
	struct ddApp_rect* rect = (struct ddApp_rect*)vrect;
	rect->parent = vparent;
}

void ddApp_draw_rect(void* vrect)
{
	struct ddApp_rect* rect = (struct ddApp_rect*)vrect;
	int gx, gy;
	ddApp_gpos(vrect, &gx, &gy);
	ddPrintf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm", rect->fgc.r, rect->fgc.g, rect->fgc.b, rect->bgc.r, rect->bgc.g, rect->bgc.b);
	draw_rect(gx, gy, gx + rect->width, gy + rect->height, " ");
}

void ddApp_draw_list(struct ddApp_list* list)
{
	ddApp_draw_rect(list);
	ddPrintf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm", list->item_fgc.r, list->item_fgc.g, list->item_fgc.b,
								 list->item_bgc.r, list->item_bgc.g, list->item_bgc.b);
	int gx, gy;
	ddApp_gpos(list, &gx, &gy);
	gx += 1;
	gy += 1;
	for (int i = 0; i < list->item_count; i++)
	{
		cursor_move_to(gx, gy+i);
		ddPrints(list->items[i].cstr);
	}
	ddPrintf("\x1b[48;2;%d;%d;%dm\x1b[38;2;%d;%d;%dm", list->item_fgc.r, list->item_fgc.g, list->item_fgc.b,
								 list->item_bgc.r, list->item_bgc.g, list->item_bgc.b);
	cursor_move_to(gx, gy + list->selected);
	ddPrints(list->items[list->selected].cstr);
}
void ddApp_list_select(struct ddApp_list* list, int idx)
{
	list->selected = idx;
	ddApp_draw_list(list);
}
void ddApp_draw_input(struct ddApp_input* input)
{
	ddApp_draw_rect(input);
	ddPrintf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm", input->fgc.r, input->fgc.g, input->fgc.b, input->bgc.r, input->bgc.g, input->bgc.b);
	int gx, gy;
	ddApp_gpos(input, &gx, &gy);
	gx += 1;
	gy += 1;
	int len = input->content.length;
	if (len - input->pos >= input->width) len = input->width - 2;
	cursor_move_to(gx, gy);
	ddPrint(input->content.cstr + input->pos, len);
}
void ddApp_draw_text_area(struct ddApp_text_area* tarea)
{
	ddApp_draw_rect(tarea);
	ddPrintf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm", tarea->fgc.r, tarea->fgc.g, tarea->fgc.b, tarea->bgc.r, tarea->bgc.g, tarea->bgc.b);
	int gx, gy;
	ddApp_gpos(tarea, &gx, &gy);
	gx += 1;
	gy += 1;
	int width = tarea->width-2;
	int ypos = 0;
	int xpos = 0;
	cursor_move_to(gx, gy + ypos);
	for (int i = 0; i < tarea->content.length; i++)
	{
		if (tarea->content.cstr[i] == '\n')
		{
			ypos++;
			xpos = 0;
			cursor_move_to(gx, gy + ypos);
			continue;
		}
		if (ypos >= tarea->pos) ddPrint_char(tarea->content.cstr[i]);
		xpos++;
		if (xpos >= width)
		{
			ypos++;
			xpos = 0;
			cursor_move_to(gx, gy + ypos);
		}
	}
}

#endif
