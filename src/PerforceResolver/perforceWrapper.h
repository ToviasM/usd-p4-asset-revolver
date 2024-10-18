#pragma once
#include <string>
#include "common.h"
#include "perforceUser.h"
#include "debugCodes.h"

PXR_NAMESPACE_OPEN_SCOPE

class PerforceClient
{
public:
	static USDUser ui;
	static ClientApi client;


	PerforceClient();
	~PerforceClient();

	int initialize_client();

	int test_error(Error e);

	void sync_file(const std::string& path);

	std::string get_absolute_path(const std::string& path);
	std::string get_path_from_drive(std::string drive, std::string path);

};

PXR_NAMESPACE_CLOSE_SCOPE
