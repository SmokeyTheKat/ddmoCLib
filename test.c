#include "./ddcBeep.h"
#include "./ddcDef.h"
#include "./ddcColors.h"
#include "./ddcString.h"
#include "./ddcPrint.h"
#include "./ddcApplication.h"
#include <stdio.h>
#include <string.h>
#include <math.h>



int main(int argc, char** argv)
{
	ddBeep();
	cursor_clear();

	struct ddApp_rect root;
	struct ddApp_text_area text;
	struct ddApp_list list;
	struct ddApp_input input;
	struct ddApp_rect cont;

	ddApp_set_rect(&root, 0, 0, cursor_get_width(), cursor_get_height());

	ddApp_set_rect(&text, 0, 0, 40, 10);
	ddApp_set_parent(&text, &root);
	ddApp_set_fgc(&text, make_color(0,0,0));
	ddApp_set_bgc(&text, make_color(255,255,255));
	text.content = make_ddString("OMG hi there how are you doing? I am doing very good. That is very sick. Omg omaom ogm POGGG");

	ddApp_set_rect(&list, 40, 0, 20, 10);
	ddApp_set_list(&list, 8, make_color(0, 0, 0), make_color(255, 0, 255));
	ddApp_set_parent(&list, &root);
	ddApp_set_fgc(&list, make_color(0,0,0));
	ddApp_set_bgc(&list, make_color(255,0,255));
	list.items[0] = make_constant_ddString("hello :)");
	list.items[1] = make_constant_ddString("option");
	list.items[2] = make_constant_ddString("Pick me");
	list.items[3] = make_constant_ddString("WOW");
	list.items[4] = make_constant_ddString("bad option");
	list.items[5] = make_constant_ddString("help");
	list.items[6] = make_constant_ddString("mad");
	list.items[7] = make_constant_ddString("YOOOOO");

	ddApp_set_rect(&cont, 0, 10, 80, 20);
	ddApp_set_parent(&cont, &root);
	ddApp_set_fgc(&cont, make_color(0,0,0));
	ddApp_set_bgc(&cont, make_color(0,0,255));

	ddApp_set_rect(&input, 20, 10, 40, 3);
	ddApp_set_input(&input);
	ddApp_set_parent(&input, &cont);
	ddApp_set_fgc(&input, make_color(0,0,0));
	ddApp_set_bgc(&input, make_color(255,255,0));
	input.content = make_ddString("123456789 here is some text and ther is too much INPUT TEXT HI THERE :)");

	ddApp_draw_text_area(&text);
	ddApp_draw_list(&list);
	ddApp_draw_rect(&cont);
	ddApp_draw_input(&input);

	ddPrints("\x1b[0m");
	cursor_move_to(0, cursor_get_height()-1);
	return 0;
}
