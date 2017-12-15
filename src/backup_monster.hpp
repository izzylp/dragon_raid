#ifndef _MONSTER_HPP_
#define _MONSTER_HPP_

#include "SFML/Graphics.hpp"

class Monster
{
public:
	Monster();

	~Monster();

	void update(sf::Time& timePerFrame);

	bool outOfBounds();
	
	void setValid(bool _valid);

	void setSpritePosition();

	void setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y);

	void reset();
	
	bool isValid() const;

	float getX() const;

	float getY() const;

	float getWidth() const;

	float getHeight() const;

	void draw(sf::RenderTarget& _target) const; 

private:
	void updatePosition(sf::Time& timePerFrame);
	void updateRectSourceSprite();

private:
	float x;
	float y;

	float min_x;
	float max_x;
	float min_y;
	float max_y;
	std::string img;
	float img_x;
	float img_y;
	int img_nx;
	int img_ny;
	float img_width;
	float img_height;

	bool valid;

	sf::Texture texture;
	sf::IntRect rectSourceSprite;
	sf::Sprite sprite;
	sf::RectangleShape hitbox;
};

#endif
