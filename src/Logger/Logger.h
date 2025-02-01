#pragma once

#include <vector>
#include <string>

enum class LogType
{
	Info,
	Warning,
	Error
};

struct LogEntry
{
	LogType type;
	std::string message;
};

class Logger
{
private:
	static std::vector<LogEntry> messages;
	static const LogEntry& AddLogEntry( const std::string& message, LogType logType );

public:
	static void Log( const std::string& message );
	static void Warning( const std::string& message );
	static void Error( const std::string& message );
};