#include "Utils.h"
#include <chrono>

std::string Utils::GetCurrentDateTimeString()
{
	auto timeNow = std::chrono::system_clock::now(); // std::chrono::system_clock::time_point
	auto time = std::chrono::floor<std::chrono::seconds>( timeNow );

	std::string dateTime = std::format( "{:%Y-%m-%d %H:%M:%S}", time );
	return dateTime;
}