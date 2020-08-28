#include <fstream>
#include <iostream>
#include "md5wrapper.h"
#include "md5.h"
#pragma warning (disable: 4267)

std::string md5wrapper::hashit(std::string text) const
{
	MD5_CTX ctx;

	md5->MD5Init(&ctx);
	md5->MD5Update(&ctx,
		(unsigned char*)text.c_str(),
		text.length());

	unsigned char buff[16] = "";
	md5->MD5Final((unsigned char*)buff, &ctx);

	return convToString(buff);
}

std::string md5wrapper::convToString(unsigned char* bytes)
{
	char asciihash[33];

	auto p = 0;
	for (int i = 0; i < 16; i++)
	{
		::sprintf(&asciihash[p], "%02x", bytes[i]);
		p += 2;
	}
	asciihash[32] = '\0';
	return std::string(asciihash);
}

md5wrapper::md5wrapper()
{
	md5 = new MD5();
}

md5wrapper::~md5wrapper()
{
	delete md5;
}

std::string md5wrapper::getHashFromString(std::string text) const
{
	return this->hashit(text);
}

std::string md5wrapper::getHashFromFile(std::string filename) const
{
	FILE* file;
	MD5_CTX context;

	int len;
	unsigned char buffer[1024], digest[16];

	if ((file = fopen(filename.c_str(), "rb")) == NULL)
	{
		return "-1";
	}

	md5->MD5Init(&context);

	while ((len = fread(buffer, 1, 1024, file)))
	{
		md5->MD5Update(&context, buffer, len);
	}

	md5->MD5Final(digest, &context);
	fclose(file);
	return convToString(digest);
}
