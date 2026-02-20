#include "AssetStore.h"
#include <Logger/Logger.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

AssetStore::AssetStore()
{
	Logger::Log( "AssetStore constructor called!" );
}

AssetStore::~AssetStore()
{
	ClearAssets();
	Logger::Log( "AssetStore destructor called!" );
}

void AssetStore::ClearAssets()
{
	ClearTextures();
}

void AssetStore::ClearTextures()
{
	if ( textures.size() == 0 )
	{
		return;
	}

	for ( auto& [_, texture] : textures )
	{
		SDL_DestroyTexture( texture );
	}

	size_t count = textures.size();
	textures.clear();
	Logger::Log( "ASSET_STORE::CLEARED::TEXTURES " + std::to_string( count ) );
}

void AssetStore::AddTexture( SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath )
{
	SDL_Texture* texture = IMG_LoadTexture( renderer, filePath.c_str() );

	textures.emplace( assetId, texture );

	Logger::Log( "ASSET_STORE::ADDED::TEXTURE StringId: " + assetId + " , file: " + filePath );
}

SDL_Texture* AssetStore::GetTexture( const std::string& assetId ) const
{
	return textures.at( assetId );
}

const std::unordered_map<std::string, SDL_Texture*>& AssetStore::GetTextures() const
{
	return textures;
}
