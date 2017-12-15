#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include <unordered_map>
#include <list>

#include "SFML/Graphics.hpp"

#include "player.hpp"

std::string img = "img/player.png";
const int img_x = 512;
const int img_y = 128;
const int img_nx = 4;
const int img_ny = 1;
const float time_frame = 0.2f;

int main(int argc, char* argv[])
{
	sf::Event event;
	sf::Texture texture;
	texture.loadFromFile(img);

	sf::IntRect rectSourceSprite(0, 0, img_x / img_nx, img_y / img_ny);
	sf::Sprite sprite(texture, rectSourceSprite);
	sf::Clock clock;

	sf::RenderWindow mainWindow(sf::VideoMode(640, 480), "Demo Game");
	std::unordered_map<int, bool> keys;
	std::list<int> changedKeys;

	mainWindow.setKeyRepeatEnabled(false);

	float x_player = 100;
	float y_player = 350;
	sprite.setPosition(x_player, y_player);

	while (mainWindow.isOpen()) {
		changedKeys.clear();

		while (mainWindow.pollEvent(event)){
			if (event.type == sf::Event::EventType::Closed) {
				mainWindow.close();
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

		std::cout << "Currently pressed keys: ";

		// To get the actual value as a string, you need to use Thor or write your own version
		for (auto& keyValue : keys) {
			std::cout << keyValue.first << " ";
			if (keyValue.first == 71) {
				x_player -= 0.08;
			}

			if (keyValue.first == 72) {
				x_player += 0.08;
			}

			if (x_player > 500) {
				x_player = 500;
			}

			if (x_player < 100) {
				x_player = 100;
			}

			sprite.setPosition(x_player, y_player);
		}
		std::cout << std::endl;

		if (!changedKeys.empty()) {
			std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Keys changed" << std::endl;
		}

		if (clock.getElapsedTime().asSeconds() > time_frame) {


			rectSourceSprite.left += img_x / img_nx;

			if (rectSourceSprite.left >= img_x) {
				rectSourceSprite.left = 0;
				rectSourceSprite.top += img_y / img_ny;
			}

			if (rectSourceSprite.top >= img_y) {
				rectSourceSprite.top = 0;
			}

			sprite.setTextureRect(rectSourceSprite);
			clock.restart();
		}

		mainWindow.clear();
		mainWindow.draw(sprite);
		mainWindow.display();
	}

	return 0;
}
