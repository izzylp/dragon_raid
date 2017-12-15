#include "../../Catch-master/include/catch.hpp"

#include "../src/Life.hpp"

TEST_CASE("Life logic", "[life]")
{
	Life life(3, 5);

	SECTION("initialization test") {
		REQUIRE(life.getLife() == 3);
	}

	SECTION("increase life test") {
		life.increase();
		life.increase();
		REQUIRE(life.getLife() == 5);
	}

	SECTION("increase life test past maxLife") {
		life.increase();
		life.increase();
		life.increase();
		REQUIRE(life.getLife() == 5);
	}

	SECTION("decrease life test") {
		life.decrease();
		REQUIRE(life.getLife() == 2);
	}

	SECTION("decrease life test past minLife") {
		life.decrease();
		life.decrease();
		life.decrease();
		life.decrease();
		REQUIRE(life.getLife() == 0);
	}
}
