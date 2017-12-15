#include "player.hpp"

Player::Player(float _x, float _y, float _min_x, float _max_x)
{
	x = _x;
	y = _y;
	min_x = _min_x;
	max_x = _max_x;

	img = "img/player.png";
	img_x = 512;
	img_y = 128;
	img_nx = 4;
	img_ny = 1;

	img_width = 0.92 * img_x / img_nx;
	img_height = 0.92 * img_y / img_ny;

	texture = sf::Texture();
	texture.loadFromFile(img);
	rectSourceSprite = sf::IntRect(0, 0, img_x / img_nx, img_y / img_ny);
	sprite = sf::Sprite(texture, rectSourceSprite);

	count_update = 0;
}

Player::~Player()
{
}

void Player::update(sf::Time& timePerFrame)
{
	updateRectSourceSprite(timePerFrame);
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
		
	sprite.setTextureRect(rectSourceSprite);
}

void Player::setX(float _x)
{
	x = _x;

	verifyBoundaries();
}

void Player::setMM(float _min, float _max)
{
	min_x = _min;
	max_x = _max;

	verifyBoundaries();
}

void Player::setSpritePosition()
{
	sprite.setPosition(x, y);
}

void Player::verifyBoundaries()
{
	if (x + img_width > max_x) {
		x = max_x - img_width;
	}

	if (x < min_x) {
		x = min_x;
	}
}

float Player::getX() const
{
	return x;
}

float Player::getY() const
{
	return y;
}

float Player::getWidth() const
{
	return img_width;
}

void Player::draw(sf::RenderTarget& _target) const
{
	_target.draw(sprite);
}
