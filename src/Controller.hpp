#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include <unordered_map>
#include <list>

#include "SFML/Graphics.hpp"

const char LEFT_ARROW = 71;
const char RIGHT_ARROW = 72;
const char Q = 16;

class Controller
{
public:
	Controller();

	~Controller();

	void clear();

	bool checkAndHandleEvents(sf::RenderWindow& _main_window, sf::Event& _event);

	bool isKeyPressed(char _key);

private:

	std::unordered_map<int, bool> keys;
	std::list<int> changed_keys;
};

#endif
