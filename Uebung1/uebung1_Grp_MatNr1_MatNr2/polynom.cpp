#include <iostream>
#include <string>
#include <vector>
#include <math.h>

double polynom(std::vector<double>* vector, int n, double x)
{
	long double sum = 0;
	for (int i = 0; i < n+1; i++)
	{
		sum += vector->at(i)* std::pow(x,i);
	}
	return sum;
}

void prettyPrint(double decimal)
{
	// ToDo: Exercise 2.c - print number with thousands separators to console
	std::string tmpstring = std::to_string(decimal);
	std::string ret_string;
	
	int i = 0;
	char c;

	int idx_point = tmpstring.find('.');
	if (idx_point != std::string::npos) {
		tmpstring.replace(idx_point, 1, ",");
	} 

	while ((c = tmpstring.at(i))!= '\0' && c != ',')
	{
		if ((idx_point-i)%3 == 0 && i != 0 && ret_string.at(i-1)!='-'){
			ret_string = ret_string.append(".");
		}
		ret_string += tmpstring.at(i++);
	}
	ret_string = ret_string.append(tmpstring.substr(idx_point,tmpstring.length()));

	int idx = ret_string.length()-1;

	while (ret_string.at(idx) == '0'){
		ret_string.pop_back();
		idx--;
	}

	if (ret_string.at(idx) == ','){
		ret_string.pop_back();
	}

	std::cout<< ret_string << std::endl;
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

int parseAsDouble(char* str, double& result){
	try
	{
		result = std::stod(str);
		return 0;
	}
	catch(const std::exception& e)
	{
		return -1;
	}
}



int main(int argc, char* argv[])
{

	// ToDo: Exercise 2.a - read parameters and x, deal with invalid values

	if (argc <= 2){	
		std::cout << "Usage: " << argv[0] << " <x> <polynom degreee (n)> <factor 0> ... <factor n>" << std::endl;
		return 0; // invalid number of parameters
	}

	double x;
	if (parseAsDouble(argv[1], x)) {
		std::cerr << "Text was given instead of number (as parameter)!" << std::endl;
		return -1; // invalid parameter
	}
	//std::cout << "x = " << x << std::endl;



	int n;
	if (parseAsInt(argv[2], n)) {
		std::cerr << "Text was given instead of number (as parameter)!" << std::endl;
		return -1; // invalid parameter
	} 
	//std::cout << "n = " << n << std::endl;

	if (n < 0){ 
		std::cerr << "polynom degree must be greater than 0!" << std::endl;
		return 0; // invalid arguments
	}

	std::vector<double> coefficients;

	double val;
	if (n == argc-4) {
		for (int i = 3; i <= n+3; i++) {
			//std::cerr << "coefficient " << i-2 << " = " << argv[i] << std::endl;
			
			if (parseAsDouble(argv[i], val)) {
				std::cerr << "Text was given instead of number (as parameter)!" << std::endl;
				return -1; // invalid parameter
			}
			coefficients.push_back(val);
		}
	} else {
		std::cout << "Usage: " << argv[0] << " <x> <polynom degreee (n)> <factor 0> ... <factor n>" << std::endl;
		return 0; // invalid number of coefficients
	}

	// ToDo: Exercise 2.b - print P(x)
	//std::cout << polynom(&coefficients, n, x) << std::endl;

	// ToDo: Exercise 2.c - print P(x) with prettyPrint
	prettyPrint(polynom(&coefficients, n, x));

	return 0;
}