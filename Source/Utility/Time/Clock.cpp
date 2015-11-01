#include "Clock.h"
#include "../../Utility/Singletons.h"
using namespace Grim;

void Clock::initialize()
{
	QueryPerformanceFrequency(&m_LargeInt);
	m_Frequency = m_LargeInt.QuadPart;
	QueryPerformanceCounter(&m_LargeInt);
	m_CounterStart = m_LargeInt.QuadPart;

	Singletons::log.preInitializePrint(Log::Level::Verbose, "CLOCK_INITIALIZED");
}

void Clock::terminate()
{
	Singletons::log.print(Log::Level::Verbose, Singletons::resources.findString("CLOCK_TERMINATED"));
}

float32 Clock::getElapsedTimeSeconds()
{
	QueryPerformanceCounter(&m_LargeInt);
	return static_cast<float32>((m_LargeInt.QuadPart - m_CounterStart) / m_Frequency);
}