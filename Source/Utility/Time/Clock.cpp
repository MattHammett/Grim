#include "../../../Include/Utility/Time/Clock.h"
using namespace Grim;

void Clock::initialize()
{
	QueryPerformanceFrequency(&m_LargeInt);
	m_Frequency = static_cast<float32>(m_LargeInt.QuadPart);
	QueryPerformanceCounter(&m_LargeInt);
	m_CounterStart = static_cast<float32>(m_LargeInt.QuadPart);
}

void Clock::terminate()
{
}

float32 Clock::getElapsedTimeSeconds()
{
	QueryPerformanceCounter(&m_LargeInt);
	return static_cast<float32>((m_LargeInt.QuadPart - m_CounterStart) / m_Frequency);
}