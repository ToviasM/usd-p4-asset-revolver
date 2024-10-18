#include "perforce_user.h"


void ResolveUser::OutputText(const char* data, int length)
{
	std::string value(data);
	ResolveUser::output = value;
}
int ResolveUser::OutputInfo(char level, char* data)
{
	std::string value(data);
	ResolveUser::output = value;
	return level;
}