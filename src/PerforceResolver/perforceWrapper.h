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

	int InitializeClient();

	int _TestError(Error e);

	void SyncFile(const std::string& path);

	std::string GetAbsolutePath(const std::string& path);
	std::string GetPathFromDrive(std::string path);

};

PXR_NAMESPACE_CLOSE_SCOPE
