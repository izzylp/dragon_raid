#include "../../Catch-master/include/catch.hpp"

#include "../src/Shot.hpp"
#include "SFML/Graphics.hpp"

TEST_CASE("Shot", "[shot]")
{
	Shot shot;
	Shot dummy;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	float velocity = 100;

	SECTION("set position") {
		shot.setPosition(5, 10, 15, 20, 30, 50);
		REQUIRE(!shot.isValid());
	}

	SECTION("set position and validity") {
		shot.setValid();
		REQUIRE(shot.isValid());
	}

	SECTION("set position and !validity") {
		shot.setInvalid();
		REQUIRE(!shot.isValid());
	}

	SECTION("move object left") {
		shot.setPosition(15, 10, 15, 20, 30, 50);
		shot.setVelocity(velocity);
		float x = shot.getX();
		shot.moveLeft(timePerFrame);
		REQUIRE((x - timePerFrame.asSeconds() * velocity) == shot.getX());
	}

	SECTION("move object right") {
		shot.setPosition(15, 10, 15, 20, 30, 50);
		shot.setVelocity(velocity);
		float x = shot.getX();
		shot.moveRight(timePerFrame);
		REQUIRE((x + timePerFrame.asSeconds() * velocity) == shot.getX());
	}

	SECTION("intersection") {
		shot.setPosition(15, 10, 15, 20, 30, 50);
		dummy.setPosition(15, 10, 15, 20, 30, 50);
		REQUIRE(shot.intersects(dummy));
	}

	SECTION("not intersection") {
		shot.setPosition(15, 10, 15, 20, 30, 50);
		dummy.setPosition(40, 50, 15, 20, 30, 50);
		REQUIRE(!shot.intersects(dummy));
	}
}
