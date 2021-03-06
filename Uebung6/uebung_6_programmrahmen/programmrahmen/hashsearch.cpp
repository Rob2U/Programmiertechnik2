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

    //subtract the character leaving the window
    hash = (hash - (primePow*leavingChar)%hashTableMagnitude);

    //multiply by prime currenthash in order to move the window to the right
    hash = (hash*prime)%hashTableMagnitude;

    if (hash<0)
        hash += hashTableMagnitude;

    hash = (hash + (enteringChar))%hashTableMagnitude;

    return hash;
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

    for (int i = 0; i < patternLength-1; i++) {
        primePow = (primePow * prime) % hashTableMagnitude;
    }


    // TODO: Compute patternHash, the hash value of the pattern and the first
    //       substringHash.
    int64_t patternHash = 0;
    int64_t substringHash = 0;

    for (int i = 0; i < patternLength; i++) {
        const char& c = pattern.at(i);
        int64_t ppow = 1;
        for (int j = 0; j < patternLength-i-1; j++) {
            ppow = (ppow * prime) % hashTableMagnitude;
        }

        patternHash += ((c)%hashTableMagnitude * (ppow)) % hashTableMagnitude;

        auto c2 = text.at(i);
        substringHash += ((c2)%hashTableMagnitude * (ppow)) % hashTableMagnitude;
    }
    substringHash %= hashTableMagnitude;
    patternHash %= hashTableMagnitude;



    // TODO: Compare each individual substring's hash with patternHash and push
    //       all found occurrences to the positions vector.
    //       Compute the next substringHash if needed.

    std::vector<size_t> positions;

    int counter = 0;
    while(counter+patternLength < textLength) {

        //if hashes match and hashcollision is excluded add position to positions
        if (substringHash==patternHash && !pattern.compare(text.substr(counter, patternLength)))
            positions.push_back(counter);

        //calculate new hash for text substr
        counter++;
        substringHash = nextHash(substringHash, primePow, text.at(counter-1), text.at(counter+patternLength-1));
    }


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
    const auto texts = loadTexts("/home/robwee/CLionProjects/datenbanksysteme/loremipsum.txt");
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
