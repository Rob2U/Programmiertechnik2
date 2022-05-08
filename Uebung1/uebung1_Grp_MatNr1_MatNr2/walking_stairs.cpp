#include <cstdlib>
#include <iostream>
#include <string>

// ToDo: Exercise 1.d - adapt and implement combinations
typedef unsigned long long u_longlong;

u_longlong combinations(int n)
{
	if (n <= 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	} else if (n == 2) {
		return 2;
	} else {
		u_longlong a = 1;
		u_longlong b = 2;
		u_longlong c = 0;
		for (int i = 3; i <= n; i++) {
			c = a + b;
			a = b;
			b = c;

		}
		return c;
	}
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

//Beachte u_long hat eine Groesse von 64 Bit (auf einem ^4-bit System), was hier ausreichend groß ist, aber bei größeren Werten problematisch weren kann.
int main(int argc, char* argv[])
{
	if (argc != 2)
		return 1; // invalid number of parameters

	int n;

	if (parseAsInt(argv[1], n)){
		std::cout << "Invalid input" << std::endl;
		return -1;
	}

	std::cout << combinations(n) << std::endl;

	return 0;
}