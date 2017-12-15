#include "Game.hpp"

#include <random>

Game::Game() : delay_shot(80), delay_monster(80), delay_player(1500), delay_wall(80)
{
}

Game::~Game()
{
	delete player;
	delete[] shot;
	delete[] monster;
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
	n_shot = 0;
	i_shot = 0;
	shot = new Shot[max_shots];

	max_monsters = 100;
	n_monster = 0;
	i_monster = 0;
	monster = new Monster[max_monsters];

	max_wall = 100;
	n_wall = 0;
	i_wall = 0;
	wall = new Wall[max_wall];

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

	if (controller.isKeyPressed(Q) && clock_shot.getElapsedTime().asMilliseconds() > delay_shot && n_shot < max_shots) {
		while (shot[i_shot].isValid()) {
			i_shot = (i_shot + 1) % max_shots;
		}
		shot[i_shot].setPosition(player->getX() + player->getWidth() / 2 - shot[i_shot].getWidth() / 2, player->getY(), min_x, max_x, min_y, max_y);
		shot[i_shot].setValid();
		i_shot = (i_shot + 1) % max_shots;
		++n_shot;

		clock_shot.restart();
	}

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uniform_chance(0, 100);
	std::uniform_int_distribution<int> uniform_chance_2(50, 300);
	auto monster_chance = uniform_chance(rng);
	auto wall_chance = uniform_chance(rng);
	auto monster_velocity_chance = uniform_chance_2(rng);
	auto wall_velocity_chance = uniform_chance_2(rng);

	if (monster_chance < 5 && clock_monster.getElapsedTime().asMilliseconds() > delay_monster && n_monster < max_monsters) {
		std::uniform_int_distribution<int> uni_y(min_x, max_x);
		auto random_y = uni_y(rng);
		while (monster[i_monster].isValid()) {
			i_monster = (i_monster + 1) % max_monsters;
		}
		monster[i_monster].setPosition(random_y, 0, min_x, max_x, min_y, max_y);
		monster[i_monster].setValid();
		monster[i_monster].setVelocity(monster_velocity_chance);
		i_monster = (i_monster + 1) % max_monsters;
		++n_monster;

		clock_monster.restart();
	}

	if (wall_chance < 2 && clock_wall.getElapsedTime().asMilliseconds() > delay_wall && n_wall < max_wall) {
		std::uniform_int_distribution<int> uni_y(min_x, max_x);
		auto random_y = uni_y(rng);
		while (wall[i_wall].isValid()) {
			i_wall = (i_wall + 1) % max_wall;
		}
		wall[i_wall].setPosition(random_y, 0, min_x, max_x, min_y, max_y);
		wall[i_wall].setValid();
		wall[i_wall].setVelocity(wall_velocity_chance);
		i_wall = (i_wall + 1) % max_wall;
		++n_wall;

		clock_wall.restart();
	}

	player->setSpritePosition();

	for (size_t i = 0; i < max_shots; ++i) {
		if (!shot[i].isValid()) {
			continue;
		}
		shot[i].setSpritePosition();
	}

	for (size_t i = 0; i < max_monsters; ++i) {
		if (!monster[i].isValid()) {
			continue;
		}
		monster[i].setSpritePosition();
	}

	for (size_t i = 0; i < max_wall; ++i) {
		if (!wall[i].isValid()) {
			continue;
		}
		wall[i].setSpritePosition();
	}

	verifyOutOfBounds();
	verifyCollisions();
}

void Game::Update(sf::Time& timePerFrame)
{
	player->update(timePerFrame);

	for (size_t i = 0; i < max_shots; ++i) {
		if (!shot[i].isValid()) {
			continue;
		}
		shot[i].update(timePerFrame);
	}

	for (size_t i = 0; i < max_monsters; ++i) {
		if (!monster[i].isValid()) {
			continue;
		}
		monster[i].update(timePerFrame);
	}

	for (size_t i = 0; i < max_wall; ++i) {
		if (!wall[i].isValid()) {
			continue;
		}
		wall[i].update(timePerFrame);
	}

	life->update(timePerFrame);
	score->update(timePerFrame);
}

void Game::Draw()
{
	map->draw(*main_window);
	player->draw(*main_window);

	for (size_t i = 0; i < max_shots; ++i) {
		if (!shot[i].isValid()) {
			continue;
		}

		shot[i].draw(*main_window);
	}

	for (size_t i = 0; i < max_monsters; ++i) {
		if (!monster[i].isValid()) {
			continue;
		}

		monster[i].draw(*main_window);
	}

	for (size_t i = 0; i < max_wall; ++i) {
		if (!wall[i].isValid()) {
			continue;
		}

		wall[i].draw(*main_window);
	}

	life->draw(*main_window);
	score->draw(*main_window);

	main_window->display();
}

void Game::Clean()
{
	main_window->clear();
}

bool Game::Running()
{
	return m_bRunning;
}

bool Game::Opened()
{
	return m_bOpened;
}

void Game::verifyCollisions()
{
	for (size_t i = 0; i < max_monsters; ++i) {
		if (!monster[i].isValid()) {
			continue;
		}

		for (size_t j = 0; j < max_shots; ++j) {
			if (!shot[j].isValid()) {
				continue;
			}

			if (monster[i].intersects(shot[j])) {
				monster[i].setInvalid();
				shot[j].setInvalid();
				--n_monster;
				--n_shot;

				score->increaseBy(50);

				break;
			}
		}
	}

	if (clock_player.getElapsedTime().asMilliseconds() > delay_player) {
		for (size_t i = 0; i < max_monsters; ++i) {
			if (!monster[i].isValid()) {
				continue;
			}

			if (monster[i].intersects(*player)) {
				life->decrease();
				clock_player.restart();
			}
		}
	}
}

void Game::verifyOutOfBounds()
{
	for (size_t i = 0; i < max_shots; ++i) {
		if (shot[i].isValid() && shot[i].getY() < min_y) {
			shot[i].setInvalid();
			--n_shot;
		}
	}

	for (size_t i = 0; i < max_monsters; ++i) {
		if (monster[i].isValid() && monster[i].getY() > max_y) {
			monster[i].setInvalid();
			--n_monster;
		}
	}

	for (size_t i = 0; i < max_wall; ++i) {
		if (wall[i].isValid() && wall[i].getY() > max_y) {
			wall[i].setInvalid();
			--n_wall;
		}
	}
}
