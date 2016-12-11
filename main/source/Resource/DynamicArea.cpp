#include <cassert>
#include <experimental/string_view>
#include <experimental/filesystem>
#include <unordered_map>

#include "DynamicArea.hpp"
#include "External/tinyxml2.h"
#include "Util/Debug.hpp"

using namespace std::experimental;

namespace overmon
{

typedef std::pair<size_t, sf::Texture*> GidPair;

static std::unordered_map<std::string, sf::Texture*> textureMap;

std::vector<GidPair> loadAreaImages(tinyxml2::XMLElement *tilesetElement, const char *relativePath,
	size_t gid = 0)
{
	if (gid == 0)
	{
		gid = std::stoul(tilesetElement->Attribute("firstgid"));
	}

	auto child = tilesetElement->FirstChildElement();
	if (child == nullptr)
	{
		tinyxml2::XMLDocument document;
		std::error_code error_code;
		auto sourceName = tilesetElement->Attribute("source");
		auto sourcePath = filesystem::canonical(sourceName, relativePath, error_code);
		if (error_code || !filesystem::exists(sourcePath))
		{
			debug("Unable to load tileset.");
			debug("  From file:", relativePath);
			debug("  Tileset path:", tilesetElement->Attribute("source"));
			return std::vector<GidPair>();
		}
		document.LoadFile(sourcePath.c_str());
		return loadAreaImages(document.FirstChildElement("tileset"),
			sourcePath.parent_path().c_str(), gid);
	}

	std::vector<GidPair> gidMap;

	while (child != nullptr)
	{
		if (std::experimental::string_view(child->Value()) == "image")
		{
			// Canonicalize the source so that two differen looking relative paths are same.
			auto sourceNormalized = filesystem::canonical(child->Attribute("source"), relativePath);
			std::string textureFilename = sourceNormalized.string();

			auto textureFound = textureMap.find(textureFilename);
			if (textureFound == textureMap.end())
			{
				sf::Texture *texture = new sf::Texture();
				texture->loadFromFile(textureFilename);
				auto thing = textureMap.emplace(textureFilename, texture);
				textureFound = textureMap.find(textureFilename);
			}
			// Else, skip adding because already there.

			gidMap.push_back(GidPair(gid, textureFound->second));
		}
		child = child->NextSiblingElement();
	}
	return gidMap;
}

std::vector<sf::Sprite> loadAreaTiles(tinyxml2::XMLElement *layerElement,
	const std::vector<GidPair> &gidMap)
{
	std::vector<sf::Sprite> tileList;
	size_t width = std::stoul(layerElement->Attribute("width"));
	size_t position = 0;

	tinyxml2::XMLElement *tileData = layerElement->FirstChildElement("data")->FirstChildElement();
	while (tileData != nullptr)
	{
		size_t gid = std::stoul(tileData->Attribute("gid"));
		if (gid != 0)
		{
			auto gidTexture = std::lower_bound(gidMap.begin(), gidMap.end(), gid,
				[](auto &lhs, auto &rhs)
			{
				return lhs.first < rhs;
			});
			if (gidTexture == gidMap.end() || gidTexture->first != gid)
			{
				gidTexture = std::prev(gidTexture);
			}
			size_t tileIndex = gid - gidTexture->first;

			sf::Sprite tile;
			tile.setPosition((position % width) * 16, (position / width) * 16);
			tile.setTexture(*gidTexture->second);

			auto textureSize = tile.getTexture()->getSize();
			size_t tileLeft = tileIndex % (textureSize.x / 16);
			size_t tileTop = tileIndex / (textureSize.x / 16);
			tile.setTextureRect(sf::IntRect(tileLeft * 16, tileTop * 16, 16, 16));
			tileList.emplace_back(tile);
		}
		tileData = tileData->NextSiblingElement();
		position += 1;
	}
	return tileList;
}

void DynamicArea::loadArea(const char *filename)
{
	width_ = 0;
	height_ = 0;
	tilesForeground_.clear();
	tilesBackground_.clear();

	tinyxml2::XMLDocument document;
	if (document.LoadFile(filename) != 0)
	{
		debug("Unable to load Tiled file:", filename);
		return;
	}

	filesystem::path relativePath = filesystem::canonical(filesystem::path(filename).parent_path());
	auto mapElement = document.FirstChildElement("map");
	width_ = std::stoul(mapElement->Attribute("width")) * 16;
	height_ = std::stoul(mapElement->Attribute("height")) * 16;

	auto child = mapElement->FirstChildElement();
	std::vector<GidPair> gidMap;
	while (child != nullptr)
	{
		auto elementType = std::experimental::string_view(child->Value());
		if (elementType == "tileset")
		{
			std::vector<GidPair> gidLoaded = loadAreaImages(child, relativePath.c_str());
			if (gidLoaded.empty())
			{
				debug("Unable to parse tileset:", filename);
				debug("  Unable to read tileset image properties.");
				return;
			}
			else
			{
				gidMap.insert(gidMap.end(), gidLoaded.begin(), gidLoaded.end());
			}
		}
		else if (elementType == "layer")
		{
			assert(!gidMap.empty());
			auto layerName = std::experimental::string_view(child->Attribute("name"));
			if (layerName == "Background")
			{
				auto tiles = loadAreaTiles(child, gidMap);
				tilesForeground_.insert(tilesForeground_.begin(), tiles.begin(), tiles.end());
			}
			else if (layerName == "Middleground")
			{
				auto tiles = loadAreaTiles(child, gidMap);
				tilesForeground_.insert(tilesForeground_.end(), tiles.begin(), tiles.end());
			}
			else if (layerName == "Foreground")
			{
				auto tiles = loadAreaTiles(child, gidMap);
				tilesBackground_.insert(tilesBackground_.begin(), tiles.begin(), tiles.end());
			}
		}
		child = child->NextSiblingElement();
	}
}

size_t DynamicArea::width() const
{
	return width_;
}

size_t DynamicArea::height() const
{
	return height_;
}

void DynamicArea::drawBackground(sf::RenderTarget &target, const sf::RenderStates &states) const
{
	for (auto &&tile : tilesForeground_)
	{
		target.draw(tile, states);
	}
}

void DynamicArea::drawForeground(sf::RenderTarget &target, const sf::RenderStates &states) const
{
	for (auto &&tile : tilesBackground_)
	{
		target.draw(tile, states);
	}
}

void DynamicArea::draw(bool background, sf::RenderTarget &target,
	const sf::RenderStates &states) const
{
	if (background)
	{
		drawBackground(target, states);
	}
	else
	{
		drawForeground(target, states);
	}
}

}
