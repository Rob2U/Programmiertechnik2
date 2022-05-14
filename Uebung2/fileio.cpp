#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int modulo(const std::string& a, int b)
{
	// Function to compute a (mod b)
	// YOUR CODE goes here. Don't forget to answer the question in a comment
	// das Problem bei der Berechnung von modulo auf der IBAN ist, dass die durch Umwandlung in eine natuerliche Zahl entstehende Zahl zu gross waere um die Zahl in einem datntyp zu speichern.
	// Daher wird die Zahl in einen String umgewandelt, damit wird schriftliche Division mit rest durchgefuehrt und dieser Rest ist dann die entstehende Pruefziffer.

	//calculate the modulo of a and b on the basis of the string a
	std::stringstream ss;
	ss << a;
	int currentVal = 0;
	std::string current = "0";

	while (current += ss.get(), !ss.eof())
	{
		currentVal = std::stoi(current);
		current = std::to_string(currentVal%b);
	}
	return std::stoi(current);
}

bool isCheckDigitCorrect(const std::string& testString)
{
	if (testString.length() < 5){
		return false;
	}

	int checkDigits = std::stoi(testString.substr(2,2));
	int checkNumbers = (testString.c_str()[0]-55)*100 + (testString.c_str()[1]-55);

	std::string parsed = std::to_string(checkNumbers) +  testString.substr(2,testString.length()-2);

	
	long parsedNum = std::stoi(parsed.substr(parsed.length()-2,2));
	//std::cerr << "Test" << std::endl;

	//std::cout << "Prüfziffer: \t" << checkDigits << "\t Prüfbuchstaben\t" << checkNumbers << std::endl;
	return (parsedNum%100 == checkDigits) ? true : false;
}

bool isValueCorrect(const std::string& teststring, const int& column)
{
	std::regex regExp;

	switch (column)
	{
		// TODO: implement cases for other columns
		case 0:
		case 1:
			regExp.assign("[A-Z][a-z]{1,14}$");
			return std::regex_match(teststring, regExp);

		case 2:
			//regExp.assign("^[A-Z][A-Z]([A-Z]|[0-9]){16,35}( )*$");
			regExp.assign("[A-Z][A-Z][A-Z0-9]{16,32}( )*");
			
			return std::regex_match(teststring, regExp);
			return true;
		default:
			return false;
	}
	return false;
}


void readTokensAndLines(char* path)
{
	std::ifstream file(path);
	std::string parsed;
	std::string line;

	std::ofstream log("fileio.log");
	
	while (std::getline(file, line))
	{
		std::istringstream linestream;
		linestream.str(line);
		
		std::string curattr;
		int counter = 0;

		bool clearLine = false;
		int error = 0;
		std::string buffer = "";
		
		while (std::getline(linestream, curattr, ','))
		{
			switch (counter)
			{
			case 0:
				if (isValueCorrect(curattr, counter))
				{
					buffer.append(curattr +  " ");
				} else {
					buffer.append(curattr +  " ");
					error+=1;
					clearLine = true;
				}
				break;
			case 1:
				if (isValueCorrect(curattr, counter))
				{
					buffer.append(curattr + " - ") ;
				}else {
					buffer.append(curattr + " - ") ;
					error+= 2;
					clearLine = true;
				}
				break;
			case 2:
				//std::cout << "IBAN: " << curattr << std::endl;
				if (!isValueCorrect(curattr.substr(0,curattr.length()-1), counter))
				{
					clearLine = true;
					error+=4;
				}
				if (!isCheckDigitCorrect(curattr.substr(0,curattr.length()-1))){
					clearLine = true;
					error += 8;
				}


				for (int i = 0; i < curattr.length(); i++) {

					if (i%4 == 3 && i < curattr.length()-2){
						buffer += curattr.at(i);
						buffer += " ";
					}
					else {
						buffer += curattr.at(i);
					}
				}
				break;			
			}
			counter++;
		}

		if (clearLine) {
			if (1 & error)
				log << "ex01 ";
			if (2 & error)
				log << "ex02 ";
			if (4 & error)
				log << "ex03 ";  
			if (8 & error)
				log << "ex04 ";

			log << buffer << std::endl;
			//std::cout << buffer;
			//std::cout << " didnt match regex!" << std::endl;
		}
		else {
			std::cout << buffer << std::endl;
		}
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
	//std::cout << "Given path to persons.dat: " << argv[1] << "\n";

	readTokensAndLines(argv[1]);
	std::cout << modulo("4152523526252528027853958240132131", 97) << "\n"; //expected result is 42

	return 0;
}
