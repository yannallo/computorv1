#include "computorv1.h"

static size_t count_term(Token *tokens, size_t i)
{
	size_t count = 0;

	if (tokens[i].type == SIGN)
		i++;
	while (tokens[i].type != END && tokens[i].type != EQUAL) {
		if (tokens[i].type == SIGN)
		       count++;	
		i++;
	}
	return count + 1;
}

static Term parse_term(Token *tokens, size_t *i)
{
	int sign = 1;
	double coef = 1;
	size_t power = 0;

	if (tokens[*i].type == SIGN) {
		if (tokens[*i].str[0] == '-')
			sign = -1;
		(*i)++;
	}
	if (tokens[*i].type == FLOAT || tokens[*i].type == INT) {
		coef = strtod(tokens[*i].str, NULL);
		(*i)++;
	}
	if (tokens[*i].type == OP)
		(*i)++;
	if (tokens[*i].type == VAR) {
		(*i)++;
		power = 1;
		if (tokens[*i].type == POW) {
			(*i)++;
			power = strtoul(tokens[*i].str, NULL, 10);
			(*i)++;
		}
	}
	Term res = {sign * coef, power};
	return res;
}

static Polynom extract_term(Token *tokens, size_t *i)
{
	size_t idx = 0;
	Polynom poly = {NULL, 0};

	poly.size = count_term(tokens, *i);
	poly.terms = malloc(sizeof(Term) * poly.size);
	if (!poly.terms) {
		ft_putstr(RED "Error: MALLOC FAIL" RESET "\n");
		return poly;
	}
	while (tokens[*i].type != END && tokens[*i].type != EQUAL) {
		Term t = parse_term(tokens, i);
		poly.terms[idx] = t;
		idx++;
	}
	if (tokens[*i].type == EQUAL)
		(*i)++;
	return poly;
}

int parse(Token *tokens, Polynom *left, Polynom *right)
{
	size_t i = 0;

	*left = extract_term(tokens, &i);
	if (!left->terms && left->size != 0)
		return 1;
	*right = extract_term(tokens, &i);
	if (!right->terms && left->size != 0)
		return 1;
	return 0;
}
