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
		int32_t areaNorthOffset;
		int32_t areaSouthOffset;
		int32_t areaEastOffset;
		int32_t areaWestOffset;
		DynamicArea area;
	};

	DynamicAreaManager();
	void areaSet(AreaId areaId);
	void drawBackground(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;
	void drawForeground(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;
	void reload();

	static std::unordered_map<AreaId, Area> load();

private:
	void draw(bool foreground, sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;

	std::unordered_map<AreaId, Area> areaMap_;
	AreaId areaCurrent_;
};

}
