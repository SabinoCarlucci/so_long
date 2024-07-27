/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:08:22 by scarlucc          #+#    #+#             */
/*   Updated: 2024/07/27 20:25:39 by scarlucc         ###   ########.fr       */
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
		error_msg("incorrect arguments number");
	point = ft_strrchr(argv[1], '.');
	if (point == NULL || ft_strncmp(point, ".ber", 4) != 0)
		error_msg("incorrect file format");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_msg("open failed");
	else
	{
		for (int i = 0; i < 8; ++i) {
			line = get_next_line(fd);
			ft_printf("%s", line);
			free(line);
		}
	}
	close(fd);
}
