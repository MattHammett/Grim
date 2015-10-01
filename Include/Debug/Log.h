#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <chrono>
#include <ctime>
#include "..\Utility\Singleton.h"
#include "../Utility/Type.h"

namespace Grim
{
	class Singletons;

	class Log : public Singleton<Log>
	{
		GRIM_SINGLETON
	public:
		enum Level
		{
			Debug,
			Fatal,
			Error,
			Warning,
			Info,
			Verbose
		};
	public:
		void setDefaultLevel(Log::Level level);

		void print(const std::string& output);
		void print(Log::Level level, const std::string& output);
	protected:
		void initialize() override;
		void terminate() override;
	private:
		void openLogFile();
		void appendLogHeader();
		void flush();
		const std::string formatDate();
		const std::string formatTime();
	private:
		std::fstream m_File;
		Log::Level m_DefaultLevel;
		bool m_ToCout;
		bool m_ToFile;
		std::size_t m_MaxLogFileSize;
		std::size_t m_LogFlushThreshold; // Number of log entries to hold until we flush

		//Time
		std::chrono::time_point<std::chrono::system_clock> m_TimeDate;
		std::time_t m_TimeDate_t;
		std::tm m_LocalTimeDate;
	};
}

#endif