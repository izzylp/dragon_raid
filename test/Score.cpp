#include "../../Catch-master/include/catch.hpp"

#include "../src/Score.hpp"

TEST_CASE("Score logic", "[score]")
{
	Score score(1000, 50000);

	SECTION("initialization test") {
		REQUIRE(score.getScore() == 1000);
	}

	SECTION("increase score test") {
		score.increaseBy(50);
		score.increaseBy(50);
		REQUIRE(score.getScore() == 1100);
	}

	SECTION("increase score test past maxScore") {
		score.increaseBy(50000);
		REQUIRE(score.getScore() == 50000);
	}

	SECTION("decrease life test") {
		score.increaseBy(-50);
		REQUIRE(score.getScore() == 950);
	}

	SECTION("decrease score test past minScore") {
		score.increaseBy(-50000);
		REQUIRE(score.getScore() == 0);
	}
}
