#include <cstdlib>
#include <iostream>
#include <string>

int steps;

int fibonacci(int number)
{
	// ToDo: Exercise 1.c - count number of calculation steps
	steps = 0;

	// ToDo: Exercise 1.b - return 0 on bad arguments
	if (number <= 0 || number > 46) 
		return 0;

	// ToDo: Exercise 1.b - retrieve nth fibonacci number iteratively
	int fib1 = 1;
	int fib2 = 1;
	int temp;
	for (int i = 1; i < number; i++) {
		temp = fib2;
		fib2 = fib2 + fib1;
		fib1 = temp;
		steps++;
	}

	return fib1;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
		return 1; // invalid number of parameters

	int n = std::stoi(argv[1]);

	// ToDo: Exercise 1.c - print calculation steps
	int fib = fibonacci(n);

	std::cout << n << " : " << fib << " : " << "#" << steps << std::endl;

	return 0;
}
