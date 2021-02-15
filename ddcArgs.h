#ifndef __ddcArguments__
#define __ddcArguments__

typedef char bool;

typedef struct pArgs pArgs;

pArgs init_pArgs(int _argc, char** _argv);
bool pArgs_has(const pArgs args, const char* cstr);
char* pArgs_get(const pArgs args, int index);
int pArgs_get_index(const pArgs args, const char* cstr);
char* pArgs_get_value(const pArgs args, const char* cstr);

struct pArgs
{
	int argc;
	char** argv;
};

pArgs init_pArgs(int _argc, char** _argv)
{
	pArgs output;
	output.argc = _argc;
	output.argv = _argv;
	return output;
}
char* pArgs_get_value(const pArgs args, const char* cstr)
{
	int index = pArgs_get_index(args, cstr);
	return (index != -1) ? args.argv[index+1] : (char*)0;
}
char* pArgs_get(const pArgs args, int index)
{
	return (index >= 0 && index < args.argc) ? args.argv[index] : (char*)0;
}
int pArgs_get_index(const pArgs args, const char* cstr)
{
	for (int i = 0; i < args.argc; i++)
	{
		int indx = 0;
		while (args.argv[i][indx] == cstr[indx])
		{
			if ((args.argv[i][indx] == 0) || (cstr[indx] == 0))
			{
				if ((args.argv[i][indx] == 0) && (cstr[indx] == 0)) return i;
				else goto DDCARGS_CONTINUE_INDEX_LOOP;
			}
			indx++;
		}
DDCARGS_CONTINUE_INDEX_LOOP:;
	}
	return -1;
}
bool pArgs_has(const pArgs args, const char* cstr)
{
	for (int i = 0; i < args.argc; i++)
	{
		int indx = 0;
		while (args.argv[i][indx] == cstr[indx])
		{
			if ((args.argv[i][indx] == 0) || (cstr[indx] == 0))
			{
				if ((args.argv[i][indx] == 0) && (cstr[indx] == 0)) return 1;
				else return 0;
			}
			indx++;
		}
	}
	return 0;
}

#endif
