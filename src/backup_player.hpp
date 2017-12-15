#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <stdexcept>
#include "SFML/Graphics.hpp"

class Player
{
public:
	Player(float _x, float _y, float _min_x, float _max_x);
	~Player();
	void update(sf::Time& timePerFrame);
	void setX(float _x);
	void setMM(float _min, float _max);
	void setSpritePosition();
	float getX() const;
	float getY() const;
	float getWidth() const;
	//const void draw(sf::RenderTarget& _target, sf::RenderStates _states) const; 
	void draw(sf::RenderTarget& _target) const; 
private:
	void verifyBoundaries();
	void updateRectSourceSprite(sf::Time& timePerFrame);

private:
	float x;
	float y;
	size_t count_update;

	float min_x;
	float max_x;
	std::string img;
	float img_x;
	float img_y;
	int img_nx;
	int img_ny;
	float img_width;
	float img_height;

	sf::Texture texture;
	sf::IntRect rectSourceSprite;
	sf::Sprite sprite;
};

#endif
