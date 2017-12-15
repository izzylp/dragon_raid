#include "Player.hpp"

Player::Player() : Object("img/player.png", 512.0, 128.0, 4, 1, 0.92, 0.92)
{
	count_update = 0;
}

Player::~Player()
{
}

void Player::setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y)
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

void Player::updatePosition(sf::Time& timePerFrame)
{
	verifyAndAdjustBoundaries();
}

void Player::updateRectSourceSprite(sf::Time& timePerFrame)
{
	if (count_update < (1 / timePerFrame.asSeconds()) / 5) {
		++count_update;
		return;
	}

	count_update = 0;

	rectSourceSprite.left += img_x / img_nx;

	if (rectSourceSprite.left >= img_x) {
		rectSourceSprite.left = 0;
		rectSourceSprite.top += img_y / img_ny;
	}

	if (rectSourceSprite.top >= img_y) {
		rectSourceSprite.top = 0;
	}
		
	drawable_sprite.setTextureRect(rectSourceSprite);
}
