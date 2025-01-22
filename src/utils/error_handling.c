#include "cub3d.h"

void	print_error(char *errormsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(errormsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
