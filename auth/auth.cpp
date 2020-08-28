#include "auth.h"
#include "XorCompileTime.hpp"


c_crypto crypto;

int auth::exiting_user(const std::string& id)
{

	c_lw_http lw_http;
	c_lw_httpd lw_http_d;

	const auto md5 = new md5wrapper();
	if (!lw_http.open_session())
	{
		std::cout << xorstr_("[ Sorry,  open_session FAILED. ]");
		exit(0);
	}
	std::string s_reply;

	lw_http_d.add_field(xorstr_("a"), md5->getHashFromString(hwid::get_hardware_id(id)).c_str());
	lw_http_d.add_field(xorstr_("b"), crypto.key.c_str());
	lw_http_d.add_field(xorstr_("c"), crypto.iv.c_str());
	lw_http_d.add_field(xorstr_("d"), id.c_str());
	lw_http_d.add_field(xorstr_("e"), xorstr_(""));
	const auto b_lw_http = lw_http.post(xorstr_(L"https://bypass.ac/auth/api/info"), s_reply, lw_http_d);

	lw_http.close_session();

	if (!b_lw_http)
	{
		std::cout << xorstr_("[ Sorry,  HTTP FAILED. ]");
		exit(0);
	}

	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "201"))
	{
		std::cout << xorstr_("[ Sorry, look wrong application id. ]");
		Sleep(2000); exit(0);
	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "202"))
	{
		std::cout << xorstr_("[ Application is paused cheat is update. ]");
		Sleep(2000); exit(0);
	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "203"))
	{
	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "100"))
	{
		std::cout << xorstr_("[ You enter wrong serial key. ]");
		Sleep(2000); exit(0);
	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "101"))
	{
		std::cout << xorstr_("[ Sorry, serial key already used by other. ]");
		Sleep(2000); exit(0);
	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "102"))
	{
		std::cout << xorstr_("[ Sorry, you enter invalid serial key. ]");
		Sleep(2000); exit(0);
	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "103"))
	{
		std::cout << xorstr_("[ Sorry, serial key has been expired. ]");
		Sleep(2000); exit(0);
	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "200"))
	{
		return TRUE;
	}
	std::cout << xorstr_("[Porco dio ]");
	Sleep(2000); exit(0);
}

int auth::set_license_key(const std::string& serial, const std::string id)
{
	c_lw_http lw_http;
	c_lw_httpd lw_http_d;
	const auto md5 = new md5wrapper();

	if (!lw_http.open_session())
	{
		std::cout << xorstr_("[ Sorry,  open_session FAILED. ]");
		exit(0);
	}
	std::string s_reply;
	lw_http_d.add_field(xorstr_("a"), md5->getHashFromString(hwid::get_hardware_id(id)).c_str());
	lw_http_d.add_field(xorstr_("b"), crypto.key.c_str());
	lw_http_d.add_field(xorstr_("c"), crypto.iv.c_str());
	lw_http_d.add_field(xorstr_("d"), id.c_str());
	lw_http_d.add_field(xorstr_("e"), serial.c_str());
	const auto b_lw_http = lw_http.post(xorstr_(L"https://bypass.ac/auth/api/action"), s_reply, lw_http_d);
	lw_http.close_session();

	if (!b_lw_http)
	{
		std::cout << xorstr_("[ Sorry,  HTTP FAILED. ]");
		exit(0);
	}

	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "201"))
	{
		std::cout << xorstr_("[ Sorry, look wrong application id. ]");
		Sleep(2000); exit(0);
	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "202"))
	{
		std::cout << xorstr_("[ Application is paused cheat is update. ]");
	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "203"))
	{
		std::cout << xorstr_("[ Sorry, Hardware id is invalid please reset it. ]");
		Sleep(2000); exit(0);

	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "100"))
	{
		std::cout << xorstr_("[ You enter wrong serial key. ]");
		Sleep(2000); exit(0);

	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "101"))
	{
		std::cout << xorstr_("[ Sorry, serial key already used by other. ]");
		Sleep(2000); exit(0);

	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "102"))
	{
		std::cout << xorstr_("[ Sorry, you enter invalid serial key. ]");
		Sleep(2000); exit(0);

	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "103"))
	{
		std::cout << xorstr_("[ Sorry, serial key has been expired. ]");
		Sleep(2000); exit(0);

	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), "104"))
	{
		std::cout << xorstr_("[ Sorry, user already unsed. ]");
		Sleep(2000); exit(0);

	}
	if (!strcmp(c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str(), ("200")))
	{
		std::cout << xorstr_("[ Registered successfully. ]");
		Sleep(2000); exit(0);

	}
	return FALSE;
	std::cout << xorstr_("[Porco dio ]");// AHHAHAHAHAH
	Sleep(2000); exit(0);
}
