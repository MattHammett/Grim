#ifndef LOG_H
#define LOG_H

#include "Singleton.h"

namespace Grim
{
	class Log : public Singleton<Log>
	{
		friend class Singleton<Log>;
	public:
		void initialize() override;
		void terminate() override;
	};
}

#endif