#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <limits>


// ToDo: Exercise 1.d - adapt and implement combinations

u_long combinations(int n)
{
	if (n <= 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	} else if (n == 2) {
		return 2;
	} else {
		u_long a = 1;
		u_long b = 2;
		u_long c = 0;
		for (int i = 3; i <= n; i++) {
			c = a + b;
			a = b;
			b = c;

		}
		return c;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
		return 1; // invalid number of parameters

	int n = std::stoi(argv[1]);

	std::cout << sizeof(u_long) << std::endl;
	std::cout << std::numeric_limits<u_long>().max() << std::endl;

	std::cout << combinations(n) << std::endl;

	return 0;
}
