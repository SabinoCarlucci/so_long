/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:26:56 by scarlucc          #+#    #+#             */
/*   Updated: 2024/09/10 22:42:29 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	movement(int x, int y, t_data *data)
{
	int	finish[2];
	char	end;

	finish[0] = data->map->start_p[0];
	finish[1] = data->map->start_p[1];
	if (x > 0)
		finish[0] = finish[0] + 1;
	else if (x < 0)
		finish[0] = finish[0] - 1;
	else if (y > 0)
		finish[1] = finish[1] + 1;
	else if (y < 0)
		finish[1] = finish[1] - 1;
	end = data->map->map_matrix[finish[0]][finish[1]];
	if ((end == 'E' && data->map->collectible == 0) || (end != '1' && end != 'E'))
	{
		data->map->moves++;
		ft_printf("you moved %i times\n", data->map->moves);
		update_map(end, finish[0], finish[1], data);
		data->map->start_p[0] = finish[0];
		data->map->start_p[1] = finish[1];
	}	
}

void	update_map(char end, int finish_x, int finish_y, t_data *data)
{
	int	start_x;
	int	start_y;
	int	exit_x;
	int	exit_y;

	start_x = data->map->start_p[0];
	start_y = data->map->start_p[1];
	exit_x = data->map->exit_p[0];
	exit_y = data->map->exit_p[1];
	data->map->map_matrix[finish_x][finish_y] = 'P';
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[5], finish_y * SIZE, finish_x * SIZE);
	data->map->map_matrix[start_x][start_y] = '0';
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[0], start_y * SIZE, start_x * SIZE);
	if (end == 'C')
	{
		if (data->map->collectible == 1)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[3], exit_y * SIZE, exit_x * SIZE);
		data->map->collectible--;
	}
	else if (end == 'E' && data->map->collectible == 0)
	{
		ft_printf("You win!\n");
		on_destroy(data);
	}
}
