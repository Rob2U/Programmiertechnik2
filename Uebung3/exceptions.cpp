#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// transforms a string to a date. Throws a logic_error if year is *not* between 1893 and 2018
std::tm stringToTime(const std::string& date) {
	std::tm t{};
	std::istringstream ss(date);
	ss >> std::get_time(&t, "%Y%m%d");

	if (ss.fail() || t.tm_year < -7 || t.tm_year > 118)
	{
		throw std::logic_error("Year should be between 1893 and 2018");
	}

	return t;
}

class FormatException : public std::runtime_error {
	// Inherits all constructors of std::runtime_error
	using std::runtime_error::runtime_error;
};

void parseLine(const std::string& line, size_t lineNum) {
	const std::array<std::string, 4> fieldNames = { "Date", "Temperature", "Rainfall", "Unknown field" }; 

	// TODO 3.1b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by
	// calling std::stof. Catch all exceptions thrown by these methods. If there have been any exceptions,
	// aggregate all necessary information into an instance of FormatException and throw that instance.

	std::stringstream linestream(line);

	int cur_column=0;
	std::string cur_column_val;
	int err_code = 0;

	while (std::getline(linestream, cur_column_val, ';')) {

		//check if reading next column worked
		if(linestream.exceptions()){
			char* str;
			std::sprintf(str, "Line %d was not in the correct CSV Format!\n", (int)lineNum);
			throw new FormatException(std::string(str));
		}

		switch (cur_column++) {
		case 0:
			try {
				stringToTime(cur_column_val);
			}
			catch(...) {
				err_code += 1;
			}
			break;
		case 1:
			try {
				std::stof(cur_column_val);
			}catch(...){
				err_code += 2;
			}
			break;
		case 2:
			try {
				int val = std::stof(cur_column_val);
				if (val < 0) 
					err_code += 4;
			}catch(...) {
				err_code += 4;
			}
			break;
		default:
			err_code += 8;
			break;
		}		
	}

	if(err_code){
		std::string err_msg = "";

		err_msg += std::to_string(err_code);
		err_msg += ";";
		err_msg += std::to_string(lineNum);

		throw FormatException(err_msg.c_str());
	}
}

// TODO 3.1d
void writeOutFormatException(const FormatException& e) {

	std::string ex_msg = e.what();
	
	int delimiter = ex_msg.find(';');

	//std::cerr << std::to_string(delimiter) << " "<< ex_msg << std::endl;

	int err_code = std::atoi(ex_msg.substr(0,delimiter).c_str());

	int lineNum = std::atoi(ex_msg.substr(delimiter+1,ex_msg.length()-delimiter).c_str());

	if(err_code){
		std::string err_msg = "";

		if(err_code & 1)
			err_msg += "time_error ";
		else
			err_msg += "           ";

		if(err_code & 2)
			err_msg += "temp_error ";
		else
			err_msg += "           ";

		if(err_code & 4)
			err_msg += "rain_error ";
		else
			err_msg += "           ";

		if(err_code & 8)
			err_msg += "csv_error ";
		else
			err_msg += "          ";

		err_msg += "\t in Line ";
		err_msg += std::to_string((int) lineNum);
		err_msg += "\n";
		
		try {
			std::ofstream file("wetter.log", std::ios_base::app | std::ios_base::out);

			file << err_msg;
			if (file.exceptions()){
				std::cerr << "Error while writing into file!" << std::endl;
				exit(1);
			}else 
				file.flush();
			
			file.close();
		}
		catch(const std::ofstream::failure& ofe) {
			std::cerr << "Error occured while opening/writing/closing wetter.log: " << ofe.what() << '\n';
		}
		
		
	}
}

void checkData(const std::string& path)
{
	std::ifstream file;

	// TODO 3.1a: open file + read each line + call parseLine function (catch ifstream::failure)
	// TODO 3.1c: read each line + call parseLine function (catch FormatException) + count valid + invalid
	//            lines
	int correct = 0;
	int incorrect = 0;

	try
	{
		file.open(path);

		if (file.fail()){
			//file could not open file
			std::cerr << "Error: opening file!" << std::endl;
			exit(1);
		}

		//create Bufferstring buf and read header line before directly overwriting it
		std::string buf;
		std::getline(file, buf);
		int counter = 1;
		int exceptionflags = 0;

		//read each line separately from file and parse it with parseLine func (takes line and lineNumber)
		
		while (std::getline(file, buf)) {
			//check if stream still feels fine

			exceptionflags = file.exceptions();
			
			if (exceptionflags) {
				if (exceptionflags & 1) {
					//eof error
					std::cerr << "Error: unexpected ending of file!" << std::endl;
					exit(1);
				}
				if (exceptionflags & 2) {
					// Logical error on i/o operation
					std::cerr << "Error: logical error occured while reading!" << std::endl;
					exit(1);
				}
				if (exceptionflags & 4) {
					// Read/writing error on i/o operation
					std::cerr << "Error: occurred during read operation!" << std::endl;
					exit(1);
				}			
			}
			try {
				parseLine(buf, ++counter);
				correct++;
			}
			catch(const FormatException& e) {
				writeOutFormatException(e);
				incorrect++;
			}
			catch(...) {
				std::cerr << "Unknown error " << std::endl;
				std::cerr.flush();
				incorrect++;
			}
			
			
		}
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	file.close();

	std::cout << std::endl 
			<< std::endl 
			<< "----------------------------------"
			<< std::endl
			<< "Correct lines: " 
			<< correct
			<< "\t Incorrect lines: "
			<< incorrect
			<< std::endl;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Invalid number of arguments - USAGE: exceptions [DATASET]" << std::endl;
		return -1;
	}

	checkData(argv[1]);

	return 0;
}