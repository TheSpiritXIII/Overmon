#include "DynamicSpriteManager.hpp"
#include "../External/cpptoml.h"

#include <iostream>

DynamicSpriteManager::DynamicSpriteManager()
{
	reload();
}

void DynamicSpriteManager::setTexture(sf::Sprite &sprite, const char *reference)
{
	auto found = _spriteMap.find(reference);
	if (found != _spriteMap.end())
	{
		sprite.setTexture(found->second.texture);
		sprite.setOrigin(found->second.offset_x, found->second.offset_y);
	}
}

void DynamicSpriteManager::setRect(sf::Sprite &sprite, const char *reference, size_t index)
{
	auto found = _spriteMap.find(reference);
	if (found != _spriteMap.end())
	{
		auto size = found->second.texture.getSize();
		size_t columns = size.x / found->second.width;
		size_t x = (index % columns) * found->second.width;
		size_t y = (index / columns) * found->second.height;
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
			auto name = table->get_as<std::string>("name");
			if (name)
			{
				auto found = _spriteMap.find(*name);
				if (found == _spriteMap.end())
				{
					found = _spriteMap.emplace(*name, Sprite()).first;
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
