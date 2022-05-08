#include <cstdlib>
#include <iostream>
#include <string>

int count_of_steps = 0;

int fibonacci(int n)
{
	// ToDo: Exercise 1.c - count number of calculation steps

	// ToDo: Exercise 1.b - return 0 on bad arguments

	// ToDo: Exercise 1.b - retrieve nth fibonacci number iteratively

	if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        int a = 1;
        int b = 1;
        int c = 1;
        for (int i = 3; i <= n; i++) {
			count_of_steps++;
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }

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
