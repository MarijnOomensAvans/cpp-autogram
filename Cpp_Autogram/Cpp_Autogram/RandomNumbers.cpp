#include "RandomNumbers.h"

RandomNumbers RandomNumbers::randomNumbers;

RandomNumbers& RandomNumbers::getInstance()
{
	return randomNumbers;
}

std::vector<int> RandomNumbers::getRandomNumbers(int minRange, int maxRange, int amount) noexcept
{
	std::vector<int> numbers;
	std::uniform_int_distribution<int> dist{ minRange, maxRange };
	for (int i{ 0 }; i < amount; ++i) {
		numbers.emplace_back(dist(dre));
	}
	return numbers;
}
