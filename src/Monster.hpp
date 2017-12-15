#ifndef _MONSTER_HPP_
#define _MONSTER_HPP_

#include "Object.hpp"
#include "SFML/Graphics.hpp"

class Monster : public Object {
public:
	Monster();

	~Monster();

	void setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y);

private:
	void updatePosition(sf::Time& timePerFrame);

	void updateRectSourceSprite(sf::Time& timePerFrame);

private:
	size_t count_update;
};

#endif
