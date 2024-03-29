#include "AutogramGenerator.h"

AutogramGenerator::AutogramGenerator()
{
	generateAlphabet();
	start();
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
		std::cout << result + "\n" << std::endl;
	}
}


std::string AutogramGenerator::askInput()
{
	std::cout << "Welcome to the CPP2 Autogram generator made by Marijn Oomens! \n" << std::endl;
	std::cout << "Please select your language first, type 1 for Dutch or 2 for English, then press ENTER \n" << std::endl;
	std::string lang;
	std::getline(std::cin, lang);
	chooseLanguage(std::stoi(lang));
	std::cout << "Please type the base sentence of you autogram and press ENTER: \n" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::cout << "\nYour chosen base sentence: \n" << std::endl;
	std::cout << input + "\n \n" << std::endl;
	std::cout << "Autogram generated from base sentence: \n" << std::endl;
	return input;
}

std::string AutogramGenerator::solveAutogram(const std::string& input)
{
	std::vector<std::string> countNumbers;
	std::vector<int> countNumberValues;
	std::string seed;
	std::map<char, int> letterCounts;
	std::map<char, int> previousCount;
	for (size_t t = 0; t < 75; ++t) {
		// Generate random numbers and write seed


		countNumberValues = RandomNumbers::getInstance().getRandomNumbers(1, 200, alphabet.size());

		evaluateCountNumbers(countNumberValues, countNumbers);

		seed = writeSentence(countNumbers, input);

		// ------------------------------------------------------------------------------------------------------------------

		for (size_t i = 0; i < 15; ++i)
		{
			letterCounts = countLetters(seed);

			countNumberValues.clear();
			for (const auto& letter : letterCounts)
			{
				countNumberValues.emplace_back(letter.second);
			}

			evaluateCountNumbers(countNumberValues, countNumbers);

			seed = writeSentence(countNumbers, input);

			if (previousCount.size() > 0)
			{
				bool correct = true;
				for (int i = START_ASCII; i <= END_ASCII; ++i)
				{
					if (letterCounts[i] != previousCount[i])
					{
						correct = false;
					}
				}

				if (correct)
				{
					return seed;
				}
			}
			previousCount = letterCounts;
		}
	}
	return seed;
}

std::string AutogramGenerator::writeSentence(const std::vector<std::string>& countNumbers, const std::string& input) const
{
	std::stringstream resultStream;

	resultStream << input + " ";

	for (size_t i = 0; i < countNumbers.size(); ++i)
	{
		if (countNumbers[i] == "een" || countNumbers[i] == "one")
		{
			if (i == (countNumbers.size() - 1)) {
				resultStream << "& " + countNumbers[i] + " " + alphabet[i] + ".";
			}
			else {
				resultStream << countNumbers[i] + " " + alphabet[i] + ", ";
			}
		}
		else {
			if (i == (countNumbers.size() - 1)) {
				resultStream << "& " + countNumbers[i] + " " + alphabet[i] + "'s.";
			}
			else {
				resultStream << countNumbers[i] + " " + alphabet[i] + "'s, ";
			}
		}
	}

	return resultStream.str();
}

std::map<char, int> AutogramGenerator::countLetters(const std::string& sentence) const
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

void AutogramGenerator::evaluateCountNumbers(const std::vector<int>& values, std::vector<std::string>& countNumbers)
{
	countNumbers.clear();
	for (size_t i = 0; i < values.size(); i++)
	{
		countNumbers.emplace_back(database.getNumeral(values[i], language));
	}
}

void AutogramGenerator::chooseLanguage(int input)
{
	try
	{
		if (input == 1)
		{
			language = input;
			std::cout << "Autogram language set to Dutch \n" << std::endl;
		}
		else if(input == 2) {
			language = input;
			std::cout << "Autogram language set to English \n" << std::endl;
		}
		else {
			throw std::runtime_error("Wrong input for language, defaulting to English \n");
			language = 0;
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << '\n';
	}
}
