#include "SFML/Graphics.hpp"
#include <iostream>

int main(int argc, char ** argv) {
	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "SFML Demo");

	sf::Event event;

	// A Clock starts counting as soon as it's created
	sf::Clock clock;

	while(renderWindow.isOpen()){
		// Check for all the events that occured since the last frame.
		while (renderWindow.pollEvent(event)){
			//Handle events here
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}

		// A microsecond is 1/1,000,000th of a second, 1000 microseconds == 1 millisecond
		std::cout << "Elapsed time since previous frame(microseconds): " << clock.getElapsedTime().asMicroseconds() << std::endl;
		// Start the countdown over.  Think of laps on a stop watch.
		clock.restart();


		renderWindow.clear();
		renderWindow.display();
	}

}
