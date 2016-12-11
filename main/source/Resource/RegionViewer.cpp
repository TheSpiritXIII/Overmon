#include <queue>

#include "Resource/RegionViewer.hpp"
#include "Resource/DynamicAreaManager.hpp"
#include "Util/Debug.hpp"

namespace overmon
{

void RegionViewer::draw(sf::RenderTarget &target, const sf::RenderStates& states) const
{
	for (auto &&area : areaList_)
	{
		sf::RenderStates states;
		states.transform = area.second;
		area.first.draw(true, target, states);
		area.first.draw(false, target, states);
	}
}


void RegionViewer::reload()
{
	typedef std::pair<AreaId, sf::Transform> DynamicAreaIdLocation;

	auto areaMap = DynamicAreaManager::load();
	std::queue<DynamicAreaIdLocation> areaQueue;
	areaQueue.push(DynamicAreaIdLocation(0, sf::Transform()));

	while (!areaQueue.empty())
	{
		auto areaFront = areaQueue.front();
		auto areaProcess = areaMap.find(areaFront.first);

		areaList_.push_back({areaProcess->second.area, areaFront.second});

//		sf::Transform transform = areaFront.second;
//			transform.translate(0, -16);
//			areaQueue.push({areaProcess->second.areaNorth, transform});

		auto add_area_if = [&](auto areaPosition, auto areaTranslate)
		{
			if (areaPosition != areaFront.first && areaMap.find(areaPosition) != areaMap.end())
			{
				sf::Transform transform = areaFront.second;
				auto transformVector = areaTranslate(areaMap.find(areaPosition)->second.area);
				transform.translate(transformVector);
				areaQueue.push({areaPosition, transform});
			}
		};

		add_area_if(areaProcess->second.areaNorth, [&](const DynamicArea &areaFound)
		{
			auto offset = areaProcess->second.areaNorthOffset * 16;
			return sf::Vector2f(offset, -static_cast<float>(areaFound.height()));
		});

		add_area_if(areaProcess->second.areaSouth, [&](const DynamicArea &areaFound)
		{
			auto offset = areaProcess->second.areaSouthOffset * 16;
			return sf::Vector2f(offset, areaProcess->second.area.height());
		});

		add_area_if(areaProcess->second.areaEast, [&](const DynamicArea &areaFound)
		{
			auto offset = areaProcess->second.areaEastOffset * 16;
			return sf::Vector2f(areaProcess->second.area.width(), offset);
		});

		add_area_if(areaProcess->second.areaWest, [&](const DynamicArea &areaFound)
		{
			auto offset = areaProcess->second.areaWestOffset * 16;
			return sf::Vector2f(-static_cast<float>(areaFound.width()), offset);
		});

		areaMap.erase(areaProcess);
		areaQueue.pop();
	}
}

}
