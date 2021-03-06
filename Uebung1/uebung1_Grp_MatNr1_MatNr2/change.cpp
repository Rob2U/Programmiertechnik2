#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

void change(const int due, const int paid, std::ostream& out)
{
	// ToDo: compute and write set of change tuples to output stream
	int left = paid - due;

	if (left < 0) {
		out << "Insufficient payment" << std::endl;
		return;
	}

	if (left == 0) {
		out << "No change" << std::endl;
		return;
	}

	while (left != 0)
	{
		if (left >= 5000)
		{
			out << "5000," << left/5000 << std::endl;
			left -= 5000*(left/5000);
		}else if (left >= 2000)
		{
			out << "2000," << left/2000 << std::endl;
			left -= 2000*(left/2000);
		}else if (left >= 1000)
		{
			out << "1000," << left/1000 << std::endl;
			left -= 1000*(left/1000);
		}else if (left >= 500){
			out << "500," << left/500 << std::endl;
			left -= 500*(left/500);
		}else if (left >= 200){
			out << "200," << left/200 << std::endl;
			left -= 200*(left/200);
		}else if (left >= 100){
			out << "100," << left/100 << std::endl;
			left -= 100*(left/100);
		}else if (left >= 50){
			out << "50," << left/50 << std::endl;
			left -= 50*(left/50);
		}
		else if (left >= 20){
			out << "20," << left/20 << std::endl;
			left -= 20*(left/20);
		}
		else if (left >= 10){
			out << "10," << left/10 << std::endl;
			left -= 10*(left/10);
		}
		else if (left >= 5){
			out << "5," << left/5 << std::endl;
			left -= 5*(left/5);
		}
		else if (left >= 2){
			out << "2," << left/2 << std::endl;
			left -= 2*(left/2);
		}
		else if (left >= 1){
			out << "1," << left/1 << std::endl;
			left -= 1*(left/1);
		}	
	}

	return;
	
}

int parseAsInt(char* str, int& result){
	try
	{
		result = std::stoi(str);
		return 0;
	}
	catch(const std::exception& e)
	{
		return -1;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3 && argc != 5){
		std::cerr << "Usage: " << argv[0] << " <due> <paid> [ -o <output-file>]\n";
		return 1; // invalid number of parameters
	}

	int due;
	if (parseAsInt(argv[1], due)) {
		std::cerr << "Text was given instead of number (as parameter)!" << std::endl;
		return -1; // invalid parameter
	}


	int paid;
	if (parseAsInt(argv[2], paid)) {
		std::cerr << "Text was given instead of number (as parameter)!" << std::endl;
		return -1; // invalid parameter
	}

	if (paid < 0 || due < 0) {
		std::cerr << "Negative numbers are not allowed!" << std::endl;
		return -1; // invalid parameter
	}
	

	try {
		if (argc==5 && argv[3]==std::string("-o"))
		{
			std::ofstream out(argv[4]);

			change(due, paid, out);
		}
		else if (argc==5 && argv[3]!=std::string("-o"))
		{
			std::cerr << "Usage: " << argv[0] << " <due> <paid> [ -o <output-file>]\n";
		} else		
		{
			change(due, paid, std::cout);
		}

		// ToDo: catch invalid arguments

		// ToDo: write change data as CSV to file if necessary

		return 0;
	} catch (...) {
		std::cerr << "Invalid arguments\n";
		return 2; // invalid arguments
	}
}
