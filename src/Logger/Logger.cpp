#include "Logger.h"
#include <Utils/Utils.h>
#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <unordered_map>


std::vector<LogEntry> Logger::messages;
bool Logger::isEnabled = true;

const std::unordered_map <LogType, std::string> logTypeToString
{
	{ LogType::Info, "LOG::" },
	{ LogType::Warning, "WARNING::" },
	{ LogType::Error, "ERROR::" },
};

const std::unordered_map <LogType, std::string> logTypeToColor
{
	{ LogType::Info, "\033[32m" },
	{ LogType::Warning, "\033[33m" },
	{ LogType::Error, "\033[31m" },
};


void Logger::AddLogEntry( const std::string& message, LogType logType )
{
	if ( !isEnabled )
	{
		return;
	}

	const LogEntry& logEntry = messages.emplace_back(
		logType,
		std::string( "[" + Utils::GetCurrentDateTimeString() + "]::" + logTypeToString.at( logType ) + message )
	);

	std::cout << logTypeToColor.at( logType ) << logEntry.message << "\033[0m" << std::endl;
}

void Logger::Log( const std::string& message )
{
	AddLogEntry( message, LogType::Info );
}

void Logger::Warning( const std::string& message )
{
	AddLogEntry( message, LogType::Warning );
}

void Logger::Error( const std::string& message )
{
	AddLogEntry( message, LogType::Error );
}

void Logger::SetLoggerEnabled( bool isEnabled )
{
	Logger::isEnabled = isEnabled;
	Warning( "LOGGER::ENABLED:" + std::to_string( isEnabled ) );
}
