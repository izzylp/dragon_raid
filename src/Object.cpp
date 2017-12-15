#include "Object.hpp"

#include <iostream>
#include <random>

Object::Object(std::string _img, 
	       float _img_x, 
	       float _img_y, 
	       int _img_nx, 
	       int _img_ny, 
	       float _mult_x,
	       float _mult_y)
{
	x = 0.0;
	y = 0.0;
	img = _img;
	img_x = _img_x;
	img_y = _img_y;
	img_nx = _img_nx;
	img_ny = _img_ny;

	img_width = _mult_x * img_x / img_nx;
	img_height = _mult_y * img_y / img_ny;

	texture = sf::Texture();
	texture.loadFromFile(img);
	rectSourceSprite = sf::IntRect(0.0, 0.0, img_x / img_nx, img_y / img_ny);
	drawable_sprite = sf::Sprite(texture, rectSourceSprite);

	drawable_hitbox = sf::RectangleShape(sf::Vector2f(img_x / img_nx, img_y / img_ny));
	drawable_hitbox.setPosition(x, y);

	hitbox = sf::IntRect(x, y, img_x / img_nx, img_y / img_ny);
}

Object::~Object()
{
}

float Object::getX() const
{
	return x;
}
	
float Object::getY() const
{
	return y;
}

float Object::getWidth() const
{
	return img_width;
}

float Object::getHeight() const
{
	return img_height;
}

void Object::setVelocity(float _velocity)
{
	velocity = _velocity;
}

void Object::setSpritePosition()
{
	drawable_sprite.setPosition(x, y);
}

void Object::moveLeft(sf::Time& timePerFrame)
{
	x -= velocity * timePerFrame.asSeconds();
}

void Object::moveRight(sf::Time& timePerFrame)
{
	x += velocity * timePerFrame.asSeconds();
}

void Object::moveUp(sf::Time& timePerFrame)
{
	y -= velocity * timePerFrame.asSeconds();
}

void Object::moveDown(sf::Time& timePerFrame)
{
	y += velocity * timePerFrame.asSeconds();
}

void Object::verifyAndAdjustBoundaries()
{
	if (x + img_width > max_x) {
		x = max_x - img_width;
	}

	if (x < min_x) {
		x = min_x;
	}
}

bool Object::intersects(Object& that)
{
	return hitbox.intersects(that.hitbox);
}

void Object::update(sf::Time& timePerFrame)
{
	updatePosition(timePerFrame);
	updateHitbox();
	updateRectSourceSprite(timePerFrame);
}

void Object::updateHitbox()
{
	drawable_hitbox.setPosition(x, y);
	hitbox.left = x;
	hitbox.top = y;
}

void Object::draw(sf::RenderTarget& _target) const
{
	//_target.draw(drawable_hitbox);
	_target.draw(drawable_sprite);
}
