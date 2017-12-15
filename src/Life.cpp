#include "Life.hpp"

Life::Life(int _life, int _maxLife)
{
	life = _life;
	maxLife = _maxLife;

	x = 150;
	y = 420;
	img = "img/heart_small.png";
	img_x = 114;
	img_y = 21;
	img_nx = 5;
	img_ny = 1;

	img_width = img_x / img_nx;
	img_height = img_y / img_ny;

	texture = sf::Texture();
	texture.loadFromFile(img);
	rectSourceSprite = sf::IntRect(0.0, 0.0, img_x / img_nx * life, img_y / img_ny);
	drawable_sprite = sf::Sprite(texture, rectSourceSprite);
	drawable_sprite.setPosition(x, y);
}

Life::~Life()
{
}

void Life::setMax(int _maxLife)
{
	maxLife = _maxLife;
}

void Life::decrease()
{
	if (life - 1 < 0) {
		life = 0;
	} else {
		--life;
	}
}

void Life::increase()
{
	if (life + 1 > 5) {
		life = 5;
	} else {
		++life;
	}
}

int Life::getLife()
{
	return life;
}

void Life::draw(sf::RenderTarget& _target) const
{
	_target.draw(drawable_sprite);
}
	
void Life::updateRectSourceSprite(sf::Time& timePerFrame)
{
	rectSourceSprite.width = img_x / img_nx * life;

	drawable_sprite.setTextureRect(rectSourceSprite);
}

void Life::update(sf::Time& timePerFrame)
{
	updateRectSourceSprite(timePerFrame);
}
