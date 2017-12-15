#include "../../Catch-master/include/catch.hpp"

#include "../src/Player.hpp"

TEST_CASE("Player logic", "[player]")
{
	Player player;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	float velocity = 100;

	SECTION("move object left") {
		player.setPosition(15, 10, 15, 20, 30, 50);
		player.setVelocity(velocity);
		float x = player.getX();
		player.moveLeft(timePerFrame);
		REQUIRE((x - timePerFrame.asSeconds() * velocity) == player.getX());
	}

	SECTION("move object right") {
		player.setPosition(15, 10, 15, 20, 30, 50);
		player.setVelocity(velocity);
		float x = player.getX();
		player.moveRight(timePerFrame);
		REQUIRE((x + timePerFrame.asSeconds() * velocity) == player.getX());
	}
}
