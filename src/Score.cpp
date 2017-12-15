#include "Score.hpp"

Score::Score(int _score, int _maxScore)
{
	font.loadFromFile("fonts/prstart.ttf");
	text.setFont(font);
	text.setCharacterSize(10);
	text.setStyle(sf::Text::Regular);

	text.setString(std::to_string(score));
	text.setPosition(150, 400);

	score = _score;
	maxScore = _maxScore;
}

Score::~Score()
{
}

void Score::increaseBy(int number)
{
	if (score + number > maxScore) {
		score = 50000;
	} else if (score + number <= 0) {
		score = 0;
	} else {
		score += number;
	}
}

int Score::getScore()
{
	return score;
}

void Score::draw(sf::RenderTarget& _target) const
{
	_target.draw(text);
}

void Score::update(sf::Time& timePerFrame)
{
	text.setString(std::to_string(score));
}
