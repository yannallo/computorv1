#include "computorv1.h"
/*
static void print_token(Token *t)
{
	size_t i = 0;

	printf("TOKEN LIST:\n");
	while (t[i].type != END)
	{
		printf("[%s]", t[i].str);
		i++;
	}
	printf("\n\n");
}

static void print_pol(Polynom p)
{
	printf("POLYNOMIAL\n");
	for (size_t i = 0; i < p.size; i++)
		printf("[%g, %ld] ", p.terms[i].coef, p.terms[i].power);
	printf("\n");
}

static void print_coef(double *coefs, size_t size)
{
	printf("\nCOEF\n");
	for (size_t i = 0; i <= size; i++)
		printf("[%g X^ %ld] ", coefs[i], i);
	printf("\n\n");
}
*/

int main(int ac, char **av)
{
	if (ac != 2) {
		ft_putstr("Give 1 equation to solve\n");
		return 1;
	}
	
	//tokenize
	Token *tokens = tokenize(av[1]);
	if (!tokens)
		return 1;
	
	//parse
	Polynom left, right;
	if (parse(tokens, &left, &right)) {
		free_all(tokens, left, right);
		return 1;
	}

	//refacto
	double *coefs;
	size_t max_power;
	coefs = refacto(&left, &right, &max_power);
	if (!coefs) {
		free_all(tokens, left, right);
		return 1;
	}

	//solve
	solve(coefs, max_power);	

	//Free
	free_all(tokens, left, right);
	free(coefs);
	return 0;
}
