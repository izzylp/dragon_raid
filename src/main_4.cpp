#include "SFML/Graphics.hpp"

std::string img = "img/dragon_frames_3.png";
const int img_x = 512;
const int img_y = 128;
const int img_nx = 4;
const int img_ny = 1;
const float time_frame = 0.2f;

int main(int argc, char ** argv){
	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Demo Game");

	sf::Event event;
	sf::Texture texture;
	texture.loadFromFile(img);

	sf::IntRect rectSourceSprite(0, 0, img_x / img_nx, img_y / img_ny);
	sf::Sprite sprite(texture, rectSourceSprite);
	sprite.setPosition(10, 100);
	sf::Clock clock;

	while (renderWindow.isOpen()){
		while (renderWindow.pollEvent(event)){
			if (event.type == sf::Event::EventType::Closed) {
				renderWindow.close();
			}
		}

		if (clock.getElapsedTime().asSeconds() > time_frame){
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


		renderWindow.clear();
		renderWindow.draw(sprite);
		renderWindow.display();
	}
}
