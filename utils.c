#include "computorv1.h"

size_t ft_strlen(char *str)
{
	size_t i = 0;
	while (str[i])
		i++;
	return i;
}

int ft_putstr(char *str)
{
	return write(1, str, ft_strlen(str));
}

int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == ' ' || c == '\r');
}

char *ft_substr(char *str, int offset, int len)
{
	char *buf;
	size_t size;

	if (!str || offset < 0 || len < 0)
		return NULL;
	size = ft_strlen(str) - offset;
	if (size > (size_t)len)
		size = len;
	buf = malloc(sizeof(char) * (size + 1));
	if (!buf)
		return NULL;
	for (size_t i = 0; i < size; i++)
		buf[i] = str[i+offset];
	buf[size] = '\0';
	return buf;
}

char *ft_strchr(char *str, int c)
{
	size_t i = 0;

	if (!str)
		return NULL;

	while (str[i])
	{
		if (str[i] == c)
			return str + i;
		i++;
	}
	return NULL;
}

void free_all(Token *tokens, Term *l, Term *r)
{
	size_t i = 0;
	if (tokens) {
		while (tokens[i].type) {
			if (tokens[i].str)
				free(tokens[i].str);
			i++;
		}
		free(tokens);
	}
	if (l)
		free(l);
	if (r)
		free(r);
}	
