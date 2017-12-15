#ifndef _WALL_HPP_
#define _WALL_HPP_

#include "Object.hpp"
#include "SFML/Graphics.hpp"

class Wall : public Object {
public:
	Wall();

	~Wall();

	void setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y);

private:
	void updatePosition(sf::Time& timePerFrame);

	void updateRectSourceSprite(sf::Time& timePerFrame);

private:
	size_t count_update;
};

#endif
