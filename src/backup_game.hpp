#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include "SFML/Graphics.hpp"

#include "player.hpp"
#include "monster.hpp"
#include "shot.hpp"

class Game
{
public:
	Game();

	~Game();

	void Init(const std::string title, int width, int height, int bpp, bool fullscreen);

	void HandleEvents(sf::Time& timePerFrame);

	void Update(sf::Time& timePerFrame);

	void Draw();

	void Clean();

	bool Running();

	void verifyCollisions();

	void verifyOutOfBounds();

private:
	/* Init */
	bool m_bRunning;
	sf::RenderWindow *main_window;
	float width;
	float height;
	float min_x;
	float max_x;
	float min_y;
	float max_y;
	size_t max_shots;
	size_t i_shot;
	size_t n_shot;
	size_t max_monsters;
	size_t i_monster;
	size_t n_monster;
	sf::Clock clock_shot;
	const float delay_shot;
	sf::Clock clock_monster;
	const float delay_monster;
	sf::Clock clock;

	/* Update */
	Player *player;
	Shot *shot;
	Monster *monster;

	/* HandleEvents */
	std::unordered_map<int, bool> keys;
	std::list<int> changedKeys;
};

#endif
