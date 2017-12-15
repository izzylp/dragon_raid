#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "SFML/Graphics.hpp"

class Object
{
public:

	explicit Object(std::string _img, 
	       float _img_x, 
	       float _img_y, 
	       int _img_nx, 
	       int _img_ny, 
	       float _mult_x,
	       float _mult_y);

	~Object();

	float getX() const;
	
	float getY() const;

	float getWidth() const;

	float getHeight() const;

	void setVelocity(float _velocity);
	
	void setSpritePosition();
	
	virtual void setPosition(float _x, float _y, float _min_x, float _max_x, float _min_y, float _max_y) = 0;

	void moveLeft(sf::Time& timePerFrame);

	void moveRight(sf::Time& timePerFrame);

	void moveUp(sf::Time& timePerFrame);

	void moveDown(sf::Time& timePerFrame);

	bool intersects(Object& that);

	void update(sf::Time& timePerFrame);

	void draw(sf::RenderTarget& _target) const;

protected:

	void verifyAndAdjustBoundaries();

	virtual void updatePosition(sf::Time& timePerFrame) = 0;

	void updateHitbox();

	virtual void updateRectSourceSprite(sf::Time& timePerFrame) = 0;

protected:

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

	float velocity;

	sf::Texture texture;
	sf::IntRect rectSourceSprite;
	sf::Sprite drawable_sprite;
	sf::RectangleShape drawable_hitbox;
	sf::IntRect hitbox;
};

#endif
