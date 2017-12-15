#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include <unordered_map>
#include <list>
#include "SFML/Graphics.hpp"
#include "Game.hpp"

int main(int argc, char* argv[])
{
	Game game;

	sf::Time timePerFrame;
	sf::Time timeSinceLastUpdate;
	sf::Clock deltaClock;

	timePerFrame = sf::seconds(1.0f / 60.0f);
	timeSinceLastUpdate = sf::Time::Zero;

	game.Init("Dragon Raid", 640, 480, 32, false);

	while (game.Running()) {
		sf::Time deltaTime = deltaClock.restart();
		timeSinceLastUpdate += deltaTime;

		while (timeSinceLastUpdate >= timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;

			game.Clean();
			game.HandleEvents(timePerFrame);
			game.Update(timePerFrame);
		}
		game.Draw();
	}

	while (game.Opened()) {
		sf::Time deltaTime = deltaClock.restart();
		timeSinceLastUpdate += deltaTime;

		while (timeSinceLastUpdate >= timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;

			game.HandleEvents(timePerFrame);
		}
	}

	return 0;
}
