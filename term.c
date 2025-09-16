#include "computorv1.h"

size_t get_size(Term *list)
{
	size_t i = 0;

	while (list)
	{
		i++;
		list = list->next;
	}
	return i;
}

Term *get_tail(Term *list)
{
	while (list->next)
		list = list->next;
	return list;
}

Term *create_node(void){
	Term *new = NULL;

	new = malloc(sizeof(Term));
	if (!new)
		return NULL;
	new->str = NULL;
	new->coef = 0;
	new->exponent = 0;
	new->next = NULL;
	return new;
}

void add_node(Term **list, Term *node)
{
	if (!*list)
	{
		*list = node;
		return ;
	}
	Term *tail = get_tail(*list);
	tail->next = node;
}

void remove_node(Term **list, Term *node)
{
	if (*list == NULL || node == NULL)
		return;

	if (*list == node)
	{
		*list = (*list)->next;
		free_node(node);
		return ;
	}

	Term *tmp = *list;
	while (tmp->next != NULL && tmp->next != node)
		tmp = tmp->next;

	if (tmp->next != NULL)
	{
		tmp->next = node->next;
		free_node(node);
	}
}

void free_node(Term *node)
{
	if (node == NULL)
		return;

	if (node->str)
		free(node->str);
	free(node);
}

void free_list(Term *list)
{
	Term *tmp;
	
	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void print_node(Term *node)
{
	if (node->coef < 0)
		printf("%g", -node->coef);
	else
		printf("%g", node->coef);

	if (node->exponent == 1)
		printf("X");
	else if (node->exponent > 1)
		printf("X^%d", node->exponent);

}

void print_list(Term *list)
{
	while (list)
	{
		printf("(%g X^%d) ", list->coef, list->exponent);
		list = list->next;
	}
	printf("\n");
}

void fill_term(Term *term)
{
	char *buf;

	if (!term)
		return;
	if (!ft_isdigit(term->str[0]) && !ft_isdigit(term->str[1]))
	{
		if (term->str[0] == '-')
			term->coef = -1;
		else
			term->coef = 1;
	}
	else
		term->coef = atof(term->str);
	buf = ft_strstr(term->str, "X");
	if (buf)
	{
		buf = ft_strstr(term->str, "X^");
		if (buf)
			term->exponent = atoi(buf+2);
		else
			term->exponent = 1;
	}
	else
		term->exponent = 0;
}

Term *get_node(Term *list, size_t exponent)
{
	if (list == NULL)
		return NULL;

	while (list && list->exponent != exponent)
		list = list->next;
	return list;
}

double get_coef(Term *list, size_t exponent)
{
	if (list == NULL)
		return 0;

	while (list)
	{
		if (list->exponent == exponent)
			return list->coef;
		list = list->next;
	}
	return 0;
}
