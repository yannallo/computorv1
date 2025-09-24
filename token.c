#include "computorv1.h"

static int get_token(int c)
{
	if (c == '-' || c == '+')
		return SIGN;
	else if (c == '=')
		return EQUAL;
	else if (c == '*')
		return OP;
	else if (c == '^')
		return POW;
	else if (c == 'X')
		return VAR;
	return 0;
}

static char *rm_space(char *str) {
	size_t i = 0;
	size_t j = 0;

	while (str[i]) {
		while (str[j] == ' ')
			j++;
		str[i] = str[j];
		i++;
		j++;
	}
	return str;
}

static int check_char(char *str) {
	size_t i = 0;
	size_t count = 0;

	while (str[i]) {
		if (!ft_strchr("0123456789*-+.X^=", str[i])) {
			printf("Invalid syntax: '%c' not valid\n", str[i]);
			return 1;
		}
		if (str[i] == '=')
			count++;
		i++;
	}
	if (count == 0) {
		ft_putstr("Invalid syntax: Missing an equality\n");
		return 1;
	}
	else if (count != 1) {
		ft_putstr("Invalid syntax: Multiple '='\n");
		return 1;
	}
	return 0;
}

static size_t get_token_size(char *str) {
	size_t i = 0;
	size_t count = 0;

	while (str[i]) {
		TYPE token = get_token(str[i]);
		
		if (token) {
			count++;
			token = 0;
		}
		else if (ft_isdigit(str[i])) {
			while (str[i+1] && (ft_isdigit(str[i+1]) || str[i+1] == '.'))
				i++;
			count++;
		}
		i++;
	}
	return count;
}

static int fill_tokens(char *str, Token *tokens) {
	size_t i = 0;
	size_t j = 0;
	size_t idx = 0;

	while (str[i]) {
		TYPE token = get_token(str[i]);
		tokens[idx].str = ft_substr(str, i, 1);
		
		if (token)
			tokens[idx].type = token;
		else if (ft_isdigit(str[i])) {
			j = i;		
			tokens[idx].type = INT;
			while (str[j+1] && (ft_isdigit(str[j+1]) || str[j+1] == '.')) {
				if (str[j+1] == '.')
					tokens[idx].type = FLOAT;
				j++;
			}
			free(tokens[idx].str);
			tokens[idx].str = ft_substr(str, i, j-i+1);
			i = j;
		}
		if (!tokens[idx].str) {
			ft_putstr("Error: MALLOC FAIL\n");
			return 1;
		}
		idx++;
		i++;
	}
	tokens[idx].type = END;
	return 0;
}

Token *tokenize(char *str)
{
	str = rm_space(str);
	if (check_char(str))
		return NULL;
	Token *tokens = malloc(sizeof(Token) * (get_token_size(str) + 1));
	if (!tokens) {
		ft_putstr("Error: MALLOC FAIL\n");
		return NULL;
	}
	if (fill_tokens(str, tokens)) {
		ft_putstr("Error: Number is out of range\n"); 
		free(tokens);
		return NULL;
	}
	return tokens;
}

