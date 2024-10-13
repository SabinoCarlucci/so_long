/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_and_movement_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:26:56 by scarlucc          #+#    #+#             */
/*   Updated: 2024/10/13 20:03:41 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	images_to_window(char	**map_matrix, t_data	data, int row, int col)
{
	while (map_matrix[row] != NULL)
	{
		col = 0;
		while (map_matrix[row][col] != '\0' && map_matrix[row][col] != '\n')
		{
			images_to_window2(map_matrix, data, row, col);
			col++;
		}
		row++;
	}
}

void	load_textures(t_data *data)
{
	int	size;

	size = SIZE;
	data->txr[0] = mlx_xpm_file_to_image(data->mlx_ptr, EMPTY, &size, &size);
	data->txr[1] = mlx_xpm_file_to_image(data->mlx_ptr, WALL, &size, &size);
	data->txr[2] = mlx_xpm_file_to_image(data->mlx_ptr, COLLECT, &size, &size);
	data->txr[3] = mlx_xpm_file_to_image(data->mlx_ptr, COLLECT2, &size, &size);
	data->txr[4] = mlx_xpm_file_to_image(data->mlx_ptr, EXIT_OPEN,
			&size, &size);
	data->txr[5] = mlx_xpm_file_to_image(data->mlx_ptr, EXIT_CLOSED,
			&size, &size);
	data->txr[6] = mlx_xpm_file_to_image(data->mlx_ptr, PLAYER,
			&size, &size);
	data->txr[7] = mlx_xpm_file_to_image(data->mlx_ptr, ENEMY,
			&size, &size);
	data->txr[8] = mlx_xpm_file_to_image(data->mlx_ptr, ENEMY2,
			&size, &size);
	data->txr[9] = NULL;
}

void	destroy_textures(t_data *data)
{
	int	textures_count;

	textures_count = 0;
	while (textures_count < NUM_ELE && data->txr[textures_count])
	{
		mlx_destroy_image(data->mlx_ptr, data->txr[textures_count]);
		textures_count++;
	}
}

void	movement(int x, int y, t_data *data)
{
	int		finish[2];
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
	if ((end == 'E' && data->map->collect == 0) || (end != '1' && end != 'E'))
		count_moves(data);
	update_map(end, finish[0], finish[1], data);
	animation(data->map->map_matrix, data, 0, 0);
	data->map->start_p[0] = finish[0];
	data->map->start_p[1] = finish[1];
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->txr[6],
		finish_y * SIZE, finish_x * SIZE);
	data->map->map_matrix[start_x][start_y] = '0';
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->txr[0],
		start_y * SIZE, start_x * SIZE);
	update_map_check(data, end, exit_x, exit_y);
}
