#include <cstdlib>
#include <iostream>
#include <string>

long long steps;

int fibonacci(int number)
{
	// ToDo: Exercise 1.c - count number of calculation steps
	steps++;

	// ToDo: Exercise 1.a - return 0 on bad arguments 
	if (number <= 0 || number > 46) 
		return 0;

	// ToDo: Exercise 1.a - retrieve nth fibonacci number recursively
	if (number <= 2) {
		return 1;
	} else {
		return fibonacci(number - 1) + fibonacci(number - 2);
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cout << "Invalid number of parameters";
		return 1; // invalid number of parameters
	}

	int n = std::stoi(argv[1]);

	// ToDo: Exercise 1.c - print calculation steps
	steps = 0;
	int fib = fibonacci(n);

	std::cout << n << " : " << fib << " : " << "#" << steps << std::endl;

	return 0;
}
