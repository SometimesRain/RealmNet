#pragma once

class Settings
{
public:
	const char* defaultHost;

	Settings();
	void save();

	//no copying
	Settings(const Settings&) = delete;
	void operator=(const Settings&) = delete;
};

namespace SettingsFile
{
	extern Settings settings;
}