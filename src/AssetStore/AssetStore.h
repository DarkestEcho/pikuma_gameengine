#pragma once

#include <unordered_map>
#include <string>

class SDL_Texture;
class SDL_Renderer;

class AssetStore
{
private:
	std::unordered_map<std::string, SDL_Texture*> textures;
	// TODO: fonts
	// TODO: audio
public:
	AssetStore();
	~AssetStore();

	void ClearAssets();
	void ClearTextures();

	void AddTexture( SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath );
	SDL_Texture* GetTexture( const std::string& assetId ) const;
	const std::unordered_map<std::string, SDL_Texture*>& GetTextures() const;
};
