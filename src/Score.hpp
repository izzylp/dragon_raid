#ifndef _SCORE_HPP_
#define _SCORE_HPP_

#include "SFML/Graphics.hpp"

class Score
{
public:
	Score(int _score, int _maxScore);

	~Score();

	void increaseBy(int number);

	void decreaseBy(int number);

	int getScore();

	void draw(sf::RenderTarget& _target) const;

	void update(sf::Time& timePerFrame);

	void updateRectSourceSprite(sf::Time& timePerFrame);

private:
	int score;
	int maxScore;

	sf::Font font;
	sf::Text text;
};

#endif
