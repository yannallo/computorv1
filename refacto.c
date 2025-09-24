#include "computorv1.h"

static size_t get_max_power(Polynom left, Polynom right)
{
	size_t power = 0;

	for (size_t i = 0; i < left.size; i++)
	{
		if (left.terms[i].power > power)
			power = left.terms[i].power;
	}
	for (size_t i = 0; i < right.size; i++)
	{
		if (right.terms[i].power > power)
			power = right.terms[i].power;
	}
	return power;
}

double *refacto(Polynom *left, Polynom *right, size_t *max_power)
{
	double *coefs;

	*max_power = get_max_power(*left, *right);
	coefs = malloc(sizeof(double) * (*max_power + 1));
	if (!coefs) {
		ft_putstr("Error: MALLOC FAIL\n");
		return NULL;
	}
	for (size_t i = 0; i < *max_power + 1; i++)
		coefs[i] = 0;
	for (size_t i = 0; i < left->size; i++)
		coefs[left->terms[i].power] += left->terms[i].coef;
	for (size_t i = 0; i < right->size; i++)
		coefs[right->terms[i].power] -= right->terms[i].coef;
	return coefs;
}
