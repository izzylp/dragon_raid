#include "Wall.hpp"
#include "Object.hpp"

#include <iostream>

Wall::Wall() : Object("img/wall_tiny.png", 23.0, 23.0, 1, 1, 1.0, 1.0)
{
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;

	drawable_sprite.setTextureRect(rectSourceSprite);

	velocity = 100;

	count_update = 0;
}

Wall::~Wall()
{
}

void Wall::setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y)
{
	x = _x;
	y = _y;

	min_x = _min_x;
	max_x = _max_x;
	min_y = _min_y;
	max_y = _max_y;

	verifyAndAdjustBoundaries();

	updateHitbox();
}

void Wall::updatePosition(sf::Time& timePerFrame)
{
	moveDown(timePerFrame);
}

void Wall::updateRectSourceSprite(sf::Time& timePerFrame)
{
	drawable_sprite.setTextureRect(rectSourceSprite);
}
