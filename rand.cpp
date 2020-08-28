#include <string>

#include "xor.h"

//static const char alpha[32] = "it0j7f14cepomdlgbn39a58sukrhq26";

// Simple function to generate a random string for us
std::string rand_str(int len)
{
	int h = len;
	std::string str;
	uint8_t *alpha;

	// it0j7f14cepomdlgbn39a58sukrhq26
	alpha = _unxor((uint8_t *)"\x4b\x56\x12\x48\x15\x44\x13\x16\x41\x47\x52\x4d\x4f\x46\x4e\x45\x40\x4c\x11\x1b\x43\x17\x1a\x51\x57\x49\x50\x4a\x53\x10\x14", 31);

	while(h-- > 0)
	{
		char tmp;

		tmp = alpha[rand() % 31];

		str += tmp;
	}
	
	free(alpha);

	return str;
}