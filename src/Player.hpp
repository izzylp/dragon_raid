#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Object.hpp"
#include "SFML/Graphics.hpp"

class Player : public Object
{
public:
	Player();

	~Player();

	void setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y);

	void setX(float _x);

private:
	void verifyBoundaries();

	void updatePosition(sf::Time& timePerFrame);

	void updateRectSourceSprite(sf::Time& timePerFrame);

private:
	size_t count_update;
};

#endif
