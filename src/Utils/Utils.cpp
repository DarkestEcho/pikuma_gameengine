#include "Utils.h"
#include <Logger/Logger.h>
#include <glm/glm.hpp>
#include <chrono>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iostream>

std::string Utils::GetCurrentDateTimeString()
{
	auto timeNow = std::chrono::system_clock::now(); // std::chrono::system_clock::time_point
	auto time = std::chrono::floor<std::chrono::seconds>( timeNow );

	std::string dateTime = std::format( "{:%Y-%m-%d %H:%M:%S}", time );
	return dateTime;
}

Map Utils::LoadMapFromFile( std::string_view filePath )
{
	std::ifstream mapFile( filePath.data() );
	if ( !mapFile.is_open() )
	{
		Logger::Error( "MAP::LOADING::FILE_ERROR:" + std::string( filePath ) );
		throw std::invalid_argument( filePath.data() );
	}

	std::string line;

	std::getline( mapFile, line );

	std::stringstream ss( line );

	//FIXME - Need some validation for map file before any actions

	//---> Fill basic Tile info
	ss >> Tile::size.x;
	ss.ignore();
	ss >> Tile::size.y;
	ss.ignore();
	ss >> Tile::scale;

	Logger::Log( "TILE_INFO::width: " + std::to_string( Tile::size.x ) +
		", height: " + std::to_string( Tile::size.y ) +
		", scale: " + std::to_string( Tile::scale ) );

	std::vector<Tile> tiles;
	glm::u16vec2 size;

	uint16_t y = 0u;
	uint16_t x = 0u;

	while ( std::getline( mapFile, line ) )
	{
		//TODO - Output values
		ss.str( line );
		ss.clear();
		x = 0u;

		std::string cell;
		while ( std::getline( ss, cell, ',' ) )
		{
			tiles.emplace_back(
				glm::u16vec2( static_cast<uint16_t>( x * Tile::size.x * Tile::scale ), static_cast<uint16_t>( y * Tile::size.y * Tile::scale ) ),
				glm::u16vec2( static_cast<uint16_t>( cell[1] - '0' ), static_cast<uint16_t>( cell[0] - '0' ) )
			);
			x++;
		}
		y++;
	}
	mapFile.close();

	size.x = x * Tile::size.x * Tile::scale;
	size.y = y * Tile::size.y * Tile::scale;


	return { tiles, size };
}

void Utils::CheckIsZIndexCorrect( uint8_t zIndex )
{
	if ( zIndex >= Z_INDEX_LIMIT )
	{
		std::string message{
			"Z-Index: " + std::to_string( zIndex ) +
			" bigger than max Z-Index: " + std::to_string( Z_INDEX_LIMIT - 1u )
		};

		Logger::Error( "UTILS::" + message );
		throw std::out_of_range( message );
	}
}


bool Utils::CheckAABBCollision( CollisionBox aBox, CollisionBox bBox )
{
	// Just for fun
	glm::bvec2 res = ( glm::lessThan( aBox.min, bBox.max ) & glm::lessThan( bBox.min, aBox.max ) );
	return res.x & res.y;
}
