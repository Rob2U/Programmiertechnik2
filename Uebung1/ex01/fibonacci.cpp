#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int count_of_sums = 0;


//implement fibonacci recursive
int fibonacci_recursive(int n) {
    if (n <= 0) {
        return 1;
    } else if (n == 1 || n == 2) {
        count_of_sums++;
        return 1;
    } else {
        count_of_sums++;
        return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
    }
}

//impement fibonacci iterative
int fibonacci_iterative(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        int a = 0;
        int b = 1;
        int c = 0;
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Fibonacci of " << n << " is " << fibonacci_recursive(n) << endl;
    cout << "It took " << count_of_sums << " iterations to calculate the fibonacci number" << endl;
    return 0;
}