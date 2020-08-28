#include <windows.h>
#include <psapi.h>

#include "types.h"

static uint64 x(uint64 start, uint64 length, const unsigned char *pattern, const char *mask)
{
	uint64 pos = 0;
	uint64 mask_length = strlen(mask) - 1;
	uint64 h = -1;
	uint64 start_addr = 0;
	uint64 i = 0;

	start_addr = start;

	for(i = start_addr; i < start_addr + length; ++i)
	{
		if(*(unsigned char *)i == pattern[pos] || mask[pos] == '?')
		{
			if(mask[pos + 1] == '\0')
			{
				h = i - mask_length;
				break;
			}

			pos++;

			continue;
		}

		pos = 0;
	}

	return h;
}

uint64 find_pattern(HMODULE module, const unsigned char *pattern, const char *mask)
{
	MODULEINFO info;

	ZeroMemory(&info, sizeof(MODULEINFO));

	GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(MODULEINFO));

	return x((uint64)module, info.SizeOfImage, pattern, mask);
}