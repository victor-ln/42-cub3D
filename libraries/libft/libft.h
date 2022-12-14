/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 04:21:22 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/08/08 04:21:22 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

/*
	Compares both strings s1 and s2 and returns the difference
	between them or zero if they're equal.
*/
int				ft_strcmp(char *s1, char *s2);

/*
	Returns a pointer to a new string which is
	a duplicate of the string s.
*/
char			*ft_strdup(const char *s);

/*
	Allocates with malloc() and returns a new
	string, which is the result of the concatenation
	of ’s1’ and ’s2’.
*/
char			*ft_strjoin(char const *s1, char const *s2);

/*
	Returns how many characters are in the given string excluding the '\0'.
*/
size_t			ft_strlen(const char *str);

/*
	Allocates memory for an array of nmemb elements of size bytes
	each and returns a pointer to the allocated memory.
	The memory is set to zero. If nmemb or size is 0, then returns NULL.
*/
void			*ft_calloc(size_t nmemb, size_t size);

/*
	Outputs the string ’s’ to the given file
	descriptor, followed by a newline.
*/
void			ft_putendl_fd(char *s, int fd);

/*
	Erases the data in the n bytes of the memory
	starting at the location pointed to by s, by writing zeros (bytes
	containing '\0') to that area.
*/
void			ft_bzero(void *s, size_t n);

/*
	Generates random numbers.
*/
unsigned int	ft_rand(void);

/*
	Delays the execution of a program for m_secs.
*/
void			ft_delay(int m_secs);

/*
	Copies n bytes from memory area src to memory area dest. 
	The memory areas must not overlap.
*/
void			*ft_memcpy(void *dest, const void *src, size_t len);

/*
	Frees a pointer and set it to NULL
*/
void			ft_free_null(void **ptr);

int				ft_isspace(int c);

char			*ft_substr(char const *s, unsigned int start, size_t len);

char			**ft_split(char const *s, char c);

void			ft_free_matrix(void **matrix, size_t size);

size_t			ft_count_vectors(void **matrix);

int				ft_isdigit(int c);

char			*ft_strchr(const char *s, int c);

char			*ft_strrchr(const char *src, int c);

int				ft_strncmp(const char *s1, const char *s2, size_t n);

int				ft_atoi(const char *str);

int				ft_count_char(char *str, char c);

char			*ft_itoa(int nbr);

#endif
