/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leftover_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:51:06 by scarlucc          #+#    #+#             */
/*   Updated: 2024/10/13 20:05:44 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->txr[4],
				exit_y * SIZE, exit_x * SIZE);
		data->map->collect--;
	}
	else if (end == 'E' && data->map->collect == 0)
	{
		ft_printf("You win!\n");
		close_game(data);
	}
	else if (end == 'N')
	{
		ft_printf("You lose!\n");
		close_game(data);
	}
}

void	animation(char **map_matrix, t_data *data, int l_cnt, int count)
{
	while (l_cnt < data->map->rows)
	{
		count = 0;
		while (count < data->map->col)
		{
			if (map_matrix[l_cnt][count] == 'C' && data->map->moves % 2 == 0)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->txr[2], count * SIZE, l_cnt * SIZE);
			else if (map_matrix[l_cnt][count] == 'C'
				&& data->map->moves % 2 != 0)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->txr[3], count * SIZE, l_cnt * SIZE);
			else if (map_matrix[l_cnt][count] == 'N'
				&& data->map->moves % 2 == 0)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->txr[7], count * SIZE, l_cnt * SIZE);
			else if (map_matrix[l_cnt][count] == 'N'
				&& data->map->moves % 2 != 0)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->txr[8], count * SIZE, l_cnt * SIZE);
			count++;
		}
		l_cnt++;
	}
}

void	images_to_window2(char	**map_matrix, t_data	data, int row, int col)
{
	if (map_matrix[row][col] == '0')
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.txr[0],
			col * SIZE, row * SIZE);
	else if (map_matrix[row][col] == '1')
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.txr[1],
			col * SIZE, row * SIZE);
	else if (map_matrix[row][col] == 'C')
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.txr[2],
			col * SIZE, row * SIZE);
	else if (map_matrix[row][col] == 'E')
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.txr[5],
			col * SIZE, row * SIZE);
	else if (map_matrix[row][col] == 'P')
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.txr[6],
			col * SIZE, row * SIZE);
	else if (map_matrix[row][col] == 'N')
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.txr[7],
			col * SIZE, row * SIZE);
}

void	count_moves(t_data *data)
{
	char	*tmp;

	data->map->moves++;
	tmp = ft_itoa(data->map->moves);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->txr[1], 0, 0);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 5, 10, 000000, tmp);
	free(tmp);
	if (data->map->moves > 999)
	{
		ft_printf("Too many moves.\nYou lose!\n");
		close_game(data);
	}
}
