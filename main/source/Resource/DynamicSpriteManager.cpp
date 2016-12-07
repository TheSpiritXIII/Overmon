#include <experimental/filesystem>
#include <iostream>

#include "External/cpptoml.h"
#include "Resource/DynamicManager.hpp"
#include "Resource/DynamicSpriteManager.hpp"
#include "Util/Debug.hpp"

namespace overmon
{

static const filesystem::path resourcesDirectory =
	filesystem::path(RESOURCES_DIRECTORY).append("/sprites/");

DynamicSpriteManager::DynamicSpriteManager()
{
	reload();
}

void DynamicSpriteManager::setTexture(sf::Sprite &sprite, SpriteId id) const
{
	auto found = spriteMap_.find(id);
	if (found != spriteMap_.end())
	{
		sprite.setTexture(found->second.texture);
		sprite.setOrigin(found->second.offset_x, found->second.offset_y);
	}
}

void DynamicSpriteManager::setFrame(sf::Sprite &sprite, SpriteId id, uint8_t frame) const
{
	auto found = spriteMap_.find(id);
	if (found != spriteMap_.end())
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
	debug("Reloading all sprites...");

	filesystem::path manifestPath(resourcesDirectory);
	manifestPath.append("/manifest.toml");

	if (!filesystem::exists(manifestPath))
	{
		debug("Unable to find manifest file.");
		debug("\tAt path:", manifestPath);
		return;
	}

	auto config = cpptoml::parse_file(manifestPath.c_str());
	auto spriteList = config->get_table_array("sprite");

	if (spriteList)
	{
		for (const auto &table : *spriteList)
		{
			auto id = table->get_as<uint8_t>("id");
			if (id)
			{
				auto filepath = table->get_as<std::string>("file");
				if (filepath)
				{
					filesystem::path path = filesystem::canonical(*filepath, resourcesDirectory);

					if (!filesystem::exists(path))
					{
						debug("Unable to find sprite file. Skipping.");
						debug("  At path:", path);
						continue;
					}

					auto found = spriteMap_.find(*id);
					if (found == spriteMap_.end())
					{
						found = spriteMap_.emplace(*id, Sprite()).first;
					}

					found->second.texture.loadFromFile(path.c_str());
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

	debug("Successfully loaded", spriteMap_.size(), "sprites.");
}

}
