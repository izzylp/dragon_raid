#ifndef _SHOT_HPP_
#define _SHOT_HPP_

#include "Object.hpp"
#include "SFML/Graphics.hpp"

class Shot : public Object {
public:
	Shot();

	~Shot();

	void setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y);

private:
	void updatePosition(sf::Time& timePerFrame);

	void updateRectSourceSprite(sf::Time& timePerFrame);
};

#endif
