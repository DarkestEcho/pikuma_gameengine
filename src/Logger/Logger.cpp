#include "Logger.h"
#include <Utils/Utils.h>
#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <unordered_map>

std::vector<LogEntry> Logger::messages;

const std::unordered_map <LogType, std::string> logTypeToString{
	{LogType::Info, "LOG::"},
	{LogType::Warning, "WARNING::"},
	{LogType::Error, "ERROR::"},
};

const LogEntry& Logger::AddLogEntry( const std::string& message, LogType logType )
{
	return messages.emplace_back(
		logType,
		std::string( "[" + Utils::GetCurrentDateTimeString() + "]::" + logTypeToString.at( logType ) + message ) );
}

void Logger::Log( const std::string& message )
{
	const LogEntry& logEntry = AddLogEntry( message, LogType::Info );
	std::cout << "\033[32m" << logEntry.message << "\033[0m" << std::endl;
}

void Logger::Warning( const std::string& message )
{
	const LogEntry& logEntry = AddLogEntry( message, LogType::Warning );
	std::cout << "\033[33m" << logEntry.message << "\033[0m" << std::endl;
}

void Logger::Error( const std::string& message )
{
	const LogEntry& logEntry = AddLogEntry( message, LogType::Error );
	std::cout << "\033[31m" << logEntry.message << "\033[0m" << std::endl;
}
