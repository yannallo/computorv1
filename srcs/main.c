#include "computorv1.h"

int main(int ac, char **av)
{
	if (ac == 1) {
		ft_putstr(CYAN "A simple solver of polynomial" RESET "\n\n");
		ft_putstr(CYAN "Usage: ./computorv1 \"equation\"" RESET "\n\n");
		ft_putstr(CYAN "Exemples:\n./computorv1 \"3 * X^2 + 2 * X^1 - 1 = 2 * X^1\"" RESET "\n");
		ft_putstr(CYAN "./computorv1 \"2X^2 + X - 1 = 0\"" RESET "\n");
		return 0;
	}
	if (ac != 2) {
		ft_putstr(CYAN "Give 1 equation to solve" RESET "\n");
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
