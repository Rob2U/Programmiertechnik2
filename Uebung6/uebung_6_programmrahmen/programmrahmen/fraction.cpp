#include <cassert>
#include <iostream>

void runTests()
{
	/* Test exception */
	// try
	//{
	//	std::cout << Fraction(4, 0);
	//	assert(false);
	//}
	// catch (const std::invalid_argument&)
	//{
	//}
	// std::cout << Fraction(2, 3) - Fraction(2, 3) << '\n'; // Should print 0 and not throw an exception

	/* Store values instead of generating them inline to better test the method's signature */
	// const Fraction fraction_4_5(4, 5);
	// const Fraction fraction_1_3(1, 3);

	/* Some simple test cases for operator overloading of fractions */
	// std::cout << fraction_4_5 + Fraction(2, 4) << '\n'; // Should print "1 3/10"
	// std::cout << fraction_4_5 - Fraction(2, 4) << '\n'; // Should print "3/10"
	// std::cout << fraction_1_3 * Fraction(2, 4) << '\n'; // Should print "1/6"
	// std::cout << fraction_1_3 / Fraction(2, 4) << '\n'; // Should print "2/3"

	/* Some simple test cases for operator overloading of fractions in connection with integers */
	// std::cout << fraction_4_5 + 2 << '\n'; // Should print "2 4/5"
	// std::cout << fraction_4_5 - 2 << '\n'; // Should print "-1 1/5"
	// std::cout << fraction_1_3 * 3 << '\n'; // Should print "1"
	// std::cout << fraction_1_3 / 3 << '\n'; // Should print "1/9"

	/* Test global operator functions */
	// std::cout << 2 + fraction_4_5 << '\n'; // Should print "2 4/5"
	// std::cout << 2 - fraction_4_5 << '\n'; // Should print "1 1/5"
	// std::cout << -3 * fraction_1_3 << '\n'; // Should print "-1"
	// std::cout << -3 / fraction_1_3 << '\n'; // Should print "-1/9"

	/* Test constexpr */
	// constexpr Fraction constexprFrac =
	//	-1 * ((Fraction(4, 5) / 2 + Fraction(2, 4) * (Fraction(3, 9) - 1)) * 3 + 4 - Fraction(1, 5))
	//	/ Fraction(7, 2);
	// std::cout << constexprFrac << '\n'; // Should print "-1 1/7"

	/* Test User - defined conversion function */
	// double castedValue = static_cast<double>(Fraction(3, 4));
	// std::cout << castedValue << '\n'; // Should print 0.75
}

int main()
{
	try
	{
		runTests();
	}
	catch (const std::invalid_argument&)
	{
		return 1;
	}

	return 0;
}
