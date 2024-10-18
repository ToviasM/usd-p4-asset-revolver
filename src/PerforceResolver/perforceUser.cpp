#include "perforceUser.h"


void USDUser::OutputText(const char* data, int length)
{
	std::string value(data);
	USDUser::output = value;
}
int USDUser::OutputInfo(char level, char* data)
{
	std::string value(data);
	USDUser::output = value;
	return level;
}