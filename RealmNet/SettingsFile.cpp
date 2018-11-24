#include "stdafx.h"

#include "SettingsFile.h"

Settings SettingsFile::settings;

Settings::Settings()
{
	std::fstream bin("settings.bin", std::ios::in | std::ios::binary);
	if (!bin.good())
	{
		//no settings file -> default settings
		defaultHost = "52.59.198.155"; //eun2
	}
	else
	{
		int temp;
		bin.read((char*)&temp, 4);
		defaultHost = new char[temp];
		bin.read((char*)defaultHost, temp); //* sizeof(char)
	}
}

void Settings::save()
{
	std::fstream bin("settings.bin", std::ios::out | std::ios::binary);

	int temp = strlen(defaultHost) + 1;
	bin.write((char*)&temp, 4);
	bin.write(defaultHost, temp);

	bin.close();
}