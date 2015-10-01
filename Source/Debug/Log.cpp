#include "../../Include/Debug/Log.h"
#include "../../Include/Utility/Singletons.h"
#include "../../Include/Utility/File.h"
#include "../../Include/Debug/Error.h"
#include "../../Include/Setup.h"
#include <iostream>
#include <sstream>
using namespace Grim;

void Log::initialize()
{
	m_DefaultLevel = Log::Level::Info;

	m_TimeDate = std::chrono::system_clock::now();
	m_TimeDate_t = std::chrono::system_clock::to_time_t(m_TimeDate);
	localtime_s(&m_LocalTimeDate, &m_TimeDate_t);

	openLogFile();
}

void Log::print(const std::string & output)
{
	print(m_DefaultLevel, output);
}

void Log::print(Log::Level level, const std::string& output)
{
#ifndef GRIM_DEBUG
	if (level == Log::Level::Debug)
	{
		return;
	}
#endif

	assert(level >= 0);
	assert(level <= Log::Verbose);
	assert(m_File.is_open());

	if (m_File.is_open())
	{
		const std::string time(formatTime());

		switch (level)
		{
		case Grim::Log::Debug:
			m_File << '[' + time + ']' << " " << Singletons::strings.find("LOG_LEVEL_DEBUG")	<< ": " << output << '\n';
			break;
		case Grim::Log::Fatal:
			m_File << '[' + time + ']' << " " << Singletons::strings.find("LOG_LEVEL_FATAL")	<< ": " << output << '\n';
			break;
		case Grim::Log::Error:
			m_File << '[' + time + ']' << " " << Singletons::strings.find("LOG_LEVEL_ERROR")	<< ": " << output << '\n';
			break;
		case Grim::Log::Warning:
			m_File << '[' + time + ']' << " " << Singletons::strings.find("LOG_LEVEL_WARNING")	<< ": " << output << '\n';
			break;
		case Grim::Log::Info:
			m_File << '[' + time + ']' << " " << Singletons::strings.find("LOG_LEVEL_INFO")		<< ": " << output << '\n';
			break;
		case Grim::Log::Verbose:
			m_File << '[' + time + ']' << " " << Singletons::strings.find("LOG_LEVEL_VERBOSE")	<< ": " << output << '\n';
			break;
		default:
			print(Log::Error, Singletons::strings.find("LOG_ERROR_INVALID_LEVEL"));
			break;
		}
	}
}

void Log::terminate()
{
	assert(m_File.is_open());
	if (m_File.is_open())
	{
		m_File.close();
	}
}

void Log::openLogFile()
{
	bool found = false;
	std::size_t i = 0;
	while(!found)
	{
		if (!File::checkFileExists(Singletons::strings.find("LOG_FILE_PATH") + std::to_string(i) + ".txt"))
		{
			found = true;
		}
		else
		{
			++i;
		}
	}
	assert(!m_File.is_open());
	m_File.open(Singletons::strings.find("LOG_FILE_PATH") + std::to_string(i) + ".txt", std::ios::out | std::ios::in | std::ios::app);

	if (m_File.is_open())
	{
		appendLogHeader();
		flush();
	}
}

void Log::appendLogHeader()
{
	assert(m_File.is_open());

	m_File << Singletons::strings.find("ENGINE_WINDOW_TITLE") << " " << Singletons::strings.find("ENGINE_VERSION_NUMBER") << "\n\n";
}

void Log::flush()
{
	assert(m_File.is_open());
	if (m_File.is_open())
	{
		m_File.flush();
	}
}

const std::string Log::formatDate()
{
	std::stringstream output;
	m_TimeDate = std::chrono::system_clock::now();
	m_TimeDate_t = std::chrono::system_clock::to_time_t(m_TimeDate);
	localtime_s(&m_LocalTimeDate, &m_TimeDate_t);

	if (m_LocalTimeDate.tm_mday < 10)
	{
		output << "0";
	}
	output << m_LocalTimeDate.tm_mday << "/";

	if (m_LocalTimeDate.tm_mon < 10)
	{
		output << "0";
	}
	output << m_LocalTimeDate.tm_mon << "/";
	output << m_LocalTimeDate.tm_year - 100;

	return output.str();
}

const std::string Log::formatTime()
{
	std::stringstream output;
	m_TimeDate = std::chrono::system_clock::now();
	m_TimeDate_t = std::chrono::system_clock::to_time_t(m_TimeDate);
	localtime_s(&m_LocalTimeDate, &m_TimeDate_t);

	if (m_LocalTimeDate.tm_hour < 10)
	{
		output << "0";
	}
	output << m_LocalTimeDate.tm_hour << ":";

	if (m_LocalTimeDate.tm_min < 10)
	{
		output << "0";
	}
	output << m_LocalTimeDate.tm_min << ":";

	if (m_LocalTimeDate.tm_sec < 10)
	{
		output << "0";
	}
	output << m_LocalTimeDate.tm_sec;

	return output.str();
}

void Log::setDefaultLevel(Log::Level level)
{
	m_DefaultLevel = level;
}