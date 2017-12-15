#include "../../Catch-master/include/catch.hpp"

#include "../src/Monster.hpp"
#include "SFML/Graphics.hpp"

TEST_CASE("Monster", "[monster]")
{
	Monster monster;
	Monster dummy;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	float velocity = 100;

	SECTION("set position") {
		monster.setPosition(5, 10, 15, 20, 30, 50);
		REQUIRE(!monster.isValid());
	}

	SECTION("set position and validity") {
		monster.setValid();
		REQUIRE(monster.isValid());
	}

	SECTION("set position and !validity") {
		monster.setInvalid();
		REQUIRE(!monster.isValid());
	}

	SECTION("move object left") {
		monster.setPosition(15, 10, 15, 20, 30, 50);
		monster.setVelocity(velocity);
		float x = monster.getX();
		monster.moveLeft(timePerFrame);
		REQUIRE((x - timePerFrame.asSeconds() * velocity) == monster.getX());
	}

	SECTION("move object right") {
		monster.setPosition(15, 10, 15, 20, 30, 50);
		monster.setVelocity(velocity);
		float x = monster.getX();
		monster.moveRight(timePerFrame);
		REQUIRE((x + timePerFrame.asSeconds() * velocity) == monster.getX());
	}

	SECTION("intersection") {
		monster.setPosition(15, 10, 15, 20, 30, 50);
		dummy.setPosition(15, 10, 15, 20, 30, 50);
		REQUIRE(monster.intersects(dummy));
	}

	SECTION("not intersection") {
		monster.setPosition(15, 10, 15, 20, 30, 50);
		dummy.setPosition(140, 150, 15, 20, 30, 50);
		REQUIRE(!monster.intersects(dummy));
	}
}
