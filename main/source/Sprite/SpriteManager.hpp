#pragma once

template<typename ReferenceType>
class SpriteManager
{
public:
	virtual void setSpriteTexture(sf::Sprite &sprite, ReferenceType reference) = 0;
	virtual void setSpriteRect(sf::Sprite &sprite, ReferenceType reference, size_t index) = 0;
};
