// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   ft_fgets.c                                         :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2025/01/20 17:48:42 by ykarimi       #+#    #+#                 */
// /*   Updated: 2025/01/20 17:55:34 by ykarimi       ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "libft.h"

// void	file_reader_init(t_reader *reader, int fd)
// {
// 	reader->fd = fd;
// 	reader->buffer_pos = 0;
// 	reader->buffer_size = 0;
// }

// char	*custom_fgets(char *dest, int size, t_reader *reader)
// {
// 	int	dest_pos;
// 	int	newline_found;
// 	char	c;

// 	newline_found = 0;
// 	dest_pos = 0;
// 	while (dest_pos < size - 1 && !newline_found)
// 	{
// 		if (reader->buffer_pos >= reader->buffer_size)
// 		{
// 			reader->buffer_size = read(reader->fd, reader->buffer, READ_BUFFER_SIZE);
// 			reader->buffer_pos = 0;
// 			if (reader->buffer_size == -1)
// 				return (perror("Read error"), NULL);
// 			if (reader->buffer_size == 0)
// 				break ;
// 		}
// 		while (reader->buffer_pos < reader->buffer_size && dest_pos < size - 1)
// 		{
// 			c = reader->buffer[reader->buffer_pos++];
// 			dest[dest_pos++] = c;
// 			if (c == '\n')
// 			{
// 				newline_found = 1;
// 				break;
// 			}
// 		}
// 	}
// 	if (dest_pos == 0)
// 		return (NULL);
// 	dest[dest_pos] = '\0';
// 	return (dest);
// }
