#include <unordered_map>

#include "BaseAreaManager.hpp"
#include "DynamicArea.hpp"

namespace overmon
{

class DynamicAreaManager : public BaseAreaManager<DynamicAreaManager>
{
public:
	struct Area
	{
		AreaId areaNorth;
		AreaId areaSouth;
		AreaId areaEast;
		AreaId areaWest;
		DynamicArea area;
	};

	DynamicAreaManager();
	void areaSet(AreaId areaId);
	void drawBackground(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;
	void drawForeground(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;
	void reload();

private:
	void draw(bool foreground, sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;

	std::unordered_map<AreaId, Area> areaMap_;
	AreaId areaCurrent_;
};

}
