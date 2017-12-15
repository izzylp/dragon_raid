#include "monster.hpp"

#include <iostream>
#include <random>

Monster::Monster()
{
	img = "img/monsters.png";
	img_x = 100;
	img_y = 77;
	img_nx = 5;
	img_ny = 4;

	img_width = 1.0 * img_x / img_nx;
	img_height = 1.0 * img_y / img_ny;

	texture = sf::Texture();
	texture.loadFromFile(img);
	rectSourceSprite = sf::IntRect(0, 0, img_x / img_nx, img_y / img_ny);
	sprite = sf::Sprite(texture, rectSourceSprite);

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni_x(0, img_nx);
	std::uniform_int_distribution<int> uni_y(0, img_ny);

	auto random_x = uni_x(rng);
	auto random_y = uni_y(rng);

	if (random_y == 3 && random_x >= 3) {
		random_y = 2;
	}

	rectSourceSprite.left = random_x * img_x / img_nx;
	rectSourceSprite.top = random_y * img_y / img_ny;

	hitbox = sf::RectangleShape(sf::Vector2f(img_width, img_height));
	hitbox.setPosition(x, y);

	valid = 0;
}

Monster::~Monster()
{
}

void Monster::setValid(bool _valid)
{
	valid = _valid;
}

void Monster::setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y)
{
	x = _x;
	y = _y;

	min_x = _min_x;
	max_x = _max_x;
	min_y = _min_y;
	max_y = _max_y;

	if (x + img_width > max_x) {
		x = max_x - img_width;
	}

	valid = 1;
}

void Monster::reset()
{
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
}

void Monster::setSpritePosition()
{
	sprite.setPosition(x, y);
	hitbox.setPosition(x, y);
}

bool Monster::isValid() const
{
	return valid;
}

void Monster::update(sf::Time& timePerFrame)
{
	updatePosition(timePerFrame);
	updateRectSourceSprite();
}

void Monster::updatePosition(sf::Time& timePerFrame)
{
	y += 100 * timePerFrame.asSeconds();
}

void Monster::updateRectSourceSprite()
{
	sprite.setTextureRect(rectSourceSprite);
}

float Monster::getX() const
{
	return x;
}

float Monster::getY() const
{
	return y;
}

float Monster::getWidth() const
{
	return img_width;
}

float Monster::getHeight() const
{
	return img_height;
}

void Monster::draw(sf::RenderTarget& _target) const
{
	//_target.draw(hitbox);
	_target.draw(sprite);
}
