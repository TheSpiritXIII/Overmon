#include "DynamicSpriteManager.hpp"
#include "../External/cpptoml.h"

#include <iostream>

namespace overmon
{

DynamicSpriteManager::DynamicSpriteManager()
{
	reload();
}

void DynamicSpriteManager::setTexture(sf::Sprite &sprite, SpriteId id) const
{
	auto found = _spriteMap.find(id);
	if (found != _spriteMap.end())
	{
		sprite.setTexture(found->second.texture);
		sprite.setOrigin(found->second.offset_x, found->second.offset_y);
	}
}

void DynamicSpriteManager::setFrame(sf::Sprite &sprite, SpriteId id, uint8_t frame) const
{
	auto found = _spriteMap.find(id);
	if (found != _spriteMap.end())
	{
		auto size = found->second.texture.getSize();
		size_t columns = size.x / found->second.width;
		size_t x = (frame % columns) * found->second.width;
		size_t y = (frame / columns) * found->second.height;
		sprite.setTextureRect(sf::IntRect(x, y, found->second.width, found->second.height));
	}
}

void DynamicSpriteManager::reload()
{
	const char *resources_dir = "../resources/";

	auto config = cpptoml::parse_file(std::string(resources_dir) + "/resources.toml");
	auto spriteList = config->get_table_array("sprite");

	if (spriteList)
	{
		for (const auto &table : *spriteList)
		{
			auto id = table->get_as<uint8_t>("id");
			if (id)
			{
				auto found = _spriteMap.find(*id);
				if (found == _spriteMap.end())
				{
					found = _spriteMap.emplace(*id, Sprite()).first;
				}

				auto file = table->get_as<std::string>("file");
				if (file)
				{
					found->second.texture.loadFromFile(resources_dir + *file);
					auto textureSize = found->second.texture.getSize();

					auto data = table->get_as<size_t>("width");
					found->second.width = data ? *data : textureSize.x;

					data = table->get_as<size_t>("height");
					found->second.height = data ? *data : textureSize.y;

					data = table->get_as<size_t>("offset_x");
					found->second.offset_x = data ? *data : 0;

					data = table->get_as<size_t>("offset_y");
					found->second.offset_y = data ? *data : 0;
				}
			}
		}
	}
}

}
