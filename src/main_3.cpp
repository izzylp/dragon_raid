// This example demostrates the main loop

#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <iostream>
#include <list>

int main(int argc, char ** argv) {
	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "SFML Demo");

	sf::Event event;

	renderWindow.setKeyRepeatEnabled(false);

	std::unordered_map<int, bool> keys;
	std::list<int> changedKeys;

	while (renderWindow.isOpen()){
		changedKeys.clear();

		while (renderWindow.pollEvent(event)){
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();

			if (event.type == sf::Event::EventType::KeyPressed){
				if (keys.count(event.key.code) == 0){
					keys[event.key.code] = true;
					changedKeys.push_back(event.key.code);
				}
			}
			if (event.type == sf::Event::EventType::KeyReleased){
				if (keys.count(event.key.code) == 1){
					keys.erase(event.key.code);
					changedKeys.push_back(event.key.code);
				}
			}
		}

		std::cout << "Currently pressed keys: ";

		// To get the actual value as a string, you need to use Thor or write your own version
		for (auto& keyValue : keys)
			std::cout << keyValue.first << " ";
		std::cout << std::endl;

		if (!changedKeys.empty()){
			std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Keys changed" << std::endl;
		}
		renderWindow.clear();
		renderWindow.display();
	}

}
