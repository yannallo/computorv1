#include "computorv1.h"

static int check_char(char *str)
{
	size_t i = 0;
	char *buf = "0123456789/*-+=X^., ";

	while (str[i])
	{
		if (!ft_strchr(buf, str[i]))
		{
			ft_putstr("Error: Unexpected symbol in equation");
			return 1;
		}
		i++;
	}
	if (!ft_strchr(str, '='))
	{
		ft_putstr("Error: No equality, can't solve");
		return 1;
	}

	return 0;
}

static char *rm_space(char *str)
{
	size_t i = 0;
	size_t j = 0;

	while (str[i])
	{
		if (!ft_isblank(str[i]))
		{
			str[j] = str[i];
			j++;
		}	
		i++;
	}
	str[j] = '\0';
	
	return str;
}

static size_t term_len(char *str)
{
	size_t i = 0;

	if (!str)
		return 0;
	
	while (str[i])
	{
		if ((str[i] == '+' || str[i] == '-') && i > 0)
			return i;
		i++;
	}
	return i;
}

static Term *split_term(char *str)
{
	Term *new = NULL;
	Term *list = NULL;
	size_t i = 0;
	size_t len = 0;

	while (str[i])
	{
		len = term_len(str+i);
		if (len == 0)
			return (free_list(list), NULL);
		new = create_node();
		if (!new)
			return (free_list(list), NULL);
		new->str = ft_substr(str, i, len);
		if (!new->str)
			return (free_list(list), NULL);
		fill_term(new);
		add_node(&list, new);
		i += len;
	}
	return list;
}

int parse(Data *data, char *str)
{
	char **split = NULL;

	str = rm_space(str);
	if (check_char(str))
		return 1;
	split = ft_split(str, '=');
	if (!split)
		return 1;
	data->left = split_term(split[0]);
	if (!data->left)
		return (free_array(split), 1);
	data->right = split_term(split[1]);
	if (!data->right)
		return (free_array(split), 1);
	free_array(split);
	return 0;
}

