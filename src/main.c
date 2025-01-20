#include "cub3d.h"

void	print_error(char *errormsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(errormsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

// int	check_arguments(int argc, char *argv[])
// {
// 	if (argc != 2)
// 		return (print_error("Too many arguments provided"), 1);
// }
int	validate_map_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		return (print_error("Map extension is not correct."), 1);
	return (0);
}

/*
might need to improve the logic of this function, and/or get_next_line
*/
char	*read_file(char *pathname)
{
	int		fd;
	char	*line;
	char	*line_joined;
	char	*temp;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (print_error("Could not open file"), NULL);
	line_joined = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		temp = ft_strjoin(line_joined, line);
		free(line_joined);
		line_joined = temp;
		free(line);
	}
	close(fd);
	return (line_joined);
}

bool	is_file_empty(char *file_content)
{
	if (*file_content == '\0')
		return (true);
	return (false);
}


int	extract_elements_from_file(char *file_content)
{
	char	**lines;

	lines = ft_split(file_content, '\n');
	if (!lines)
		return (1);
}


int	parse_file(int argc, char *argv[])
{
	char	*file_content;

	if (argc != 2)
		return (print_error("Too many or few arguments provided"), 1);
	if (validate_map_extension(argv[1]) == 1)
		return (1);
	file_content = read_file(argv[1]);
	if (!file_content)
		return (1);
	// printf("line is: %s\n", file_content);
	// free(file_content);
	if (!is_file_empty(file_content))
	{
		free(file_content);
		return (1);
	}
	extract_elements_from_file(file_content);
	return (0);
}


// parse_map()
// {

// }

int main(int argc, char *argv[])
{
	// char **map;
	// t_map map;

	parse_file(argc, argv);

	return 0;
}