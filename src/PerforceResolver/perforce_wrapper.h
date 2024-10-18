#pragma once
#include <string>
#include "common.h"
#include "perforce_user.h"

class PerforceClient
{
public:
	static ResolveUser ui;
	static ClientApi client;


	PerforceClient();
	~PerforceClient();

	int initialize_client();

	int test_error(Error e);

	void sync_file(const std::string& path);

	std::string get_absolute_path(const std::string& path);
	std::string get_path_from_drive(std::string drive, std::string path);

};

extern "C" __declspec(dllexport) void* Test_Perforce();