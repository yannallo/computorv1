#include "computorv1.h"

static void print_abs(double coef)
{
	if (coef < 0)
		coef = -coef;
	printf("%g", coef);
}

static void print_equation(double *coefs, size_t power)
{
	if (power == 0) {
		printf("%g * X^0 = 0\n", coefs[0]);
		return ;
	}
	for (size_t i = power; i+1 > 0; i--)
	{
		if (i == power) {
			if (coefs[i] < 0)
				printf("-");
		}
		else if (coefs[i] != 0) {
			if (coefs[i] < 0)
				printf("- ");
			else
				printf("+ ");
		}
		if (coefs[i] != 0) {
			if (coefs[i] != 1 || i == 0)
				print_abs(coefs[i]);
			if (i == 1)
				printf("X");
			else if (i != 0)
				printf("X^%zu", i);
			printf(" ");
		}
	}
	printf("= 0\n");
}

void solve_linear(double *coefs)
{
	double res = -coefs[0]/coefs[1];
	
	if (res == 0)
		printf("Solution:\n0\n");
	else
		printf("Solution:\n%g\n", res);
}

void solve_quadratic(double *coefs)
{
	double a = coefs[2];
	double b = coefs[1];
	double c = coefs[0];
	double discri = b*b - 4*a*c;

	printf("Discriminant = %g\n", discri);
	if (discri > 0) {
		printf("Solutions:\n%g %g\n", (-b + sqrt(discri)) / (2*a), (-b - sqrt(discri)) / (2*a));
	}
	else if (discri == 0) {
		printf("Solution: %g\n", (-b + sqrt(discri)) / (2*a));
	}
	else {
		double real = -b / (2*a);
		double i = sqrt(-discri) / (2*a);
		if (real != 0) {
			if (i == 1)
				printf("Solution:\n%g + i  %g - i\n", real, real);
			else
				printf("Solution:\n%g + %gi  %g - %gi\n", real, i, real, i);
		}
		else {
			if (i == 1)
				printf("Solutions:\ni  -i\n");
			else
				printf("Solutions:\n%gi  -%gi\n", i, i);
		}
	}
}

void solve(double *coefs, size_t max_power)
{
	size_t power = 0;
	for (size_t i = 0; i <= max_power; i++) {
		if (coefs[i] != 0)
			power = i;
	}
	print_equation(coefs, power);
	printf("Equation degree: %zu\n", power);
	if (power > 2)
		printf("Can't solve polynomial above second degree\n");
	else if (power == 0) {
		if (coefs[0] == 0)
			printf("Any real number is a solution\n");
		else
			printf("No solution\n");
	}
	else if (power == 1)
		solve_linear(coefs);
	else if (power == 2)
		solve_quadratic(coefs);
}
