#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#include "api_hook.h"
#include "mem.h"
#include "mmap.h"

static void write_protected_mem(uint64_t src, uint64_t buf, size_t size)
{
	ULONG old = 0;

	virtual_protect((uint64_t)src, size, PAGE_EXECUTE_READWRITE, &old);

	write_memory((uint64_t)src, (uint64_t)buf, size);

	virtual_protect((uint64_t)src, size, old, &old);

	return;
}

void *copy_func(void *src)
{
    int i = 0;
    int pos = 0;
    mem *m;

    if((m = (mem *)malloc(sizeof(mem))) == NULL)
    {
        return NULL;
    }

    for(i = 0; i < (MAX_BUF_SIZE + 14); i++)
    {
        BYTE tmp = 0;

		tmp = read_memory<BYTE>((uint64_t)src + i);

        if(tmp == 0xC3 || tmp == 0xCC) // Copy until we reach the functions return or a breakpoint.
        {
            break;
        }

        m->buf[pos] = tmp;
        pos++;
    }

    for(i = 0; i < 7; i++) // Append another 7 breakpoints
    {
        m->buf[pos] = 0xCC;
        pos++;
    }

    m->size = pos;

    return m;
}

void hook_func(void *src, void *dest)
{
    int i = 0;

	uint8_t buf[14] =
	{
		0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

    memcpy(&buf[6], &dest, sizeof(uint64_t));

    write_memory((uint64_t)src, (uint64_t)buf, sizeof(buf));

    return;
}

void restore_func(void *func, void *copy)
{
    DWORD old = 0;
    mem *m;

    m = (mem *)copy;
    
	virtual_protect((uint64_t)func, m->size, PAGE_READWRITE, &old);

    write_memory((uint64_t)func, (uint64_t)m->buf, m->size);

    virtual_protect((uint64_t)func, m->size, old, &old); // Restore the protection

    return;
}