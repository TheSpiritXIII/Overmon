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

void DynamicAreaManager::drawBackground(sf::RenderTarget &target,
	const sf::RenderStates &states) const
{
	areaMap_.find(areaCurrent_)->second.drawBackground(target, states);
}

void DynamicAreaManager::drawForeground(sf::RenderTarget &target,
	const sf::RenderStates &states) const
{
	areaMap_.find(areaCurrent_)->second.drawForeground(target, states);
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
			auto id = table->get_as<uint8_t>("id");
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
						found = areaMap_.emplace(*id, DynamicArea()).first;
					}

					found->second.loadArea(path.c_str());
				}
			}
		}
	}
	debug("Successfully loaded", areaMap_.size(), "areas.");
}

}
