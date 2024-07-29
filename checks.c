/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:08:22 by scarlucc          #+#    #+#             */
/*   Updated: 2024/07/29 19:39:10 by scarlucc         ###   ########.fr       */
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
		perror("Error\n");
	free(line);
	/* {
		for (int i = 0; i < 8; ++i) {
			line = get_next_line(fd);
			if (!line)
			{
				perror("Error\n");
				free(line);
				break ;
			}
			ft_printf("%s", line);
			free(line);
		}
	} */
	close(fd);
}

void	check_map(char	*map_file, t_map	map_struct)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "\n", 1))
			map_struct.rows++;
		free(line);
		line = get_next_line(fd);
	}//se hai problemi di memoria, prova a chiamare get_next_line una volta extra per liberare buffer
	if (map_struct.rows < 3)
		error_msg(ERR_ROWS);
}
