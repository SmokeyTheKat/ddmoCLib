#ifndef __ddcLib_ddcMem_h__
#define __ddcLib_ddcMem_h__

void mem_set(void* dest, int value, long length);
void mem_copy(void* dest, const void* src, long length);
void mem_copy_step(void* dest, const void* src, long step, long length);
void mem_copy_offset(void* dest, const void* src, long destOffset, long srcOffset, long length);
void mem_copy_offset_step(void* dest, const void* src, long destOffset, long srcOffset, long step, long length);
void mem_copy_step_offset(void* dest, const void* src, long destOffset, long srcOffset, long step, long stepOffset, long length);

void mem_set(void* dest, int value, long length)
{
	char* cdest = (char*)dest;
	for (long i = 0; i < length; i++)
	{
		cdest[i] = value;
	}
}

void mem_copy(void* dest, const void* src, long length)
{
	char* cdest = (char*)dest;
	const char* csrc = (const char*)src;
	for (long i = 0; i < length; i++)
	{
		*cdest = *csrc;
		cdest++;
		csrc++;
	}
}

void mem_copy_step(void* dest, const void* src, long step, long length)
{
	char* cdest = (char*)dest;
	const char* csrc = (const char*)src;
	for (long i = 0; i < length; i++)
	{
		*cdest = *csrc;
		cdest+=step;
		csrc+=step;
	}
}

void mem_copy_offset(void* dest, const void* src, long destOffset, long srcOffset, long length)
{
	char* cdest = (char*)dest;
	const char* csrc = (const char*)src;
	cdest += destOffset;
	csrc += srcOffset;
	for (long i = 0; i < length; i++)
	{
		*cdest = *csrc;
		cdest++;
		csrc++;
	}
}
void mem_copy_offset_step(void* dest, const void* src, long destOffset, long srcOffset, long step, long length)
{
	char* cdest = (char*)dest;
	const char* csrc = (const char*)src;
	cdest += destOffset;
	csrc += srcOffset;
	for (long i = 0; i < length; i+=step)
	{
		*cdest = *csrc;
		cdest++;
		csrc++;
	}
}

void mem_copy_step_offset(void* dest, const void* src, long destOffset, long srcOffset, long step, long stepOffset, long length)
{
	char* cdest = (char*)dest;
	const char* csrc = (const char*)src;
	cdest += destOffset;
	csrc += srcOffset;
	for (long i = stepOffset; i < length; i+=step)
	{
		*cdest = *csrc;
		cdest++;
		csrc++;
	}
}

#endif
