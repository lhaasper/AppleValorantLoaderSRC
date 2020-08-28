#include "AutoUpdate.h"
#include <filesystem>
#include <iostream>
#include <mutex>

std::string version = "6";
std::string token;

std::string ExePath()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

void StartThem(LPCSTR name)
{
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcessA(name, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		return;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}


static const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()
{

	return alphanum[rand() % stringLength];
}

#define SELF_REMOVE_STRING  TEXT("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\"")

void DelMe()
{
	TCHAR szModuleName[MAX_PATH];
	TCHAR szCmd[2 * MAX_PATH];
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	GetModuleFileName(NULL, szModuleName, MAX_PATH);

	StringCbPrintf(szCmd, 2 * MAX_PATH, SELF_REMOVE_STRING, szModuleName);

	CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}
void show_progress_bar(int time, const std::string& message, char symbol)
{
	std::cout << "[>] Autoupdate Found new loader is getting downloaded ";
	Sleep(1000);
	std::string progress_bar;
	const double progress_level = 1.42;
	for (double percentage = 0; percentage <= 100; percentage += progress_level)
	{
		progress_bar.insert(0, 1, symbol);
		std::cout << "\r[" << std::ceil(percentage) << '%' << "] " << progress_bar;
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}
}
void CheckForUpdates()
{
	std::string fix;
	std::string encryptedversion = c_crypto::encrypt(version, crypto.key, crypto.iv);
	c_lw_http lw_http;
	c_lw_httpd lw_http_d;
	const auto md5 = new md5wrapper();

	if (!lw_http.open_session())
	{
		return;
	}
	std::string s_reply;
	lw_http_d.add_field("version", encryptedversion.c_str());
	lw_http_d.add_field("key", crypto.key.c_str());
	lw_http_d.add_field("iv", crypto.iv.c_str());;
	const auto b_lw_http = lw_http.post(L"https://bypass.ac/update.php", s_reply, lw_http_d);
	lw_http.close_session();

	if (!b_lw_http)
	{
		return;
	}
	std::string decrypt = c_crypto::decrypt(s_reply, crypto.key, crypto.iv).c_str();
	switch (std::stoi(decrypt))
	{
	case 300:
	{
		break;
	}
	case 10:
	{
		CHAR name[UNLEN + 1];
		DWORD size = UNLEN + 1;
		GetUserNameA((CHAR*)name, &size);

		std::string gay1 = ExePath();

		srand(time(0));
		std::string Str;
		for (unsigned int i = 0; i < 20; ++i)
		{
			Str += genRandom();

		}

		std::string gay2 = "\\" + Str + ".exe";



		std::string gay3 = gay1 + gay2;



		while (1)
		{
			show_progress_bar(100, "", '#');
			HRESULT hr;
			LPCSTR Url = "https://bypass.ac/valo.exe", File = gay3.c_str();
			hr = URLDownloadToFileA(0, Url, File, 0, 0);
			switch (hr)
			{
			case S_OK:
				break;
			case E_OUTOFMEMORY:
				break;
			case INET_E_DOWNLOAD_FAILURE:
				break;
			default:
				break;
			}

			Sleep(3000);
			StartThem(gay3.c_str());

			DelMe();
			exit(0);
		}
		break;

	}
	default:
	{
		MessageBoxA(0, "An unknown error has occured! Please try again later", "error", 0);
		exit(0);
		break;
	}
	}
}
