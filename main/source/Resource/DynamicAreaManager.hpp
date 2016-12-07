#include <unordered_map>

#include "BaseAreaManager.hpp"
#include "DynamicArea.hpp"

namespace overmon
{

class DynamicAreaManager : public BaseAreaManager<DynamicAreaManager>
{
public:
	DynamicAreaManager();
	void areaSet(AreaId areaId);
	void drawBackground(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;
	void drawForeground(sf::RenderTarget &target,
		const sf::RenderStates& states = sf::RenderStates::Default) const;
	void reload();

private:
	std::unordered_map<AreaId, DynamicArea> areaMap_;
	AreaId areaCurrent_;
};

}
