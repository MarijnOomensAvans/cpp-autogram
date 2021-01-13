#pragma once
#include <vector>
#include <iostream>
#include <random>

class RandomNumbers
{
public:
	static RandomNumbers& getInstance();
	std::vector<int> getRandomNumbers(int minRange, int maxRange, int amount) noexcept;
private:
	static RandomNumbers randomNumbers;

	std::random_device dev;
	std::default_random_engine dre { dev() };
};

