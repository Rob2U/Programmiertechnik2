#include <cstdlib>
#include <iostream>
#include <string>

// ToDo: Exercise 1.d - adapt and implement combinations

unsigned long long combinations(int number)
{
	if (number < 1)
		return 0;
	if (number == 1)
		return 1;
	if (number == 2)
		return 2;
	else {
		unsigned long long s1 = 1;
		unsigned long long s2 = 2;
		unsigned long long temp;

		for (int i = 3; i <= number; i++) {
			temp = s2;
			s2 = s1 + s2;
			s1 = temp;
		}
		return s2;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
		return 1; // invalid number of parameters

	int n = std::stoi(argv[1]);

	std::cout << combinations(n) << std::endl;

	return 0;
}