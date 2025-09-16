#include "computorv1.h"

static void add_coef(Term **list)
{
	Term *cur = *list;
	Term *next;
	Term *target;

	if (*list == NULL)
		return;
	while (cur)
	{
		next = cur->next;
		while (next)
		{
			if (cur->exponent == next->exponent)
			{
				cur->coef += next->coef;
				target = next;
				next = next->next;
				remove_node(list, target);
			}
			else
				next = next->next;
		}
		cur = cur->next;
	}
}

static void rm_coef(Term **list)
{
	Term *cur = *list;

	while (cur)
	{
		if (cur->coef == 0)
			remove_node(list, cur);
		cur = cur->next;
	}
}

void refacto(Data *data)
{
	add_coef(&(data->left));
	add_coef(&(data->right));
	rm_coef(&(data->left));
	rm_coef(&(data->right));

	while (data->right)
	{
		Term *node = data->right;

		data->right = data->right->next;
		node->coef = -node->coef;
		node->next = NULL;
		add_node(&(data->left), node);
	}
	add_coef(&(data->left));
	rm_coef(&(data->left));
}
