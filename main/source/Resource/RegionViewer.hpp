#pragma once

#include "Resource/DynamicArea.hpp"

namespace overmon
{

class RegionViewer
{
public:
	void draw(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;
	void reload();

private:
	typedef std::pair<DynamicArea, sf::Transform> DynamicAreaLocation;
	std::vector<DynamicAreaLocation> areaList_;
};

}
