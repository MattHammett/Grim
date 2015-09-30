#include "../../Include/Debug/Log.h"
#include "../../Include/Utility/Singletons.h"
#include <iostream>
using namespace Grim;

void Log::initialize()
{
	m_DefaultLevel = Log::Level::Info;

	m_TimeDate = std::chrono::system_clock::now();
	m_TimeDate_t = std::chrono::system_clock::to_time_t(m_TimeDate);
	localtime_s(&m_LocalTimeDate, &m_TimeDate_t);

	m_File.open(Singletons::strings.find("LOG_FILE_PATH"));
}

void Log::terminate()
{
	m_File.close();
}

void Log::flush()
{
	if (m_File.is_open())
	{
		m_File.flush();
	}
}

void Log::setDefaultLevel(Log::Level level)
{
	m_DefaultLevel = level;
}
