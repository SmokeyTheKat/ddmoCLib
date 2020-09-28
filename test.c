#include <ddcString.h>
#include <ddcDef.h>

int main(void)
{
	ddString ds = nddString("yo");
	ddString bs = nddString(" bro");
	ddString cs;
	dscpy(&cs, &ds);
	dsadd(&cs, &bs);
	printf(ds.cstr);
	printf(bs.cstr);
	printf(cs.cstr);


	dddString(&ds);
	dddString(&bs);
	dddString(&cs);
	return 0;
}
