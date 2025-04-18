/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 12:25:48 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/03/26 20:17:58 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//#define READ_BUFFER_SIZE 1024

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>

/*
** Character Class Tests
*/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
/*
** String Functions
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *src, int c, size_t n);
void	*ft_memset(void *buffer, int value, size_t len);
void	ft_bzero(void *s, size_t n);

/*
** Utility Functions
*/
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/*
** Functions for writing
*/
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*
** Bonus Part - Linked Lists 
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// typedef struct s_reader
// {
// 	int		fd;
// 	char	buffer[READ_BUFFER_SIZE];
// 	int		buffer_pos;
// 	int		buffer_size;
// }				t_reader;

/*
** The Bonus Functions
*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* get_next_line */
char	*get_next_line(int fd);
char	*read_from_fd(int fd, char *read_chunk);
char	*get_line_from_buffer(char *remaining_buffer);
char	*remove_returned_line(char *remaining_buffer, int *flag);
char	*ftt_strjoin(char *s1, char *s2);
char	*allocate_memory(int i);
void	copy_characters(char *remaining_buffer, char *extracted_line);

/* ft_fgets */
// char	*custom_fgets(char *dest, int size, t_reader *reader);
// void	file_reader_init(t_reader *reader, int fd);

#endif