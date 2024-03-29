#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include "DatabaseRAII.h"
#include "RandomNumbers.h"

class AutogramGenerator
{
public:
	AutogramGenerator();
private:
	int language;
	const std::string DBPATH = "D:/GitHub/cpp-autogram/Cpp_Autogram/Data/numerals.db";
	const int START_ASCII = 97;
	const int END_ASCII = 122;
	std::vector<char> alphabet;

	DatabaseRAII database { DBPATH };

	void generateAlphabet();
	void start();
	std::string askInput();
	std::string solveAutogram(const std::string& input);
	std::string writeSentence(const std::vector<std::string>& countNumbers, const std::string& input) const;
	std::map<char, int> countLetters(const std::string& sentence) const;
	void evaluateCountNumbers(const std::vector<int>& values, std::vector<std::string>& countNumbers);
	void chooseLanguage(int input);
};

