#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include <unordered_map>
#include <list>

#include "SFML/Graphics.hpp"

#include "game.hpp"
#include "player.hpp"
#include "monster.hpp"
#include "shot.hpp"

#include <chrono>

int main(int argc, char* argv[])
{
	Game game;

	game.Init("River Raid", 640, 480, 32, false);

	auto start = std::chrono::steady_clock::now();
	auto diff1 = start - start;
	auto diff2 = start - start;
	auto diff3 = start - start;
	auto diff4 = start - start;

	while (game.Running()) {
		auto start1 = std::chrono::steady_clock::now();
		game.Clean();
		auto end1 = std::chrono::steady_clock::now();
		auto start2 = std::chrono::steady_clock::now();
		game.HandleEvents();
		auto end2 = std::chrono::steady_clock::now();
		auto start3 = std::chrono::steady_clock::now();
		game.Update();
		auto end3 = std::chrono::steady_clock::now();
		auto start4 = std::chrono::steady_clock::now();
		game.Draw();
		auto end4 = std::chrono::steady_clock::now();

		diff1 += end1 - start1;
		diff2 += end2 - start2;
		diff3 += end3 - start3;
		diff4 += end4 - start4;
	}

	std::cout << "A " << std::chrono::duration <double, std::milli> (diff1).count() << " ms" << std::endl;
	std::cout << "B " << std::chrono::duration <double, std::milli> (diff2).count() << " ms" << std::endl;
	std::cout << "C " << std::chrono::duration <double, std::milli> (diff3).count() << " ms" << std::endl;
	std::cout << "D " << std::chrono::duration <double, std::milli> (diff4).count() << " ms" << std::endl;

	return 0;
}
