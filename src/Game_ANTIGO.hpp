#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include "SFML/Graphics.hpp"

#include "Player.hpp"
#include "Monster.hpp"
#include "Wall.hpp"
#include "Shot.hpp"
#include "Life.hpp"
#include "Score.hpp"
#include "Map.hpp"
#include "Controller.hpp"

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

	bool Opened();

	void verifyCollisions();

	void verifyOutOfBounds();

private:
	/* Init */
	bool m_bRunning;
	bool m_bOpened;
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
	size_t max_wall;
	size_t i_wall;
	size_t n_wall;
	sf::Clock clock_shot;
	const float delay_shot;
	sf::Clock clock_monster;
	const float delay_monster;
	sf::Clock clock_player;
	const float delay_player;
	sf::Clock clock_wall;
	const float delay_wall;
	sf::Clock clock;

	/* Update */
	Player *player;
	Shot *shot;
	Monster *monster;
	Wall *wall;
	Score *score;
	Life *life;
	Map *map;

	/* HandleEvents */
	Controller controller;
	std::unordered_map<int, bool> keys;
	std::list<int> changedKeys;
};

#endif
