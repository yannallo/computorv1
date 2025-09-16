#include "computorv1.h"

int main(int ac, char **av)
{
	if (ac < 2) {
		ft_putstr("Error: No polynomial given\n");
		return 0;
	}
	if (ac > 2) {
		ft_putstr("Error: Too much arguments\n");
		return 0;
	}
	if (ft_strlen(av[1]) == 0) {
		ft_putstr("Error: No polynomia given\n");
	       	return 0;
	}

	Data *data = malloc(sizeof(Data));
	if (!data) {
		ft_putstr("Error: MALLOC FAIL\n");
		return 0;
	}
	if (parse(data, av[1]))
		return 0;

	refacto(data);
	solve(data->left);

	free_list(data->left);
	free_list(data->right);
	free(data);
	return 0;
}
