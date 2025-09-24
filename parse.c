#include "computorv1.h"

static Token *valid_equation(Token *tokens)
{
	size_t i = 0;
	bool var = false;
	TYPE next;
	TYPE cur = tokens[0].type;

	if (!(cur == SIGN || cur == INT || cur == FLOAT || cur == VAR || cur == END)) {
		printf("Invalid syntax: left side of equation\n");
		return tokens;
	}
	while (tokens[i+1].type != END)
	{
		cur = tokens[i].type;
		next = tokens[i+1].type;

		if (!var && (cur == VAR || next == VAR))
			var = true;
		if ((cur == INT || cur == FLOAT) && !(next == EQUAL || next == OP || next == SIGN || next == VAR))
			return tokens+i+1;
		else if (cur == OP && !(next == INT || next == FLOAT || next == VAR))
			return tokens+i+1;
		else if (cur == SIGN && !(next == INT || next == FLOAT || next == VAR))
			return tokens+i+1;
		else if (cur == VAR && !(next == EQUAL || next == OP || next == SIGN || next == POW))
			return tokens+i+1;
		else if (cur == POW && !(next == INT || next == FLOAT))
			return tokens+i+1;
		else if (cur == EQUAL && !(next == INT || next == FLOAT || next == SIGN || next == VAR))
			return tokens+i+1;
		else if (next == POW && cur != VAR)
			return tokens+i+1;
		else if (next == OP && !(cur == INT || cur == FLOAT))
			return tokens+i+1;
		i++;
	}
	if (!(next == INT || next == FLOAT || next == VAR)) {
		printf("Invalid syntax: right side of equation\n");
		return tokens + i + 1;
	}
	if (!var) {
		printf("Invalid syntax: Missing a variable 'X'\n");
		return tokens + i + 1;
	}
	return NULL;
}

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
		ft_putstr("Error: MALLOC FAIL\n");
		return poly;
	}
	while (tokens[*i].type != END && tokens[*i].type != EQUAL) {
		Term t = parse_term(tokens, i);
		if (t.coef == HUGE_VAL || t.coef == -HUGE_VAL || t.coef == DBL_MIN || t.power == ULONG_MAX) {
			printf("ERROR: INVALID CONVERTION\n");
			poly.size = 0;
			return poly;
		}
		poly.terms[idx] = t;
		idx++;
	}
	if (tokens[*i].type == EQUAL)
		(*i)++;
	return poly;
}

int parse(Token *tokens, Polynom *left, Polynom *right)
{
	Token *tmp = valid_equation(tokens);
	if (tmp) {
		if (tmp->type != END)
			printf("Invalid syntax: '%s'\n", tmp->str);
		return 1;
	}
	size_t i = 0;

	*left = extract_term(tokens, &i);
	if (!left->terms && left->size != 0)
		return 1;
	*right = extract_term(tokens, &i);
	if (!right->terms && left->size != 0)
		return 1;
	return 0;
}
