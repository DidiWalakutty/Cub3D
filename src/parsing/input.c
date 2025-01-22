#include "cub3d.h"

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
char	*read_file(const char *pathname)
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

int	handle_input(const char *filename, char ***lines)
{
	char	*file_content;

	file_content = read_file(filename);
	if (!file_content)
		return (1);
	printf("File content:\n%s\n", file_content);
	if (is_file_empty(file_content))
	{
		printf("File is empty\n");
		free(file_content);
		return (1);
	}
	*lines = ft_split(file_content, '\n');
	free(file_content);
	if (!*lines)
		return 1;
	printf("Split was successful\n");
	return (0);
}
