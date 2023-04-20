// Read three values (variables A, B and C), which are the three student's grades. Then, calculate the average, considering that grade A has weight 2, grade B has weight 3 and the grade C has weight 5. Consider that each grade can go from 0 to 10.0, always with one decimal place.
// Input

// The input file contains 3 values of floating points (double) with one digit after the decimal point.
// Output

// Print the message "MEDIA"(average in Portuguese) and the student's average according to the following example, with a blank space before and after the equal signal.

// Input Samples 	
// 5.0
// 6.0
// 7.0
// Output Samples
// MEDIA = 6.3

// Input Samples
// 5.0
// 10.0
// 10.0
// Output Samples
// MEDIA = 9.0

// Input Samples
// 10.0
// 10.0
// 5.0
// Output Samples
// MEDIA = 7.5

#include <stdio.h>
 
int main() {
	double a, b, c;
	
	scanf("%lf", &a);
	scanf("%lf", &b);
	scanf("%lf", &c);

	double average = (a*2 + b*3 + c*5) / 10;

	printf("MEDIA = %.1lf\n", average);

	return 0;
}