#include "computorv1.h"

static size_t count(char *str, int sep)
{
	size_t i = 0;
	size_t count = 0;

	while (str[i])
	{
		if (str[i] != sep)
		{
			while (str[i] && str[i] != sep)
				i++;
			count++;
		}
		else
			i++;
	}

	return count;
}

char **ft_split(char *str, int sep)
{
	char **split = NULL;
	size_t idx = 0;
	size_t i = 0;
	size_t len = 0;

	if (!str)
		return NULL;

	idx = count(str, sep);
	if (idx == 0)
		return NULL;
	
	split = malloc(sizeof(char *) * (idx + 1));
	if (!split)
		return NULL;
	split[idx] = NULL;

	idx = 0;
	while (str[i])
	{
		if (str[i] != sep)
		{
			len = 0;
			while (str[i + len] != sep && str[i + len])
				len++;
			split[idx] = ft_substr(str, i, len);
			if (!split[idx])
				return (free_array(split), NULL);
			i += len;
			idx++;
		}
		else
			i++;
	}

	return split;
}
