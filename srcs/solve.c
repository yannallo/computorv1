#include "computorv1.h"

static void print_abs(double coef)
{
	if (coef < 0)
		coef = -coef;
	printf(GREEN "%g" RESET, coef);
}

static void print_equation(double *coefs, size_t power)
{
	if (power == 0) {
		printf(GREEN "%g * X^0 = 0" RESET "\n", coefs[0]);
		return ;
	}
	for (size_t i = power; i+1 > 0; i--)
	{
		if (i == power) {
			if (coefs[i] < 0)
				printf(GREEN "-" RESET);
		}
		else if (coefs[i] != 0) {
			if (coefs[i] < 0)
				printf(GREEN "- " RESET);
			else
				printf(GREEN "+ " RESET);
		}
		if (coefs[i] != 0) {
			if ((coefs[i] != 1 && coefs[i] != -1) || i == 0)
				print_abs(coefs[i]);
			if (i == 1)
				printf(GREEN "X" RESET);
			else if (i != 0)
				printf(GREEN "X^%zu" RESET, i);
			printf(GREEN " " RESET);
		}
	}
	printf(GREEN "= 0" RESET "\n");
}

void solve_linear(double *coefs)
{
	double res = -coefs[0]/coefs[1];
	
	if (res == 0)
		printf(MAGENTA "Solution:\n0" RESET "\n");
	else
		printf(MAGENTA "Solution:\n%g" RESET "\n", res);
}

void solve_quadratic(double *coefs)
{
	double a = coefs[2];
	double b = coefs[1];
	double c = coefs[0];
	double discri = b*b - 4*a*c;

	printf(YELLOW "Discriminant = %g" RESET "\n", discri);
	if (discri > 0) {
		printf(MAGENTA "Solutions:\n%g\n%g" RESET "\n", (-b + sqrt(discri)) / (2*a), (-b - sqrt(discri)) / (2*a));
	}
	else if (discri == 0) {
		printf(MAGENTA "Solution:\n%g" RESET "\n", (-b + sqrt(discri)) / (2*a));
	}
	else {
		double real = -b / (2*a);
		double i = sqrt(-discri) / (2*a);
		if (real != 0) {
			if (i == 1)
				printf(MAGENTA "Solution:\n%g + i\n%g - i" RESET "\n", real, real);
			else
				printf(MAGENTA "Solution:\n%g + %gi\n%g - %gi" RESET "\n", real, i, real, i);
		}
		else {
			if (i == 1)
				printf(MAGENTA "Solutions:\ni\n-i" RESET "\n");
			else
				printf(MAGENTA "Solutions:\n%gi\n-%gi" RESET "\n", i, i);
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
	printf(YELLOW "Equation degree: %zu" RESET "\n", power);
	if (power > 2)
		printf(MAGENTA "Can't solve polynomial above second degree" RESET "\n");
	else if (power == 0) {
		if (coefs[0] == 0)
			printf(MAGENTA "Any real number is a solution" RESET "\n");
		else
			printf(MAGENTA "No solution" RESET "\n");
	}
	else if (power == 1)
		solve_linear(coefs);
	else if (power == 2)
		solve_quadratic(coefs);
}

