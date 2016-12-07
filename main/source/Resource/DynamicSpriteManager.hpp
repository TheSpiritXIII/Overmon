#pragma once

#include <string>
#include <unordered_map>
#include <experimental/filesystem>

#include "BaseSpriteManager.hpp"

using namespace std::experimental;

namespace overmon
{

class DynamicSpriteManager : public BaseSpriteManager<DynamicSpriteManager>
{
public:
	DynamicSpriteManager();

	void setTexture(sf::Sprite &sprite, SpriteId id) const;
	void setFrame(sf::Sprite &sprite, SpriteId id, uint8_t frame) const;

	void reload();

private:
	struct Sprite
	{
		size_t width;
		size_t height;
		size_t offset_x;
		size_t offset_y;
		sf::Texture texture;
	};

	std::unordered_map<SpriteId, Sprite> spriteMap_;
};

}
