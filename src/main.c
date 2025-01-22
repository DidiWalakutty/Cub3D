#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_input	file_data;

	if (argc != 2)
		return (print_error("Too many or few arguments provided"), 1);
	ft_bzero(&file_data, sizeof(file_data));
	if (parse_file(argv, &file_data) == 1)
	{
		return (1);
	}
	return (0);
}
