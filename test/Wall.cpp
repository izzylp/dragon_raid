#include "../../Catch-master/include/catch.hpp"

#include "../src/Wall.hpp"
#include "SFML/Graphics.hpp"

TEST_CASE("Wall", "[wall]")
{
	Wall wall;
	Wall dummy;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	float velocity = 100;

	SECTION("set position") {
		wall.setPosition(5, 10, 15, 20, 30, 50);
		REQUIRE(!wall.isValid());
	}

	SECTION("set position and validity") {
		wall.setValid();
		REQUIRE(wall.isValid());
	}

	SECTION("set position and !validity") {
		wall.setInvalid();
		REQUIRE(!wall.isValid());
	}

	SECTION("move object left") {
		wall.setPosition(15, 10, 15, 20, 30, 50);
		wall.setVelocity(velocity);
		float x = wall.getX();
		wall.moveLeft(timePerFrame);
		REQUIRE((x - timePerFrame.asSeconds() * velocity) == wall.getX());
	}

	SECTION("move object right") {
		wall.setPosition(15, 10, 15, 20, 30, 50);
		wall.setVelocity(velocity);
		float x = wall.getX();
		wall.moveRight(timePerFrame);
		REQUIRE((x + timePerFrame.asSeconds() * velocity) == wall.getX());
	}

	SECTION("intersection") {
		wall.setPosition(15, 10, 15, 20, 30, 50);
		dummy.setPosition(15, 10, 15, 20, 30, 50);
		REQUIRE(wall.intersects(dummy));
	}

	SECTION("not intersection") {
		wall.setPosition(15, 10, 15, 20, 30, 50);
		dummy.setPosition(140, 150, 15, 20, 30, 50);
		REQUIRE(!wall.intersects(dummy));
	}
}
