#include "Monster.hpp"
#include "Object.hpp"

#include <iostream>

Monster::Monster() : Object("img/monsters_dragon.png", 750.0, 560.0, 10, 8, 1.0, 1.0)
{
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 2 * img_y / img_ny;

	drawable_sprite.setTextureRect(rectSourceSprite);

	velocity = 100;

	count_update = 0;
}

Monster::~Monster()
{
}

void Monster::setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y)
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

void Monster::updatePosition(sf::Time& timePerFrame)
{
	moveDown(timePerFrame);
}

void Monster::updateRectSourceSprite(sf::Time& timePerFrame)
{
	if (count_update < (1 / timePerFrame.asSeconds()) / 10) {
		++count_update;
		return;
	}

	count_update = 0;

	rectSourceSprite.left += img_x / img_nx;

	if (rectSourceSprite.left >= img_x) {
		rectSourceSprite.left = 0;
	}

	drawable_sprite.setTextureRect(rectSourceSprite);
}
