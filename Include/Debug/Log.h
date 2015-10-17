#ifndef LOG_H
#define LOG_H

#include <queue>
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
			sf,
			Lua,
			Verbose
		};
	public:
		void setDefaultLevel(Log::Level level);

		void preInitializePrint(Log::Level level, const std::string& output);

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
		void flushPrintPreInitializeQueue();
	private:
		std::fstream m_File;
		Log::Level m_DefaultLevel;
		bool m_ToFile;
		bool m_ToConsole;
		std::size_t m_MaxLogFileSize;
		std::size_t m_LogFlushThreshold; // Number of log entries to hold until we flush

		//Time
		std::chrono::time_point<std::chrono::system_clock> m_TimeDate;
		std::time_t m_TimeDate_t;
		std::tm m_LocalTimeDate;

		float32 m_LastTime;

		//Pre initialize queue for any thing that needs printing to log before its initialized
		std::queue<Log::Level> m_PreInitializeQueueLevel;
		std::queue<std::string> m_PreInitializeQueueString;
	};
}

#endif