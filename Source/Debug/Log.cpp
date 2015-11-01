#include "Log.h"
#include "../Utility/Singletons.h"
#include "../Utility/File.h"
#include "../Debug/Error.h"
#include "../Setup.h"
#include <iostream>
#include <sstream>
using namespace Grim;

void Log::initialize()
{
	m_DefaultLevel = Log::Level::Info;
	m_bShouldPrintToFile = true;
	m_bShouldPrintToConsole = true;
	m_LastTime = 0.0f;
	m_bShouldPrintVerbose = false;

	m_TimeDate = std::chrono::system_clock::now();
	m_TimeDate_t = std::chrono::system_clock::to_time_t(m_TimeDate);
	localtime_s(&m_LocalTimeDate, &m_TimeDate_t);

	openLogFile();
	print(Level::Info, Singletons::resources.findString("ENGINE_INITIALIZING"));

	flushPrintPreInitializeQueue();
	print(Level::Verbose, Singletons::resources.findString("LOG_INITIALIZED"));
}

void Log::print(const std::string & output)
{
	print(m_DefaultLevel, output);
}

void Log::print(Log::Level level, const std::string& output)
{
	if (!m_bShouldPrintToFile && !m_bShouldPrintToConsole)
	{
		return;
	}
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
			if (m_bShouldPrintToFile)
			{
				m_File		<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_DEBUG")	<< ": "	<< output << '\n';
			}								    
			if (m_bShouldPrintToConsole)
			{								    
				std::cout	<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_DEBUG")	<< ": "	<< output << '\n';
			}								    
			break;							    
		case Grim::Log::Fatal:
			if (m_bShouldPrintToFile)
			{								    
				m_File		<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_FATAL")	<< ": "	<< output << '\n';
			}								    
			if (m_bShouldPrintToConsole)
			{								    
				std::cout	<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_FATAL")	<< ": "	<< output << '\n';
			}								    
			break;							    
		case Grim::Log::Error:
			if (m_bShouldPrintToFile)
			{								    
				m_File		<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_ERROR")	<< ": "	<< output << '\n';
			}								    
			if (m_bShouldPrintToConsole)
			{								    
				std::cout	<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_ERROR")	<< ": "	<< output << '\n';
			}								    
			break;							    
		case Grim::Log::Warning:
			if (m_bShouldPrintToFile)
			{								    
				m_File		<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_WARNING") << ": " << output << '\n';
			}								    
			if (m_bShouldPrintToConsole)
			{								    
				std::cout	<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_WARNING") << ": " << output << '\n';
			}								    
			break;							    
		case Grim::Log::Info:
			if (m_bShouldPrintToFile)
			{								    
				m_File		<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_INFO")	<< ": "	<< output << '\n';
			}								    
			if (m_bShouldPrintToConsole)
			{								    
				std::cout	<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_INFO")	<< ": "	<< output << '\n';
			}								    
			break;							    
		case Grim::Log::sf:
			if (output.size() == 0) break;	    
			if (m_bShouldPrintToFile)
			{								    
				m_File		<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_SFML")			<< output << '\n';
			}								    
			if (m_bShouldPrintToConsole)
			{								    
				std::cout	<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_SFML")			<< output << '\n';
			}								    
			break;
		case Grim::Log::Lua:
			if (m_bShouldPrintToFile)
			{
				m_File		<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_LUA")		<< ": " << output << '\n';
			}
			if (m_bShouldPrintToConsole)
			{
				std::cout	<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_LUA")		<< ": " << output << '\n';
			}
			break;
		case Grim::Log::Verbose:
			if (!m_bShouldPrintVerbose)
			{
				break;
			}
			if (m_bShouldPrintToFile)
			{								    
				m_File		<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_VERBOSE")	<< ": " << output << '\n';
			}								    
			if (m_bShouldPrintToConsole)
			{								    
				std::cout	<< '[' + time + ']' << " " << Singletons::resources.findString("LOG_LEVEL_VERBOSE")	<< ": " << output << '\n';
			}
			break;
		default:
			print(Log::Error, Singletons::resources.findString("LOG_ERROR_INVALID_LEVEL"));
			break;
		}
	}
	Log::flush();
}

void Log::terminate()
{
	assert(m_File.is_open());
	print(Level::Verbose, "Log singleton terminated!");
	if (m_File.is_open())
	{
		m_File.close();
	}
}

void Log::openLogFile()
{
	bool bFound = false;
	std::size_t i = 0;
	while(!bFound)
	{
		if (!File::doesFileExist(Singletons::resources.findString("LOG_FILE_PATH") + std::to_string(i) + ".txt"))
		{
			bFound = true;
		}
		else
		{
			++i;
		}
	}
	assert(!m_File.is_open());

	m_File.open(Singletons::resources.findString("LOG_FILE_PATH") + std::to_string(i) + ".txt", std::ios::out | std::ios::in | std::ios::app);

	if (m_File.is_open())
	{
		appendLogHeader();
		flush();
	}
}

void Log::appendLogHeader()
{
	assert(m_File.is_open());

	if (m_bShouldPrintToFile)
	{
		m_File		<< Singletons::resources.findString("ENGINE_WINDOW_TITLE") << " " << Singletons::resources.findString("ENGINE_VERSION_NUMBER") << "\n\n";
	}
	if (m_bShouldPrintToConsole)
	{
		std::cout	<< Singletons::resources.findString("ENGINE_WINDOW_TITLE") << " " << Singletons::resources.findString("ENGINE_VERSION_NUMBER") << "\n\n";
	}
	if (m_bShouldPrintToConsole && !m_bShouldPrintToFile)
	{
		m_File		<< Singletons::resources.findString("LOG_TO_FILE_SET");
	}
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

void Log::flushPrintPreInitializeQueue()
{
	std::size_t size(m_PreInitializeQueueLevel.size());
	for (std::size_t i = 0; i < size; ++i)
	{
		print(m_PreInitializeQueueLevel.front(), Singletons::resources.findString(m_PreInitializeQueueString.front()));
		m_PreInitializeQueueLevel.pop();
		m_PreInitializeQueueString.pop();
	}
}

void Log::setDefaultLevel(Log::Level level)
{
	m_DefaultLevel = level;
}

void Log::preInitializePrint(Log::Level level, const std::string& output)
{
	assert(level > -1);
	assert(output.size() > 0);
	m_PreInitializeQueueLevel.emplace(level);
	m_PreInitializeQueueString.emplace(output);
}