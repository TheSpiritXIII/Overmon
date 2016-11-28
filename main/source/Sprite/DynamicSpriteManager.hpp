#pragma once

#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "SpriteManager.hpp"

class DynamicSpriteManager : public SpriteManager<const char *>
{
public:
	DynamicSpriteManager();

	virtual void setTexture(sf::Sprite &sprite, const char *reference) override;
	virtual void setRect(sf::Sprite &sprite, const char *reference, size_t index) override;

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

	std::unordered_map<std::string, Sprite> _spriteMap;
};

typedef const char *SpriteReferenceType;
typedef DynamicSpriteManager DefaultSpriteManager;

#define SPRITE_REFERENCE(s) STRINGIFY(s)
#define STRINGIFY(s) #s
