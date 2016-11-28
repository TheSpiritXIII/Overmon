#pragma once

template<typename ReferenceType>
class SpriteManager
{
public:
	virtual void setTexture(sf::Sprite &sprite, ReferenceType reference) = 0;
	virtual void setRect(sf::Sprite &sprite, ReferenceType reference, size_t index) = 0;
};
