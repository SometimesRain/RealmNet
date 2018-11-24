#include "stdafx.h"

#include "Downloader.h"

void Downloader::download(const char* url, const char* path, const char* filename)
{
	HINTERNET hIntSession = InternetOpenA("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	HINTERNET hHttpSession = InternetConnectA(hIntSession, url, 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
	HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", path, 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	const char* szHeaders = "Content-Type: */*\n";
	CHAR szReq[1024] = "";
	if (!HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq)))
	{
		DWORD dwErr = GetLastError();
		printf("Error %d\n", dwErr);
	}

	CHAR* szBuffer = new char[1024 * 1024 * 8]; //8 MB
	DWORD dwRead = 0;
	DWORD totalRead = 0;
	while (InternetReadFile(hHttpRequest, szBuffer+totalRead, 1024 * 1024 * 8 - totalRead, &dwRead) && dwRead)
	{
		szBuffer[dwRead] = 0;
		totalRead += dwRead;
	}

	InternetCloseHandle(hHttpRequest);
	InternetCloseHandle(hHttpSession);
	InternetCloseHandle(hIntSession);

	std::fstream bin(filename, std::ios::out | std::ios::binary);
	bin.write(szBuffer, totalRead);
	bin.close();

	printf("Downloaded %s\n", filename);
}