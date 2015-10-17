#ifndef CLOCK_H
#define CLOCK_H

#define WIN32_LEAN_AND_MEAN

#include "..\Singleton.h"
#include "..\Type.h"
#include <Windows.h>

namespace Grim
{
	class Singletons;

	class Clock : public Singleton<Clock>
	{
		GRIM_SINGLETON
	public:
		float32 getElapsedTimeSeconds();
	protected:
		void initialize() override;
		void terminate() override;
	private:
		LARGE_INTEGER m_LargeInt;
		float64 m_Frequency;
		uint64 m_CounterStart;
	};
}

#endif