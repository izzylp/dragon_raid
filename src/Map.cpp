#include "Map.hpp"
#include "Object.hpp"

#include <iostream>
#include <random>

Map::Map() : Object("img/map.png", 1024.0, 1024.0, 1, 1, 1.0, 1.0)
{
	count_update = 0;
}

Map::~Map()
{
}

void Map::setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y)
{
}

void Map::updatePosition(sf::Time& timePerFrame)
{
}

void Map::updateRectSourceSprite(sf::Time& timePerFrame)
{
	if (count_update < (1 / timePerFrame.asSeconds()) / 10) {
		++count_update;
		return;
	}

	count_update = 0;

	rectSourceSprite.top += 100;

	if (rectSourceSprite.top >= 1024.0) {
		rectSourceSprite.left = 0;
	}

	drawable_sprite.setTextureRect(rectSourceSprite);
}
