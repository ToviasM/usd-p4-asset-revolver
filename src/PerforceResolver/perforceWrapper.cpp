#include "perforceWrapper.h"
#include "common.h"
#include <cstring>


PXR_NAMESPACE_OPEN_SCOPE

USDUser PerforceClient::ui;
ClientApi PerforceClient::client;

PerforceClient::PerforceClient()
{
	int client_status = PerforceClient::initialize_client();

	if (client_status != 1)
	{
		Error e;
		PerforceClient::client.Init(&e);
		PerforceClient::test_error(e);
		TF_DEBUG(PERFORCE_CLIENT, "Error creating client!\n");
	}

	TF_DEBUG(PERFORCE_CLIENT, "Initialized Client!\n");

}

PerforceClient::~PerforceClient()
{
	Error e;
	PerforceClient::client.Final(&e);
	PerforceClient::test_error(e);
	P4Libraries::Shutdown(P4LIBRARIES_INIT_ALL, &e);
	PerforceClient::test_error(e);
}

int PerforceClient::initialize_client()
{
	StrBuf msg;
	Error e;
	P4Libraries::Initialize(P4LIBRARIES_INIT_ALL, &e);

	PerforceClient::test_error(e);
	PerforceClient::client.Init(&e);
	PerforceClient::test_error(e);
	return 1;
}

int PerforceClient::test_error(Error e)
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

void PerforceClient::sync_file(const std::string& path)
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

std::string PerforceClient::get_absolute_path(const std::string& path)
{
	char* modifiablePath = new char[path.size() + 1];
	strcpy_s(modifiablePath, path.size() + 1, path.c_str());

	// Create an array of char* for SetArgv
	char* args[] = { modifiablePath };
	PerforceClient::client.SetArgv(1, args);
	PerforceClient::client.Run("where", &PerforceClient::ui);
	delete[] modifiablePath;

	return PerforceClient::get_path_from_drive("D:\\", PerforceClient::ui.GetTextOutput());
}

std::string PerforceClient::get_path_from_drive(std::string drive, std::string path)
{
	std::string modifiedPath;

	size_t pos = path.find(drive);
	TF_DEBUG(PERFORCE_CLIENT, "Getting new path!\n");
	if (pos != std::string::npos) {
		return path.substr(pos);
	}
	TF_DEBUG(PERFORCE_CLIENT, "Failed To Get Path!\n");
	return std::string();
}

PXR_NAMESPACE_CLOSE_SCOPE
