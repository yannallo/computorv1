#include "computorv1.h"

int main(int ac, char **av)
{
	if (ac == 1) {
		ft_putstr("A simple solver of polynomial\n\n");
		ft_putstr("Usage: ./computorv1 \"equation\"\n\n");
		ft_putstr("Exemples:\n./computorv1 \"3 * X^2 + 2 * X^1 - 1 = 2 * X^1\"\n");
		ft_putstr("./computorv1 \"2X^2 + X - 1 = 0\"\n");
		return 0;
	}
	if (ac != 2) {
		ft_putstr("Give 1 equation to solve\n");
		return 0;
	}

	//tokenize
	Token *tokens = tokenize(av[1]);
	if (!tokens)
		return 1;
	
	//valid
	if (valid(tokens)) {
		free_all(tokens, NULL, NULL);
		return 1;
	}

	//parse
	Polynom left, right;
	if (parse(tokens, &left, &right)) {
		free_all(tokens, left.terms, right.terms);
		return 1;
	}

	//refacto
	double *coefs;
	size_t max_power;
	coefs = refacto(left, right, &max_power);
	if (!coefs) {
		free_all(tokens, left.terms, right.terms);
		return 1;
	}

	//solve
	solve(coefs, max_power);

	//Free
	free_all(tokens, left.terms, right.terms);
	free(coefs);
	return 0;
}
