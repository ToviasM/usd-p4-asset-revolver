#include "perforceWrapper.h"
#include "common.h"
#include <cstring>


PXR_NAMESPACE_OPEN_SCOPE

USDUser PerforceClient::ui;
ClientApi PerforceClient::client;

PerforceClient::PerforceClient()
{
	int client_status = PerforceClient::InitializeClient();

	if (client_status != 1)
	{
		Error e;
		PerforceClient::client.Init(&e);
		PerforceClient::_TestError(e);
		TF_DEBUG(PERFORCE_CLIENT, "Error creating client!\n");
	}

	TF_DEBUG(PERFORCE_CLIENT, "Initialized Client!\n");

}

PerforceClient::~PerforceClient()
{
	Error e;
	PerforceClient::client.Final(&e);
	PerforceClient::_TestError(e);
	P4Libraries::Shutdown(P4LIBRARIES_INIT_ALL, &e);
	PerforceClient::_TestError(e);
}

int PerforceClient::InitializeClient()
{
	StrBuf msg;
	Error e;
	P4Libraries::Initialize(P4LIBRARIES_INIT_ALL, &e);

	PerforceClient::_TestError(e);
	PerforceClient::client.Init(&e);
	PerforceClient::_TestError(e);
	return 1;
}

int PerforceClient::_TestError(Error e)
{
	StrBuf msg;
	if (e.Test())
	{
		e.Fmt(&msg);
		TF_DEBUG(PERFORCE_CLIENT, "%s\n", msg.Text());
		return 1;
	}
	return 0;
}

void PerforceClient::SyncFile(const std::string& path)
{
	TF_DEBUG(PERFORCE_CLIENT, "Syncing!\n");
	char* modifiablePath = new char[path.size() + 1];
	strcpy_s(modifiablePath, path.size() + 1, path.c_str());

	// Create an array of char* for SetArgv
	char* args[] = { modifiablePath };
	PerforceClient::client.SetArgv(1, args);

	PerforceClient::client.Run("sync", &PerforceClient::ui);

	TF_DEBUG(PERFORCE_CLIENT, "Synced!\n");
	delete[] modifiablePath;
}

std::string PerforceClient::GetAbsolutePath(const std::string& path)
{
	char* modifiablePath = new char[path.size() + 1];
	strcpy_s(modifiablePath, path.size() + 1, path.c_str());

	// Create an array of char* for SetArgv
	char* args[] = { modifiablePath };
	PerforceClient::client.SetArgv(1, args);
	PerforceClient::client.Run("where", &PerforceClient::ui);
	delete[] modifiablePath;

	return PerforceClient::GetPathFromDrive(PerforceClient::ui.GetTextOutput());
}

std::string PerforceClient::GetPathFromDrive(std::string path)
{
	size_t pos = path.find(":\\");
	TF_DEBUG(PERFORCE_CLIENT, "Getting new path!\n");

	if (pos != std::string::npos && pos > 0) { // Ensure that pos - 1 is valid
		// Subtract 1 from pos to include the drive letter
		return path.substr(pos - 1);
	}

	TF_DEBUG(PERFORCE_CLIENT, "Failed To Get Path!\n");
	return std::string();
}

PXR_NAMESPACE_CLOSE_SCOPE
