#include "shot.hpp"

#include <iostream>

Shot::Shot()
{
	img = "img/shot.png";
	img_x = 64;
	img_y = 12.8;
	img_nx = 5;
	img_ny = 1;

	img_width = 1.0 * img_x / img_y;
	img_height = 1.0 * img_y / img_ny;

	texture = sf::Texture();
	texture.loadFromFile(img);
	rectSourceSprite = sf::IntRect(0, 0, img_x / img_nx, img_y / img_ny);
	sprite = sf::Sprite(texture, rectSourceSprite);

	valid = 0;
}

Shot::~Shot()
{
}

void Shot::setValid(bool _valid)
{
	valid = _valid;
}

void Shot::setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y)
{
	x = _x;
	y = _y;

	min_x = _min_x;
	max_x = _max_x;
	min_y = _min_y;
	max_y = _max_y;

	valid = 1;
}

void Shot::reset()
{
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
}

void Shot::setSpritePosition()
{
	sprite.setPosition(x, y);
}

bool Shot::isValid() const
{
	return valid;
}

void Shot::update(sf::Time& timePerFrame)
{
	updatePosition(timePerFrame);
	updateRectSourceSprite();
}

void Shot::updatePosition(sf::Time& timePerFrame)
{
	y -= 300 * timePerFrame.asSeconds();
}

void Shot::updateRectSourceSprite()
{
	sprite.setTextureRect(rectSourceSprite);
}

float Shot::getX() const
{
	return x;
}

float Shot::getY() const
{
	return y;
}

float Shot::getWidth() const
{
	return img_width;
}

float Shot::getHeight() const
{
	return img_width;
}

void Shot::draw(sf::RenderTarget& _target) const
{
	_target.draw(sprite);
}
