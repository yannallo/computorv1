#include "computorv1.h"

void ft_putstr(char *str)
{
	size_t len = ft_strlen(str);
	write(1, str, len);
}

size_t ft_strlen(char *str)
{
	size_t i = 0;
	
	while (str[i])
		i++;
	return i;
}

char *ft_strstr(char *fullstr, char *substr)
{
	size_t substr_len = ft_strlen(substr) - 1;
	size_t i = 0;
	size_t j = 0;

	if (!fullstr || !substr)
		return NULL;
	while (fullstr[i])
	{
		j = 0;
		while (fullstr[i + j] == substr[j] && fullstr[i+j])
		{
			if (j >= substr_len)
				return (fullstr + i);
			j++;
		}
		i++;
	}
	return NULL;
}

char *ft_strchr(char *str, int c)
{
	size_t i = 0;

	if (str == NULL)
		return NULL;

	while (str[i])
	{
		if (str[i] == c)
			return str + i;
		i++;
	}
	return NULL;
}

int ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
}

int ft_isdigit(int c)
{
	return (c > 47 && c < 58);
}

void free_array(char **array)
{
	size_t i = 0;

	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char *ft_substr(char *str, int offset, int len)
{
	size_t i = 0;
	char *buf = NULL;
	
	if (offset + len > ft_strlen(str))
		return NULL;
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return NULL;
	while (i < len)
	{
		buf[i] = str[offset + i];
		i++;
	}
	buf[i] = '\0';
	
	return buf;
}
