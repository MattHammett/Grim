#ifndef TYPE_H
#define TYPE_H

#include <cstdint>
#include <SFML\System\Vector2.hpp>
#include <SFML\System\Vector3.hpp>
#include <SFML\Graphics\Transform.hpp>

namespace Grim
{
	using float32 = float;
	using float64 = double;
	using int8 = std::int8_t;
	using uint8 = std::uint8_t;
	using int32 = std::int32_t;
	using uint32 = std::uint32_t;
	using int64 = std::int64_t;
	using uint64 = std::uint64_t;
	using Vector2f = sf::Vector2f;
	using Vector2i = sf::Vector2i;
	using Vector2u = sf::Vector2u;
	using Vector3f = sf::Vector3f;
	using Vector3i = sf::Vector3i;
}

#endif
