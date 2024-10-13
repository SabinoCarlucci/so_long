/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leftover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:51:06 by scarlucc          #+#    #+#             */
/*   Updated: 2024/09/21 15:30:41 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	floodfill_check(char **copy_matrix, t_data data, int l_cnt, int c_cnt)
{
	while (l_cnt < data.map->rows)
	{
		while (c_cnt < data.map->col)
		{
			if (copy_matrix[l_cnt][c_cnt] == 'C'
			|| copy_matrix[l_cnt][c_cnt] == 'E'
			|| copy_matrix[l_cnt][c_cnt] == 'P')
			{
				free_matrix(copy_matrix, data.map->rows);
				error_msg(ERR_PATH, data);
			}
			c_cnt++;
		}
		c_cnt = 0;
		l_cnt++;
	}
}

void	update_map_check(t_data *data, char end, int exit_x, int exit_y)
{
	if (end == 'C')
	{
		if (data->map->collect == 1)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->txr[3],
				exit_y * SIZE, exit_x * SIZE);
		data->map->collect--;
	}
	else if (end == 'E' && data->map->collect == 0)
	{
		ft_printf("You win!\n");
		close_game(data);
	}
}
