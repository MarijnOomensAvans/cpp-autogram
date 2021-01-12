#include "AutogramGenerator.h"

AutogramGenerator::AutogramGenerator()
{
	generateAlphabet();
	start();
}

AutogramGenerator::~AutogramGenerator()
{
}

void AutogramGenerator::generateAlphabet()
{
	for (size_t i = START_ASCII; i <= END_ASCII; ++i)
	{
		alphabet.emplace_back((char)i);
	}
}

void AutogramGenerator::start()
{
	bool exit = false;
	while (!exit)
	{
		std::string input = askInput();
		std::string result = solveAutogram(input);
		std::cout << result << std::endl;
	}
}


std::string AutogramGenerator::askInput()
{
	std::cout << "Welcome to the CPP2 Autogram generator made by Marijn Oomens! \n" << std::endl;
	std::cout << "Please type the base sentence of you autogram and press ENTER: \n" << std::endl;
	std::string input = "";
	std::getline(std::cin, input);
	std::cout << "\nYour chosen base sentence: \n" << std::endl;
	std::cout << input + "\n \n" << std::endl;
	std::cout << "Autogram generated from base sentence: \n" << std::endl;
	return input;
}

std::string AutogramGenerator::solveAutogram(const std::string& input)
{
	std::vector<std::string> countNumbers;

	std::vector<int> countNumberValues = RandomNumbers::getInstance().getRandomNumbers(1, 200, alphabet.size());

	for (size_t i = 0; i < countNumberValues.size(); i++)
	{
		countNumbers.emplace_back(database.getNumeral(countNumberValues[i]));
	}

	std::string seed = writeSentence(countNumbers, input);

	std::map<char, int> letterCounts = startCount(seed);

	countNumberValues.clear();
	for (const auto& letter : letterCounts)
	{
		countNumberValues.emplace_back(letter.second);
	}

	std::vector<std::string> previousEvaluation;
	for (size_t i = 0; i < 20; ++i)
	{
		std::vector<std::string> evaluation = evaluateCountNumbers(countNumberValues);
		if (previousEvaluation.size() > 0)
		{
			bool correct = false;
			for (size_t j = 0; j < evaluation.size(); ++j)
			{
				if (evaluation[j] != previousEvaluation[j])
				{
					previousEvaluation = evaluation;
				}
				else {
					correct = true;
				}
			}

			if (correct)
			{
				return writeSentence(evaluation, input);
			}
		}
		std::map<char, int> letterCounts2 = startCount(writeSentence(evaluation, input));

		countNumberValues.clear();
		for (const auto& letter : letterCounts2)
		{
			countNumberValues.emplace_back(letter.second);
		}
		previousEvaluation = evaluateCountNumbers(countNumberValues);
	}

	return seed;
}

std::string AutogramGenerator::writeSentence(std::vector<std::string> countNumbers, const std::string& input)
{
	std::stringstream resultStream;

	resultStream << input + " ";

	for (size_t i = 0; i < countNumbers.size(); ++i)
	{
		if (i == (countNumbers.size() - 1)) {
			resultStream << "en " + countNumbers[i] + " " + alphabet[i] + "'s.";
		}
		else {
			resultStream << countNumbers[i] + " " + alphabet[i] + "'s, ";
		}
	}

	return resultStream.str();
}

std::map<char, int> AutogramGenerator::startCount(const std::string& sentence)
{
	std::map<char, int> letterCounts;
	for (const auto& letter : alphabet)
	{
		letterCounts.try_emplace(letter);
	}

	for (auto& letter : letterCounts)
	{
		for (size_t j = 0; j < sentence.size(); j++)
		{
			if (sentence[j] == letter.first)
			{
				letter.second++;
			}
		}
	}

	return letterCounts;
}

std::vector<std::string> AutogramGenerator::evaluateCountNumbers(std::vector<int> values)
{
	std::vector<std::string> countNumbers;
	for (size_t i = 0; i < values.size(); i++)
	{
		countNumbers.emplace_back(database.getNumeral(values[i]));
	}
	return countNumbers;
}
