#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t key = 0xDEADBEEF;

void _xor(uint8_t *data, int data_len)
{
	uint8_t k1 = key & 0xff;
	uint8_t k2 = (key >> 8) & 0xff;
	uint8_t k3 = (key >> 16) & 0xff;
	uint8_t k4 = (key >> 24) & 0xff;
	int i = 0;

	for(i = 0; i < data_len; i++)
	{
		data[i] ^= k1;
		data[i] ^= k2;
		data[i] ^= k3;
		data[i] ^= k4;
	}

	return;
}

uint8_t *_unxor(uint8_t *data, int data_len)
{
	uint8_t *buf;

	buf = (uint8_t *)malloc(data_len);
    if(!buf)
    {
        return NULL;
    }

    memcpy(buf, data, data_len);

	_xor(buf, data_len);

	return buf;
}