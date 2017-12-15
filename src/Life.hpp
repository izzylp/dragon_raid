#ifndef _LIFE_HPP_
#define _LIFE_HPP_

#include "SFML/Graphics.hpp"

class Life
{
public:
	Life(int _life, int _maxLife);

	~Life();

	void setMax(int _maxLife);

	void decrease();

	void increase();

	int getLife();

	void draw(sf::RenderTarget& _target) const;

	void update(sf::Time& timePerFrame);

	void updateRectSourceSprite(sf::Time& timePerFrame);

private:
	int life;
	int maxLife;

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

	sf::Texture texture;
	sf::IntRect rectSourceSprite;
	sf::Sprite drawable_sprite;
};

#endif
