#include "computorv1.h"

static size_t get_degree(Term *term)
{
	size_t degree = 0;

	while (term)
	{
		if (term->exponent > degree)
			degree = term->exponent;
		term = term->next;
	}

	return degree;
}

static double get_coef(Term *list, size_t exponent)
{
	while (list)
	{
		if (list->exponent == exponent)
			return list->coef;
		list = list->next;
	}
	return 0;
}

static void print_equation(Term *list)
{
	size_t size = get_degree(list);
	Term *term;

	if (!list)
		return;

	printf("Reduced form: ");
	for (ssize_t i = size; i >= 0; i--)
	{
		term = get_node(list, i);
		if (i != size)
		{
			if (term && term->coef < 0)
				printf(" - ");
			else
				printf(" + ");
		}
		else if (term && term->coef < 0)
			printf("-");

		if (!term)
			printf("0 * X^%d", i);
		else
			print_node(term);
	}
	printf(" = 0\n");
}

static int is_equals(Term *list)
{
	while (list)
	{
		if (list->coef != 0)
			return 0;
		list = list->next;
	}
	return 1;
}

void solve(Term *term)
{
	int degree = get_degree(term);
	double a = get_coef(term, 2);
	double b = get_coef(term, 1);
	double c = get_coef(term, 0);

	print_equation(term);
	if (is_equals(term))
	{
		printf("Any real number is a solution");
		return ;
	}

	printf("Polynomial degree: %d\n", degree);
	if (degree > 2)
		ft_putstr("Polynomial degree is too high\n");
	else if(degree == 0)
		printf("No solution\n");
	else if (degree == 1)
		printf("SOLUTION: \n%g\n", -(c / b));
	else if (degree == 2)
	{
		double discri = b * b - 4 * a * c;

		dprintf(2, "DISCRIMINANT = %g\n", discri);
		if (discri > 0)
		{
			printf("There is 2 solution:\n");
			printf("%g\n%g\n", (-b+sqrt(discri))/(2*a), (-b-sqrt(discri))/(2*a));
		}
		else if (discri == 0)
		{
			printf("There is 1 solution:\n");
			printf("%g\n", (-b+sqrt(discri))/(2*a));
		}
		else if (discri < 0)
		{
			printf("There is 2 complex solution:\n");
			double tmp = -b/(2*a);
			double i = sqrt(-discri)/(2*a);
			printf("%g + %gi\n%g - %gi\n", tmp, i, tmp, i);
		}
	}
}
