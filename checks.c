/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:08:22 by scarlucc          #+#    #+#             */
/*   Updated: 2024/07/31 19:08:38 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_msg(char *msg)
{
	ft_printf("Error\n");
	ft_printf("%s\n", msg);
	exit(1);
}

void	check_input(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	*point;

	if (argc != 2)
		error_msg(ERR_ARGS);
	point = ft_strrchr(argv[1], '.');
	if (point == NULL || ft_strncmp(point, ".ber", 4) != 0)
		error_msg(ERR_FORMAT);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_msg(ERR_OPEN);
	line = get_next_line(fd);
	if (!line)
		error_msg(ERR_EMPTY_OR_FOLDER);
	free(line);
	close(fd);
}

void	check_map(char	*map_file, t_map	map)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "\n", 1))
		{
			if (map.rows == 0)
				map.columns = (int)ft_strlen_mod(line);
			if ((int)ft_strlen_mod(line) != map.columns)
			{
				free(line);
				error_msg(ERR_RECT);
			}
			map.rows++;
		}
		free(line);
		line = get_next_line(fd);
	}//se hai problemi di memoria, prova a chiamare get_next_line una volta extra per liberare buffer
	if (map.rows < 3)//probabilemtne togliere 
		error_msg(ERR_ROWS);
	close(fd);
	check_walls_and_chars(map_file, map);
}

void	check_line(char	*line, t_map map, int rows)
{
	char	*allowed;
	int		l_cnt;
	int		a_count;

	l_cnt = 0;
	while (line[l_cnt] != '\0' && line[l_cnt] != '\n')
	{
		a_count = 0;
		if (!rows || rows == map.rows || !l_cnt || l_cnt == (map.columns - 1))
			allowed = "1\0";
		else
			allowed = "10CEP\0";
		while (allowed[a_count] != '\0')
		{
			if (line[l_cnt] == allowed[a_count])
				break ;
			a_count++;
			if (allowed[a_count] == '\0')
			{
				free(line);
				error_msg(ERR_CHAR);
			}
		}
		l_cnt++;
	}
}

void	check_walls_and_chars(char	*map_file, t_map	map)
{
	int		rows;
	int		fd;
	char	*line;

	rows = 0;
	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	while (rows < map.rows)
	{
		check_line(line, map, rows);
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
