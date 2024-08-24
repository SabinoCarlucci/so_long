/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:52:24 by scarlucc          #+#    #+#             */
/*   Updated: 2024/08/24 14:34:43 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_map	o_map;
	char	**map_matrix;
	char	*line;

	o_map = init_map_struct();
	map = &o_map;
	line = NULL;
	map_matrix = check_input(argc, argv, map, line);
	check_rect(map_matrix, map);
	check_duplicates(map_matrix, map, 0);
	return (0);
}
