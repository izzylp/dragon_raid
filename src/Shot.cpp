#include "Shot.hpp"
#include "Object.hpp"

#include <iostream>

Shot::Shot() : Object("img/shot.png", 64.0, 12.8, 5, 1, 1.0, 1.0)
{
}

Shot::~Shot()
{
}

void Shot::setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y)
{
	x = _x;
	y = _y;

	min_x = _min_x;
	max_x = _max_x;
	min_y = _min_y;
	max_y = _max_y;

	velocity = 300;

	verifyAndAdjustBoundaries();

	updateHitbox();
}

void Shot::updatePosition(sf::Time& timePerFrame)
{
	moveUp(timePerFrame);
}

void Shot::updateRectSourceSprite(sf::Time& timePerFrame)
{
	drawable_sprite.setTextureRect(rectSourceSprite);
}
