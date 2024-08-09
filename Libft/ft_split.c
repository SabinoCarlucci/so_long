/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:31:30 by scarlucc          #+#    #+#             */
/*   Updated: 2024/08/08 12:17:40 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//static char	**free_matrix(char **matrix, size_t sub_done);
//static char	**make_matrix(char const *s_str, char sep, size_t n_str, int count);

char	**free_matrix(char **matrix, size_t sub_done)
{
	size_t	count;

	count = 0;
	while (count <= sub_done)
	{
		free(matrix[count]);
		count++;
	}
	free(matrix);
	return (NULL);
}

char	**make_matrix(char const *s_str, char sep, size_t n_str, int count)
{
	char	**matrix;
	size_t	sub_don;
	size_t	startsub;
	size_t	endsub;

	matrix = malloc(sizeof(char *) * (n_str + 1));
	if (!matrix)
		return (NULL);
	matrix[n_str] = NULL;
	sub_don = 0;
	while (sub_don < n_str)
	{
		while (s_str[count] == sep && s_str[count] != '\0')
			count++;
		startsub = count;
		while (s_str[count] != sep && s_str[count] != '\0')
			count++;
		endsub = count;
		matrix[sub_don] = ft_substr(s_str, startsub, (endsub - startsub));
		if (!matrix[sub_don])
			return (free_matrix(matrix, sub_don));
		sub_don++;
	}
	return (matrix);
}

char	**ft_split(char const *s_str, char sep)
{
	int		count;
	size_t	n_str;

	count = 0;
	n_str = 0;
	while (s_str[count] != '\0')
	{
		while (s_str[count] == sep && s_str[count] != '\0')
			count++;
		if (s_str[count] != sep && s_str[count] != '\0')
			n_str++;
		while (s_str[count] != sep && s_str[count] != '\0')
			count++;
	}
	count = 0;
	return (make_matrix(s_str, sep, n_str, count));
}
//paco -s sbaglia, fai valgrind con questo main e non ci sono leak
/*
int main(void)
{
    char *str = "hello";
    char c = ' ';

	int i = 0;
    char **array = ft_split(str, c);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}*/
