#include "../../../Include/Utility/Math/Random.h"
#include "../../../Include/Setup.h"
using namespace Grim;

std::mt19937 Random::m_Engine;
std::random_device Random::m_RandomDevice;

void Random::seed(uint32 seed)
{
	if (seed == 0)
	{
		m_Engine.seed(m_RandomDevice());
	}
	else
	{
		m_Engine.seed(seed);
	}
}

int32 Random::between(int32 min, int32 max)
{
	// Consistent numbers generated for debugging
#ifdef GRIM_DEBUG
	assert(max > min);
	return std::move(static_cast<int32>(rand() % max + min));
#endif

	// Completely random numbers for release mode
#ifdef GRIM_RELEASE
	if (max > min)
	{
		std::uniform_int_distribution<int32> distribution(min, max);
		return std::move(static_cast<int32>(distribution(m_Engine)));
	}
	else
	{
		// TODO: Handle error
		return 0;
	}
#endif
}

float32 Random::between(float32 min, float32 max)
{
	// Consistent numbers generated for debugging
#ifdef GRIM_DEBUG
	assert(max > min);
	return std::move(static_cast<float32>(min + static_cast<float32>(rand()) / (static_cast<float32>(RAND_MAX / (max - min)))));
#endif

	// Completely random numbers for release mode
#ifdef GRIM_RELEASE
	if (max > min)
	{
		std::uniform_real_distribution<> distribution(min, max);
		return std::move(static_cast<float32>(distribution(m_Engine)));
	}
	else
	{
		// TODO: Handle error
		return 0.0f;
	}
#endif
}
