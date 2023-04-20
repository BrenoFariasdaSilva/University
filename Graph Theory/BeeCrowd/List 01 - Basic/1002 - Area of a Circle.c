// The formula to calculate the area of a circumference is defined as A = π . R2. Considering to this problem that π = 3.14159:

// Calculate the area using the formula given in the problem description.
// Input

// The input contains a value of floating point (double precision), that is the variable R.
// Output

// Present the message "A=" followed by the value of the variable, as in the example bellow, with four places after the decimal point. Use all double precision variables. Like all the problems, don't forget to print the end of line after the result, otherwise you will receive "Presentation Error".
// Input Samples 	
// 2.00
// Output Samples
// A=12.5664

// Input Samples
// 100.64
// Output Samples
// A=31819.3103

// Input Samples
// 150.00
// Output Samples
// A=70685.7750

#include <stdio.h>
 
int main() {
	long double area = 0;
	long double pi = 3.14159;
	long double r = 0;
	
	scanf("%Lf", &r);
	
	area = pi * (r * r);
	
	printf("A=%.4Lf\n", area);

	return 0;
}