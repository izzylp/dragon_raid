#include "Game.hpp"

#include <random>

Game::Game() : delay_shot(80), delay_monster(80), delay_player(1500), delay_wall(80)
{
}

Game::~Game()
{
	delete player;
	delete life;
	delete score;
}

void Game::Init(const std::string title, int _width, int _height, int bpp, bool fullscreen)
{
	width = _width;
	height = _height;

	min_x = 0; 
	max_x = 640; 
	min_y = 0;
	max_y = 480;

	main_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	main_window->setKeyRepeatEnabled(false);

	map = new Map();

	player = new Player();
	player->setPosition(width / 2, height / 2 + height * 0.2, min_x, max_x, min_y, max_y);
	player->setSpritePosition();
	player->setVelocity(width / 2);

	max_shots = 100;
	shots.setSize(max_shots);

	max_monsters = 100;
	monster_chance = 5;
	monsters.setSize(max_monsters);

	max_wall = 100;
	wall_chance = 2;
	walls.setSize(max_wall);

	life = new Life(3, 3);
	score = new Score(1000, 50000);

	m_bRunning = true;
	m_bOpened = true;
}

void Game::HandleEvents(sf::Time& timePerFrame)
{
	sf::Event event;
	changedKeys.clear();

	m_bOpened = controller.checkAndHandleEvents(*main_window, event);

	if (life->getLife() == 0) {
		m_bRunning = 0;
	}

	if (controller.isKeyPressed(LEFT_ARROW)) {
		player->moveLeft(timePerFrame);
	}
		
	if (controller.isKeyPressed(RIGHT_ARROW)) {
		player->moveRight(timePerFrame);
	}

	if (controller.isKeyPressed(Q) && clock_shot.getElapsedTime().asMilliseconds() > delay_shot && !shots.isFull()) {
		auto it = shots.insert();
		it->setPosition(player->getX() + player->getWidth() / 2 - it->getWidth() / 2, player->getY(), min_x, max_x, min_y, max_y);
		clock_shot.restart();
	}

	createObject(monster_chance, clock_monster, delay_monster, monsters);
	createObject(wall_chance, clock_wall, delay_wall, walls);

	player->setSpritePosition();
	setSpritePositionObject(shots);
	setSpritePositionObject(monsters);
	setSpritePositionObject(walls);

	verifyOutOfBounds();
	verifyCollisions();
}

void Game::Update(sf::Time& timePerFrame)
{
	player->update(timePerFrame);
	life->update(timePerFrame);
	score->update(timePerFrame);

	for (auto it = shots.begin(); it != shots.end(); ++it) {
		if (!shots.isValid(it)) {
			continue;
		}
		it->update(timePerFrame);
	}

	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (!monsters.isValid(it)) {
			continue;
		}
		it->update(timePerFrame);
	}

	for (auto it = walls.begin(); it != walls.end(); ++it) {
		if (!walls.isValid(it)) {
			continue;
		}
		it->update(timePerFrame);
	}
}

void Game::Draw()
{
	map->draw(*main_window);
	player->draw(*main_window);
	life->draw(*main_window);
	score->draw(*main_window);

	for (auto it = shots.begin(); it != shots.end(); ++it) {
		if (!shots.isValid(it)) {
			continue;
		}
		it->draw(*main_window);
	}

	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (!monsters.isValid(it)) {
			continue;
		}
		it->draw(*main_window);
	}

	for (auto it = walls.begin(); it != walls.end(); ++it) {
		if (!walls.isValid(it)) {
			continue;
		}
		it->draw(*main_window);
	}

	main_window->display();
}

void Game::Clean()
{
	main_window->clear();
}

bool Game::Running()
{
	return m_bRunning && m_bOpened;
}

bool Game::Opened()
{
	return m_bOpened;
}

void Game::verifyCollisions()
{
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (!monsters.isValid(it)) {
			continue;
		}

		for (auto jt = shots.begin(); jt != shots.end(); ++jt) {
			if (!shots.isValid(jt)) {
				continue;
			}

			if (it->intersects(*jt)) {
				monsters.setInvalid(it);
				shots.setInvalid(jt);

				score->increaseBy(50);

				break;
			}
		}
	}

	if (clock_player.getElapsedTime().asMilliseconds() > delay_player) {
		for (auto it = monsters.begin(); it != monsters.end(); ++it) {
			if (!monsters.isValid(it)) {
				continue;
			}

			if (it->intersects(*player)) {
				life->decrease();
				clock_player.restart();
			}
		}
	}
}

void Game::verifyOutOfBounds()
{
	verifyOutOfBoundsObject(shots);
	verifyOutOfBoundsObject(monsters);
	verifyOutOfBoundsObject(walls);
}

template <typename T> void 
Game::createObject(const uint32_t _chance, sf::Clock& _clock, const float _delay, CircularArray<T>& _objects)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint32_t> uniform_chance(0, 100);
	std::uniform_int_distribution<uint32_t> uniform_chance_2(50, 300);
	auto chance = uniform_chance(rng);
	auto velocity_chance = uniform_chance_2(rng);

	if (chance < _chance && _clock.getElapsedTime().asMilliseconds() > _delay && !_objects.isFull()) {
		std::uniform_int_distribution<int> uni_y(min_x, max_x);
		auto random_y = uni_y(rng);
		auto it = _objects.insert();

		it->setPosition(random_y, 0, min_x, max_x, min_y, max_y);
		it->setVelocity(velocity_chance);

		_clock.restart();
	}
}

template <typename T> void 
Game::verifyOutOfBoundsObject(CircularArray<T>& _objects)
{
	for (auto it = _objects.begin(); it != _objects.end(); ++it) {
		if (_objects.isValid(it) && it->getY() < min_y) {
			_objects.setInvalid(it);
		}
	}
}

template <typename T> void 
Game::setSpritePositionObject(CircularArray<T>& _objects)
{
	for (auto it = _objects.begin(); it != _objects.end(); ++it) {
		if (!_objects.isValid(it)) {
			continue;
		}
		it->setSpritePosition();
	}

}
