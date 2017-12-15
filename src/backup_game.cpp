#include "game.hpp"

#include <chrono>
#include <random>

static const char LEFT_ARROW = 71;
static const char RIGHT_ARROW = 72;
static const char Q = 16;

Game::Game() : delay_shot(80), delay_monster(80)
{
}

Game::~Game()
{
	delete player;
	delete[] shot;
	delete[] monster;
}

void Game::Init(const std::string title, int _width, int _height, int bpp, bool fullscreen)
{
	width = _width;
	height = _height;

	min_x = 100; //TODO
	max_x = 500; //TODO
	min_y = 0;
	max_y = 480;

	main_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	main_window->setKeyRepeatEnabled(false);

	player = new Player(width / 2, height / 2 + height * 0.2, min_x, max_x);
	player->setSpritePosition();

	max_shots = 1000;
	n_shot = 0;
	i_shot = 0;
	shot = new Shot[max_shots];

	max_monsters = 100;
	n_monster = 0;
	i_monster = 0;
	monster = new Monster[max_monsters];

	m_bRunning = true;
}

void Game::HandleEvents(sf::Time& timePerFrame)
{
	sf::Event event;
	changedKeys.clear();

	auto start1 = std::chrono::steady_clock::now();
	if (main_window->pollEvent(event)){
		if (event.type == sf::Event::EventType::Closed) {
			main_window->close();
			m_bRunning = false;
		}

		if (event.type == sf::Event::EventType::KeyPressed){
			if (keys.count(event.key.code) == 0) {
				keys[event.key.code] = true;
				changedKeys.push_back(event.key.code);
			}
		}
		if (event.type == sf::Event::EventType::KeyReleased){
			if (keys.count(event.key.code) == 1) {
				keys.erase(event.key.code);
				changedKeys.push_back(event.key.code);
			}
		}
	}

	auto end1 = std::chrono::steady_clock::now();
	auto diff1 = end1 - start1;

	//std::cout << i_shot << std::endl;

	// To get the actual value as a string, you need to use Thor or write your own version
	auto start2 = std::chrono::steady_clock::now();

	for (auto& keyValue : keys) {
		//std::cout << keyValue.first << " ";
		if (keyValue.first == LEFT_ARROW) {
			player->setX(player->getX() - width / 2 * timePerFrame.asSeconds());
		}

		if (keyValue.first == RIGHT_ARROW) {
			player->setX(player->getX() + width / 2 * timePerFrame.asSeconds());
		}

		if (clock_shot.getElapsedTime().asMilliseconds() > delay_shot && keyValue.first == Q && n_shot < max_shots) {
			while (shot[i_shot].isValid()) {
				i_shot = (i_shot + 1) % max_shots;
			}
			shot[i_shot].setPosition(player->getX() + player->getWidth() / 2 - shot[i_shot].getWidth() / 2, player->getY(), min_x, max_x, min_y, max_y);
			i_shot = (i_shot + 1) % max_shots;
			++n_shot;

			clock_shot.restart();
		}

	}

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni_chance(0, 100);
	auto chance = uni_chance(rng);

	if (chance < 20 && clock_monster.getElapsedTime().asMilliseconds() > delay_monster && n_monster < max_monsters) {
	//if (chance < 101 && clock_monster.getElapsedTime().asMilliseconds() > delay_monster && n_monster < max_monsters) {
		std::uniform_int_distribution<int> uni_y(min_x, max_x);
		auto random_y = uni_y(rng);
		while (monster[i_monster].isValid()) {
			i_monster = (i_monster + 1) % max_monsters;
		}
		monster[i_monster].setPosition(random_y, 0, min_x, max_x, min_y, max_y);
		//monster[i_monster].setPosition(300, 0, min_x, max_x, min_y, max_y);
		i_monster = (i_monster + 1) % max_monsters;
		++n_monster;

		clock_monster.restart();
	}

	auto end2 = std::chrono::steady_clock::now();
	auto diff2 = end2 - start2;

	auto start3 = std::chrono::steady_clock::now();
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

	verifyCollisions();
	verifyOutOfBounds();
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
}

void Game::Draw()
{
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

void Game::verifyCollisions()
{
	for (size_t i = 0; i < max_monsters; ++i) {
		if (!monster[i].isValid()) {
			continue;
		}

		sf::IntRect rect_monster(monster[i].getX(), monster[i].getY(), monster[i].getWidth(), monster[i].getHeight());

		for (size_t j = 0; j < max_shots; ++j) {
			if (!shot[j].isValid()) {
				continue;
			}

			sf::IntRect rect_shot(shot[j].getX(), shot[j].getY(), shot[j].getWidth(), shot[j].getHeight());

			if (rect_monster.intersects(rect_shot)) {
				monster[i].setValid(0);
				shot[j].setValid(0);
				--n_monster;
				--n_shot;
			}
		}
	}
}

void Game::verifyOutOfBounds()
{
	/* TODO: Could be reworked */
	for (size_t i = 0; i < max_shots; ++i) {
		if (shot[i].isValid() && shot[i].getY() < min_y) {
			shot[i].setValid(0);
			--n_shot;
		}
	}

	/* TODO: Could be reworked */
	for (size_t i = 0; i < max_monsters; ++i) {
		if (monster[i].isValid() && monster[i].getY() > max_y) {
			monster[i].setValid(0);
			--n_monster;
		}
	}
}
