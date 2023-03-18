#include "lem_in.h"

int	ant_checker(char *line) {
	int	i;
	int ants;

	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (i == ft_strlen(line) && i != 0)
	{
		ants = ft_atoi(line);
		free(line);
		return (ants);
	}
	free(line);
	return (-1);
}