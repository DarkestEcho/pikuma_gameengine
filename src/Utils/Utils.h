#pragma once

#include <Types/Core.h>

#include <string>
#include <vector>

class Utils
{
public:
	static std::string GetCurrentDateTimeString();
	static std::vector<Tile> GetTilesFromMapFile( std::string_view filePath );
};