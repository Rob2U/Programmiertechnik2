#include <cstdlib>
#include <iostream>
#include <string>

int count_of_sums = 0;

int fibonacci(int n)
{
	// ToDo: Exercise 1.c - count number of calculation steps

	// ToDo: Exercise 1.a - return 0 on bad arguments

	// ToDo: Exercise 1.a - retrieve nth fibonacci number recursively

	if (n <= 0) {
        return 1;
    } else if (n == 1 || n == 2) {
        count_of_sums++;
        return 1;
    } else {
        count_of_sums++;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
		return 1; // invalid number of parameters

	int n = std::stoi(argv[1]);

	// ToDo: Exercise 1.c - print calculation steps

	std::cout << n << " : " << fibonacci(n) << " : #" <<  count_of_sums << std::endl;

	return 0;
}
