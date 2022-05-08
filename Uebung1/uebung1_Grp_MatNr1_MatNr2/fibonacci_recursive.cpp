#include <cstdlib>
#include <iostream>
#include <string>

int parseAsInt(char*, int&);

int count_of_steps = 0;

int fibonacci(int n)
{
	// ToDo: Exercise 1.c - count number of calculation steps

	// ToDo: Exercise 1.a - return 0 on bad arguments

	// ToDo: Exercise 1.a - retrieve nth fibonacci number recursively

	if (n <= 0) {
        return 0;
    } else if (n == 1 || n == 2) {
        count_of_steps++;
        return 1;
    } else {
        count_of_steps++;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
		return 1; // invalid number of parameters

	int n;
	if (parseAsInt(argv[1], n)) {
		std::cerr << "Text was given instead of number (as parameter)!" << std::endl;
		return -1; // invalid parameter
	} 

	// ToDo: Exercise 1.c - print calculation steps
	int fib = fibonacci(n);
	std::cout << n << " : " << fib << " : #" <<  count_of_steps << std::endl;

	return 0;
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
