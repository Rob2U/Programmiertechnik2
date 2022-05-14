#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int modulo(const std::string& a, int b)
{
	// Function to compute a (mod b)
	// YOUR CODE goes here. Don't forget to answer the question in a comment
	return -1;
}

bool isCheckDigitCorrect(const std::string& testString)
{
	return true;
}

bool isValueCorrect(const std::string& teststring, const int& column)
{
	std::regex regExp;

	switch (column)
	{
		// TODO: implement cases for other columns

		default:
			return false;
	}

	return std::regex_match(teststring, regExp);
}

void readTokensAndLines(char* path)
{
	std::ifstream file(path);
	std::string parsed;
	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream linestream;
		linestream.str(line);

		// TODO: - Split line and write result to std::cout
		//       - Check each part of line with isValueCorrect and log if values are not supported
		//       - Use and extend isValueCorrect and isCheckDigitCorrect function for this
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "not enough arguments - USAGE: fileio [DATASET]\n";
		return -1; // invalid number of parameters
	}

	std::cout << "Given path to persons.dat: " << argv[1] << "\n";

	readTokensAndLines(argv[1]);
	std::cout << modulo("4152523526252528027853958240132131", 97) << "\n"; //expected result is 42

	return 0;
}
