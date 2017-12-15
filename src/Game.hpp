#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <iostream>
#include <string>
#include <stdint.h>
#include "SFML/Graphics.hpp"

#include "Player.hpp"
#include "Monster.hpp"
#include "Wall.hpp"
#include "Shot.hpp"
#include "Life.hpp"
#include "Score.hpp"
#include "Map.hpp"
#include "Controller.hpp"
#include "CircularArray.hpp"

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
	template <typename T> void 
	createObject(const uint32_t _chance, sf::Clock& _clock, const float _delay, CircularArray<T>& _objects);

	template <typename T> void 
	verifyOutOfBoundsObject(CircularArray<T>& _objects);

	template <typename T> void 
	setSpritePositionObject(CircularArray<T>& _objects);

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
	size_t max_monsters;
	size_t max_wall;
	uint32_t monster_chance;
	uint32_t wall_chance;
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
	CircularArray<Monster> monsters;
	CircularArray<Shot> shots;
	CircularArray<Wall> walls;

	Score *score;
	Life *life;
	Map *map;

	/* HandleEvents */
	Controller controller;
	std::unordered_map<int, bool> keys;
	std::list<int> changedKeys;
};

#endif
