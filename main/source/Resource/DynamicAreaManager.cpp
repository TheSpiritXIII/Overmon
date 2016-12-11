#include <experimental/filesystem>

#include "External/cpptoml.h"
#include "Resource/DynamicAreaManager.hpp"
#include "Resource/DynamicManager.hpp"
#include "Util/Debug.hpp"

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
		transformState.transform.translate(0, -static_cast<float>(areaNorth.area.height()));
		areaNorth.area.draw(foreground, target, transformState);
	}

	if (area.areaSouth != areaCurrent_)
	{
		auto &areaSouth = areaMap_.find(area.areaSouth)->second;

		sf::RenderStates transformState = states;
		transformState.transform.translate(0, area.area.height());
		areaSouth.area.draw(foreground, target, transformState);
	}

	if (area.areaEast != areaCurrent_)
	{
		auto &areaEast = areaMap_.find(area.areaEast)->second;

		sf::RenderStates transformState = states;
		transformState.transform.translate(area.area.width(), 0);
		areaEast.area.draw(foreground, target, transformState);
	}

	if (area.areaWest != areaCurrent_)
	{
		auto &areaWest = areaMap_.find(area.areaWest)->second;

		sf::RenderStates transformState = states;
		transformState.transform.translate(-static_cast<float>(areaWest.area.width()), 0);
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
	debug("Reloading all areas...");

	filesystem::path manifestPath(resourcesDirectory);
	manifestPath.append("/manifest.toml");

	if (!filesystem::exists(manifestPath))
	{
		debug("Unable to find manifest file.");
		debug("\tAt path:", manifestPath);
		return;
	}

	auto config = cpptoml::parse_file(manifestPath.c_str());
	auto areaList = config->get_table_array("area");

	if (areaList)
	{
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

					auto found = areaMap_.find(*id);
					if (found == areaMap_.end())
					{
						found = areaMap_.emplace(*id, Area()).first;
					}

					found->second.area.loadArea(path.c_str());

					auto data = table->get_as<AreaId>("north");
					found->second.areaNorth = data ? *data : *id;

					data = table->get_as<AreaId>("south");
					found->second.areaSouth = data ? *data : *id;

					data = table->get_as<AreaId>("east");
					found->second.areaEast = data ? *data : *id;

					data = table->get_as<AreaId>("west");
					found->second.areaWest = data ? *data : *id;
				}
			}
		}
	}
	debug("Successfully loaded", areaMap_.size(), "areas.");
}

}
