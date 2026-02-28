#pragma once
#include <bitset>
#include <stdint.h>
#include <glm/glm.hpp>

const uint8_t MAX_COMPONENTS = 32;
const uint8_t Z_INDEX_LIMIT = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

struct Tile
{
	glm::u16vec2 position{ 0, 0 };
	glm::u8vec2 source{ 0, 0 };

	static glm::u8vec2 size;
	static float scale;
};