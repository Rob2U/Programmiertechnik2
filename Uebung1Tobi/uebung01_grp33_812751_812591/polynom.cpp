#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

double polynom(double x, int n, std::vector<double> parameters)
{
	double result = 0;
	// ToDo: Exercise 2.b - compute value of P(x)
	for (int i = 0; i < n; i++)
	{
		result = result + parameters[i]*std::pow(x, i);
	}

	return result;
}

std::string reverseString (std::string str) {
	std::string revStr;
	for (int i = str.length()-1; i >= 0; i--) {
		revStr[(str.length()-1)-i] = str[i];
	}
	
	return revStr;
}

void prettyPrint(double decimal)
{
	// ToDo: Exercise 2.c - print number with thousands separators to console
	int number = decimal;

	std::string str = std::to_string(number);
	int preDecPlaces = str.length();
	std::string formStr;
	int counter = 0;

	//add separators
	for (int i = str.length()-1; i >= 0; i--) {
		if (counter != 0 && counter % 3 == 0) {
			formStr = formStr + '.';
		}
		formStr = formStr + str[i];
		counter++;
	}
	
	//reverse String
	std::reverse(formStr.begin(), formStr.end());

	//add decimal places to the nearest 4 places
	if (decimal - number != 0){
		str = std::to_string(decimal);
		formStr = formStr + ',';
		for (int i = preDecPlaces+1; i < preDecPlaces+5; i++) {
			formStr = formStr + str[i];
		}
		
	}
	
	//print formatted String
	std::cout << formStr << std::endl;
}

int main(int argc, char* argv[])
{
	// ToDo: Exercise 2.a - read parameters and x, deal with invalid values
	double x, helper;
	int n;
	std::vector<double> parameters;

	//enter x
	std::cout << "Enter x: ";
	while(!(std::cin >> x)){
		std::cout << "ERROR: please enter a correct number: ";
		std::cin.clear();
   		std::cin.ignore(123, '\n');
	}
	
	//remove truncated incorrect input
	std::cin.clear();
	std::cin.ignore(123, '\n');

	//enter n
	std::cout << "Enter n: ";
	while(!(std::cin >> n)){
		std::cout << "ERROR: please enter a correct number: ";
		std::cin.clear();
   		std::cin.ignore(123, '\n');
	}

	//check whether input is correct
	if (n<0) {
		std::cout << "n must be greater than zero";
		return 1;
	}

	//remove truncated incorrect input
	std::cin.clear();
	std::cin.ignore(123, '\n');

	//enter coefficients
	for (int i = 0; i < n; i++) {
		std::cout << "Enter a" << i << ": ";
		while(!(std::cin >> helper)){
			std::cout << "ERROR: please enter a correct number: ";
			std::cin.clear();
   			std::cin.ignore(123, '\n');
		}
		if (helper != 0) {
			parameters.push_back(helper);
		} else {
			std::cout << "A coefficient can't be 0.";
			return 1;
		}
	}
	

	double result = polynom(x, n, parameters);

	// ToDo: Exercise 2.b - print P(x)
	std::cout << "P(x) = " << result << std::endl;

	// ToDo: Exercise 2.c - print P(x) with prettyPrint
	prettyPrint(result);

	return 0;
}