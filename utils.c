/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:11:44 by scarlucc          #+#    #+#             */
/*   Updated: 2024/09/06 12:01:14 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_msg(char *msg)
{
	ft_printf("Error\n");
	ft_printf("%s\n", msg);
	exit(1);
}

char	**make_matrix_solong(size_t	map_rows, char	*map_file)
{
	int		fd;
	char	*line;
	char	**out;
	size_t	chars_line;

	out = ft_calloc(map_rows + 1, sizeof(char *));
	if (!out)
		return (NULL);
	out[map_rows] = NULL;
	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	chars_line = 0;
	while (line)
	{
		out[chars_line] = line;
		out[chars_line][ft_strlen(line)] = '\0';
		line = get_next_line(fd);
		chars_line++;
	}
	close(fd);
	return (out);
}

t_map	*init_map_struct(void)
{
	t_map	*map_struct;

	map_struct = malloc(sizeof(t_map));
	if (!map_struct)
		return (NULL);
	map_struct->rows = 0;
	map_struct->columns = 0;
	map_struct->collectible = 0;
	map_struct->player = 0;
	map_struct->exit = 0;
	map_struct->map_matrix = NULL;
	map_struct->copy_matrix = NULL;
	return (map_struct);
}

size_t	ft_strlen_mod(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	if (s[count - 1] == '\n')
		count--;
	return (count);
}
