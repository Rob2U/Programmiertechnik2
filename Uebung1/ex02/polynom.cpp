#include <iostream>
#include <string>
#include <vector>
#include <math.h>

long double polynom(std::vector<double>* vector, int n, double x)
{
	long double sum = 0;
	for (int i = 0; i <= n; i++)
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
		if ((idx_point-i)%3 == 0 && i != 0){
			ret_string = ret_string.append(".");
		}
		ret_string += tmpstring.at(i++);
	}
	ret_string = ret_string.append(tmpstring.substr(idx_point,tmpstring.length()));

	std::cout<< ret_string << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc <= 3)		return 1; // invalid number of parameters

	double x = std::stod(argv[1]);
	int n = std::stoi(argv[2]);

	if (x < 0 || n < 0)	return 1; // invalid arguments

	std::vector<double> coefficients;

	try
	{
		for (int i = 3; i < argc; i++)
		{
			coefficients.push_back(std::stod(argv[i]));
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}



	// ToDo: Exercise 2.a - read parameters and x, deal with invalid values

	// ToDo: Exercise 2.b - print P(x)
	// ToDo: Exercise 2.c - print P(x) with prettyPrint

	std::cout << polynom(&coefficients, n, x) << std::endl << std::endl;

	prettyPrint(polynom(&coefficients, n, x));

	return 0;
}
