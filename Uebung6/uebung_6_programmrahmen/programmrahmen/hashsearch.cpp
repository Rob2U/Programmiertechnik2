#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int64_t prime = 293; // Prime close to the magnitude of the alphabet
constexpr int64_t hashTableMagnitude = 1000000009;

int64_t nextHash(int64_t hash, int64_t primePow, char leavingChar, char enteringChar)
{
	// TODO: Compute next rolling hash based on previous hash, primePow, the
	//       character "leaving" the search window and the character
	//       "entering" the search window.

	return 0;
}

std::vector<size_t> search(const std::string& pattern, const std::string& text)
{
	const size_t patternLength = pattern.length();
	const size_t textLength = text.length();

	if (textLength < patternLength)
	{
		return {};
	}

	// TODO: Compute primePow = prime ^ patternLength (modulo hashTableMagnitude).
	//       keep in mind to apply modulo after each operation.
	//       Hint: you can't simply use std::pow because of that.
	int64_t primePow = 1;

	// TODO: Compute patternHash, the hash value of the pattern and the first
	//       substringHash.
	int64_t patternHash = 0;
	int64_t substringHash = 0;

	// TODO: Compare each individual substring's hash with patternHash and push
	//       all found occurrences to the positions vector.
	//       Compute the next substringHash if needed.
	std::vector<size_t> positions;

	return positions;
}

std::vector<std::string> loadTexts(const std::string& filepath)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit);
	try
	{
		file.open(filepath);
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << R"(Could not open file (")" << filepath << R"("): )" << std::strerror(errno)
				  << std::endl;
		return {};
	}
	file.exceptions(std::ifstream::goodbit);

	std::string line;
	std::vector<std::string> lines;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}
	return lines;
}

int main()
{
	const auto texts = loadTexts("loremipsum.txt");
	const std::string pattern = "ipsum";

	std::cout << R"(Searching for ")" << pattern << R"(")" << '\n';

	std::cout << "Found at positions:\n";
	size_t counter = 0;
	for (size_t lineNumber = 0; lineNumber < texts.size(); ++lineNumber)
	{
		for (size_t linePos : search(pattern, texts[lineNumber]))
		{
			std::cout << "  " << lineNumber << ", " << linePos << '\n';
			counter++;
		}
	}
	std::cout << '\n';
	std::cout << "Number of occurences: " << counter << '\n'; // Expected occurences of "ipsum": 57
	return 0;
}
