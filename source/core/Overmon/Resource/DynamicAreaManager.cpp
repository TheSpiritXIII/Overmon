#include <experimental/filesystem>

#include "Overmon/External/cpptoml.h"
#include "Overmon/Resource/DynamicAreaManager.hpp"
#include "Overmon/Resource/DynamicManager.hpp"
#include "Overmon/Util/Debug.hpp"

using namespace std::experimental;

namespace overmon
{

static const filesystem::path resourcesDirectory =
	filesystem::path(RESOURCES_DIRECTORY).append("/areas/");


DynamicAreaManager::DynamicAreaManager()
	: areaCurrent_(0)
{
	reload();
}

void DynamicAreaManager::areaSet(AreaId areaId)
{
	areaCurrent_ = areaId;
}

void DynamicAreaManager::draw(bool foreground, sf::RenderTarget &target,
	const sf::RenderStates &states) const
{
	auto &area = areaMap_.find(areaCurrent_)->second;
	area.area.draw(foreground, target, states);

	if (area.areaNorth != areaCurrent_)
	{
		auto &areaNorth = areaMap_.find(area.areaNorth)->second;

		sf::RenderStates transformState = states;
		transformState.transform.translate(static_cast<float>(area.areaNorthOffset),
			-static_cast<float>(areaNorth.area.height()));
		areaNorth.area.draw(foreground, target, transformState);
	}

	if (area.areaSouth != areaCurrent_)
	{
		auto &areaSouth = areaMap_.find(area.areaSouth)->second;

		sf::RenderStates transformState = states;
		transformState.transform.translate(static_cast<float>(area.areaSouthOffset),
			static_cast<float>(area.area.height()));
		areaSouth.area.draw(foreground, target, transformState);
	}

	if (area.areaEast != areaCurrent_)
	{
		auto &areaEast = areaMap_.find(area.areaEast)->second;

		sf::RenderStates transformState = states;
		transformState.transform.translate(static_cast<float>(area.area.width()),
			static_cast<float>(area.areaEastOffset));
		areaEast.area.draw(foreground, target, transformState);
	}

	if (area.areaWest != areaCurrent_)
	{
		auto &areaWest = areaMap_.find(area.areaWest)->second;

		sf::RenderStates transformState = states;
		transformState.transform.translate(-static_cast<float>(areaWest.area.width()),
			static_cast<float>(area.areaWestOffset));
		areaWest.area.draw(foreground, target, transformState);
	}
}

void DynamicAreaManager::drawBackground(sf::RenderTarget &target,
	const sf::RenderStates &states) const
{
	draw(true, target, states);
}

void DynamicAreaManager::drawForeground(sf::RenderTarget &target,
	const sf::RenderStates &states) const
{
	draw(false, target, states);
}

void DynamicAreaManager::reload()
{
	areaMap_ = load();
}

std::unordered_map<AreaId, DynamicAreaManager::Area> DynamicAreaManager::load()
{
	std::unordered_map<AreaId, DynamicAreaManager::Area> areaMap;
	std::unordered_map<std::string, AreaId> areaNameMap;
	debug("Reloading all areas...");

	filesystem::path manifestPath(resourcesDirectory);
	manifestPath.append("/manifest.toml");

	if (!filesystem::exists(manifestPath))
	{
		debug("Unable to find manifest file.");
		debug("\tAt path:", manifestPath);
		return std::unordered_map<AreaId, DynamicAreaManager::Area>();
	}

	// TODO: filesystem
	auto config = cpptoml::parse_file(manifestPath.string().c_str());
	auto areaList = config->get_table_array("area");

	if (areaList)
	{
		for (const auto &table : *areaList)
		{
			auto id = table->get_as<AreaId>("id");
			if (id)
			{
				auto name = table->get_as<std::string>("name");
				areaNameMap.emplace(*name, *id);
			}
		}
		for (const auto &table : *areaList)
		{
			auto id = table->get_as<AreaId>("id");
			if (id)
			{
				auto filepath = table->get_as<std::string>("file");
				if (filepath)
				{
					filesystem::path path = filesystem::canonical(*filepath, resourcesDirectory);

					if (!filesystem::exists(path))
					{
						debug("Unable to find area file. Skipping.");
						debug("  At path:", path);
						continue;
					}

					auto found = areaMap.find(*id);
					if (found == areaMap.end())
					{
						found = areaMap.emplace(*id, Area()).first;
					}

					// TODO: filesystem
					found->second.area.loadArea(path.string().c_str());

					auto border = table->get_as<std::string>("north");
					found->second.areaNorth = border ? areaNameMap.find(*border)->second : *id;

					border = table->get_as<std::string>("south");
					found->second.areaSouth = border ? areaNameMap.find(*border)->second : *id;

					border = table->get_as<std::string>("east");
					found->second.areaEast = border ? areaNameMap.find(*border)->second : *id;

					border = table->get_as<std::string>("west");
					found->second.areaWest = border ? areaNameMap.find(*border)->second : *id;

					auto offset = table->get_as<int32_t>("northOffset");
					found->second.areaNorthOffset = offset ? *offset * 16 : 0;

					offset = table->get_as<int32_t>("southOffset");
					found->second.areaSouthOffset = offset ? *offset * 16 : 0;

					offset = table->get_as<int32_t>("eastOffset");
					found->second.areaEastOffset = offset ? *offset * 16 : 0;

					offset = table->get_as<int32_t>("westOffset");
					found->second.areaWestOffset = offset ? *offset * 16 : 0;
				}
			}
		}
	}
	debug("Successfully loaded", areaMap.size(), "areas.");

	return areaMap;
}

}
