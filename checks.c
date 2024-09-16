/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:08:22 by scarlucc          #+#    #+#             */
/*   Updated: 2024/09/12 18:50:39 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**check_input(int argc, char **argv, t_data data, char	*line)
{
	int		fd;
	char	*point;
	size_t	map_rows;

	if (argc != 2)
		error_msg(ERR_ARGS, data);
	point = ft_strrchr(argv[1], '.');
	if (point == NULL || ft_strncmp(point, ".ber", 5) != 0)
		error_msg(ERR_FORMAT, data);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_msg(ERR_OPEN, data);
	line = get_next_line(fd);
	if (!line)
		error_msg(ERR_EMPTY_OR_FOLDER, data);
	map_rows = 0;
	while (line)
	{
		map_rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	data.map->rows = map_rows;
	return (make_matrix_solong(map_rows, argv[1]));
}

void	check_rect(char	**map_matrix, t_data data)
{
	size_t	row_matrix;

	row_matrix = 0;
	data.map->col = (int)ft_strlen_mod(map_matrix[row_matrix]);
	while (map_matrix[row_matrix])
	{
		if ((int)ft_strlen_mod(map_matrix[row_matrix]) != data.map->col)
			error_msg(ERR_RECT, data);
		check_walls_and_chars(map_matrix, data, row_matrix);
		row_matrix++;
	}
}

void	check_walls_and_chars(char	**mat, t_data data, int l_cnt)
{
	char	*allowed;
	int		c_cnt;
	int		a_cnt;

	c_cnt = -1;
	while (mat[l_cnt][++c_cnt] != '\0' && mat[l_cnt][c_cnt] != '\n')
	{
		a_cnt = -1;
		if (l_cnt == 0 || l_cnt == data.map->rows - 1
			|| c_cnt == 0 || c_cnt == (data.map->col - 1))
			allowed = ONLY_WALL;
		else
			allowed = ALLOWED;
		while (allowed[++a_cnt] != '\0')
		{
			if (mat[l_cnt][c_cnt] == allowed[a_cnt])
				break ;
			if (allowed[a_cnt + 1] == '\0')
				error_msg(ERR_CHAR, data);
		}
	}
}

void	check_cep(char **map_matrix, t_data data, int l_cnt, int count)
{
	while (l_cnt < data.map->rows)
	{
		count = 0;
		while (count < data.map->col)
		{
			if (map_matrix[l_cnt][count] == 'C')
				data.map->collect++;
			else if (map_matrix[l_cnt][count] == 'E')
			{
				data.map->exit++;
				data.map->exit_p[0] = l_cnt;
				data.map->exit_p[1] = count;
			}
			else if (map_matrix[l_cnt][count] == 'P')
			{
				data.map->player++;
				data.map->start_p[0] = l_cnt;
				data.map->start_p[1] = count;
			}
			count++;
		}
		l_cnt++;
	}
	if (data.map->collect <= 0 || data.map->exit != 1 || data.map->player != 1)
		error_msg(ERR_DUP_OR_MISS, data);
}

void	flood_fill(char **copy_matrix, t_map *map, int l_cnt, int c_cnt)
{
	if (copy_matrix[l_cnt][c_cnt] == '1' || copy_matrix[l_cnt][c_cnt] == 'E'
		|| copy_matrix[l_cnt][c_cnt] == 'x')
		return ;
	copy_matrix[l_cnt][c_cnt] = 'x';
	flood_fill(copy_matrix, map, l_cnt + 1, c_cnt);
	flood_fill(copy_matrix, map, l_cnt - 1, c_cnt);
	flood_fill(copy_matrix, map, l_cnt, c_cnt + 1);
	flood_fill(copy_matrix, map, l_cnt, c_cnt - 1);
}
