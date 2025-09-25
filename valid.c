#include "computorv1.h"

static Token *valid_equation(Token *tokens)
{
	size_t i = 0;
	TYPE next;
	TYPE cur = tokens[0].type;

	while (tokens[i+1].type != END)
	{
		cur = tokens[i].type;
		next = tokens[i+1].type;
		
		if ((cur == INT || cur == FLOAT) && !(next == EQUAL || next == OP || next == SIGN || next == VAR))
			return tokens+i+1;
		else if (cur == OP && !(next == INT || next == FLOAT || next == VAR))
			return tokens+i+1;
		else if (cur == SIGN && !(next == INT || next == FLOAT || next == VAR))
			return tokens+i+1;
		else if (cur == VAR && !(next == EQUAL || next == OP || next == SIGN || next == POW))
			return tokens+i+1;
		else if (cur == POW && next != INT)
			return tokens+i+1;
		else if (cur == EQUAL && !(next == INT || next == FLOAT || next == SIGN || next == VAR))
			return tokens+i+1;
		else if (next == POW && cur != VAR)
			return tokens+i+1;
		else if (next == OP && !(cur == INT || cur == FLOAT))
			return tokens+i+1;
		i++;
	}
	if (next == EQUAL) {
		ft_putstr("Invalid syntax: Missing right side of equation\n");
		return tokens + i + 1;
	}
	if (!(next == INT || next == FLOAT || next == VAR)) {
		ft_putstr("Invalid syntax: right side of equation\n");
		return tokens + i;
	}
	return NULL;
}

static int valid_numbers(Token *tokens)
{
	size_t i = 0;
	char *endptr;

	while (tokens[i].type != END) {
		if (tokens[i].type == FLOAT) {
			double tmp = strtod(tokens[i].str, &endptr);
			if (tmp == HUGE_VAL || tmp == -HUGE_VAL || tmp == DBL_MIN || endptr[0]) {
				printf("Error: invalid convertion '%s'\n", tokens[i].str);
				return 1;
			}
		}
		else if (tokens[i].type == INT) {
			size_t tmp = strtoul(tokens[i].str, &endptr, 10);
			if (tmp == ULONG_MAX || endptr[0]) {
				printf("Error: invalid convertion '%s'\n", tokens[i].str);
				return 1;
			}
		}
		i++;
	}
	return 0;
}

int valid(Token *tokens)
{
	TYPE cur = tokens[0].type;

	if (cur == EQUAL) {
		ft_putstr("Invalid syntax: Missing left side of equation\n");
		return 1;
	}
	if (cur == OP || cur == POW) {
		printf("Invalid syntax: Left side of equation can't start with '%s'\n", tokens[0].str);
		return 1;
	}
	Token *tmp = valid_equation(tokens);
	if (tmp) {
		if (tmp->type != END)
			printf("Invalid syntax: '%s'\n", tmp->str);
		return 1;
	}
	if (valid_numbers(tokens))
		return 1;
	return 0;
}
