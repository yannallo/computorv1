#include "computorv1.h"

int read_input(int ac, char **av, char *buffer)
{
	char *trunc;

	if (ac == 2) {
		buffer = strncpy(buffer, av[1], MAX_SIZE-1);
		buffer[MAX_SIZE] = '\0';
	}
	else {
		if (fgets(buffer, MAX_SIZE, stdin) == NULL) {
			ft_putstr(RED "Error: Can't read from stdin\n"RESET);
			return 0;
		}
		trunc = strchr(buffer, '\n');
		if (!trunc) {
			ft_putstr(RED "Error: Equation too long (max: 1024)\n"RESET);
			return 0;
		}
		if (buffer[0] == '\n') {
			ft_putstr(RED "Error: No equation given\n"RESET);
			return 0;
		}
		*trunc = '\0';
	}
	return 1;
}

int main(int ac, char **av)
{
	char input[1024] = {0};

	if (ac == 1) {
		ft_putstr(CYAN "A simple solver of polynomial\n\n"RESET);
		ft_putstr(CYAN "Usage: ./computorv1 \"equation\"\n\n"RESET);
		ft_putstr(CYAN "Exemples:\n./computorv1 \"3 * X^2 + 2 * X^1 - 1 = 2 * X^1\"\n"RESET);
		ft_putstr(CYAN "./computorv1 \"2X^2 + X - 1 = 0\"\n"RESET);
		ft_putstr(GREEN "Enter your equation\n"RESET);
	}
	else if (ac != 2) {
		ft_putstr(CYAN "Give 1 equation to solve" RESET "\n");
		return 0;
	}
	//Input
	if (!read_input(ac, av, input))
		return 1;

	//tokenize
	Token *tokens = tokenize(input);
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
	free(coefs);
	free_all(tokens, left.terms, right.terms);
	return 0;
}
