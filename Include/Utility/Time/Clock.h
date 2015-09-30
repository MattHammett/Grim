#ifndef CLOCK_H
#define CLOCK_H

#include "..\Singleton.h"

namespace Grim
{
	class Singletons;

	class Clock : public Singleton<Clock>
	{
		GRIM_SINGLETON
	public:
		int test();
	protected:
		void initialize() override;
		void terminate() override;
	};
}

#endif