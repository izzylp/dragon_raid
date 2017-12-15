#include "Controller.hpp"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::clear()
{
	changed_keys.clear();
}

bool Controller::checkAndHandleEvents(sf::RenderWindow& _main_window, sf::Event& _event)
{
	bool m_bOpened = true;

	if (_main_window.pollEvent(_event)){
		if (_event.type == sf::Event::EventType::Closed) {
			_main_window.close();
			m_bOpened = false;
		}

		if (_event.type == sf::Event::EventType::KeyPressed){
			if (keys.count(_event.key.code) == 0) {
				keys[_event.key.code] = true;
				changed_keys.push_back(_event.key.code);
			}
		}
		if (_event.type == sf::Event::EventType::KeyReleased){
			if (keys.count(_event.key.code) == 1) {
				keys.erase(_event.key.code);
				changed_keys.push_back(_event.key.code);
			}
		}
	}

	return m_bOpened;
}

bool Controller::isKeyPressed(char _key)
{
	for (auto& keyValue : keys) {
		if (keyValue.first == _key) {
			return true;
		}
	}
}
