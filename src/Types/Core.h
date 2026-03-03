#pragma once
#include <bitset>
#include <stdint.h>
#include <glm/glm.hpp>
#include <vector>

const uint8_t MAX_COMPONENTS = 32;
const uint8_t Z_INDEX_LIMIT = 32;
const uint16_t MS_IN_SEC = 1000;

typedef std::bitset<MAX_COMPONENTS> Signature;

struct Tile
{
	glm::u16vec2 position{ 0, 0 };
	glm::u16vec2 source{ 0, 0 };

	static glm::u16vec2 size;
	static float scale;
};

struct Map
{
	std::vector<Tile> tiles;
	glm::u16vec2 size;
};

struct CollisionBox
{
	glm::vec2 min{ 0.0f };
	glm::vec2 max{ 0.0f };
};