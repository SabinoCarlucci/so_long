/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:08:22 by scarlucc          #+#    #+#             */
/*   Updated: 2024/09/06 12:58:25 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**check_input(int argc, char **argv, t_map *map, char	*line)
{
	int		fd;
	char	*point;
	size_t	map_rows;

	if (argc != 2)
		error_msg(ERR_ARGS);
	point = ft_strrchr(argv[1], '.');
	if (point == NULL || ft_strncmp(point, ".ber", 5) != 0)
		error_msg(ERR_FORMAT);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_msg(ERR_OPEN);
	line = get_next_line(fd);
	if (!line)
		error_msg(ERR_EMPTY_OR_FOLDER);
	map_rows = 0;
	while (line)
	{
		map_rows++;
		free(line);
		line = get_next_line(fd);
	}//se hai problemi di memoria, prova a chiamare get_next_line una volta extra per liberare buffer
	close(fd);
	map->rows = map_rows;
	return (make_matrix_solong(map_rows, argv[1]));
}

void	check_rect(char	**map_matrix, t_map	*map)
{
	size_t	row_matrix;

	row_matrix = 0;
	while (map_matrix[row_matrix])
	{
		if (row_matrix == 0)
			map->columns = (int)ft_strlen_mod(map_matrix[row_matrix]);//togli da ciclo, tanto lo fai solo una volta
		if ((int)ft_strlen_mod(map_matrix[row_matrix]) != map->columns)
		{
			free_matrix(map_matrix, map->rows);
			error_msg(ERR_RECT);
		}
		check_walls_and_chars(map_matrix, map, row_matrix);
		row_matrix++;
	}
	//map.rows = row_matrix;//questo decommenta se non riesci a mettere assegnazione righe matrice in check_input
}
//mi pare questa non funzioni, mentre quelle prima si, controlla
void	check_walls_and_chars(char	**mat, t_map *map, int l_cnt)
{
	char	*allowed;
	int		c_cnt;
	int		a_cnt;

	c_cnt = -1;
	while (mat[l_cnt][++c_cnt] != '\0' && mat[l_cnt][c_cnt] != '\n')
	{
		a_cnt = -1;
		if (l_cnt == 0 || l_cnt == map->rows - 1
			|| c_cnt == 0 || c_cnt == (map->columns - 1))
			allowed = "1\0";
		else
			allowed = "10CEP\0";
		while (allowed[++a_cnt] != '\0')
		{
			if (mat[l_cnt][c_cnt] == allowed[a_cnt])
				break ;
			if (allowed[a_cnt + 1] == '\0')
			{
				free_matrix(mat, map->rows);
				error_msg(ERR_CHAR);
			}
		}
	}
}

void	check_duplicates(char **map_matrix, t_map *map, int	l_cnt)
{
	int	count;

	while (l_cnt < map->rows)
	{
		count = 0;
		while (count < map->columns)
		{
			if (map_matrix[l_cnt][count] == 'C')
				map->collectible++;
			if (map_matrix[l_cnt][count] == 'E')
				map->exit++;
			if (map_matrix[l_cnt][count] == 'P')
				map->player++;
			count++;
		}
		l_cnt++;
	}
	if (l_cnt == map->rows)
	{
		if (map->collectible <= 0 || map->exit != 1 || map->player != 1)
		{
			free_matrix(map_matrix, map->rows);
			error_msg(ERR_DUP_OR_MISS);
		}
	}
}
void	flood_fill(char **copy_matrix, t_map *map, int	l_cnt, int	c_cnt)
{
	if (copy_matrix[l_cnt][c_cnt] == '1' || copy_matrix[l_cnt][c_cnt] == 'x' || copy_matrix[l_cnt][c_cnt] == 'N')
		return ;
	copy_matrix[l_cnt][c_cnt] = 'x';
	flood_fill(copy_matrix, map, l_cnt + 1, c_cnt);
	flood_fill(copy_matrix, map, l_cnt - 1, c_cnt);
	flood_fill(copy_matrix, map, l_cnt, c_cnt + 1);
	flood_fill(copy_matrix, map, l_cnt, c_cnt - 1);
}

void	flood_fill_check(t_map *map, int	l_cnt, int	c_cnt)
{
	while (l_cnt < map->rows)
	{
		while (c_cnt < map->columns)
		{
			if (map->copy_matrix[l_cnt][c_cnt] == 'C' || map->copy_matrix[l_cnt][c_cnt] == 'E' || map->copy_matrix[l_cnt][c_cnt] == 'P')
			{
				free_matrix(map->copy_matrix, map->rows);
				free_matrix(map->map_matrix, map->rows);
				error_msg(ERR_PATH);
			}
			c_cnt++;
		}
		c_cnt = 0;
		l_cnt++;
	}
}

char	**parsing(int argc, char **argv, t_data data)
{
	char	*line;

	line = NULL;
	data.map->map_matrix = check_input(argc, argv, data.map, line);
	check_rect(data.map->map_matrix, data.map);
	check_duplicates(data.map->map_matrix, data.map, 0);
	data.map->copy_matrix = make_matrix_solong(data.map->rows, argv[1]);
	flood_fill(data.map->copy_matrix, data.map, 1, 1);
	flood_fill_check(data.map, 0, 0);
	free_matrix(data.map->copy_matrix, data.map->rows);
	return (data.map->map_matrix);
}
