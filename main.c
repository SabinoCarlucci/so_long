/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:52:24 by scarlucc          #+#    #+#             */
/*   Updated: 2024/09/21 15:55:26 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game(t_data *data)
{
	destroy_textures(data);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_map(data);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC)
		close_game(data);
	else if (keysym == KEY_D || keysym == ARROW_RIGHT)
		movement(0, 1, data);
	else if (keysym == KEY_A || keysym == ARROW_LEFT)
		movement(0, -1, data);
	else if (keysym == KEY_W || keysym == ARROW_UP)
		movement(-1, 0, data);
	else if (keysym == KEY_S || keysym == ARROW_DOWN)
		movement(1, 0, data);
	return (0);
}

char	**parsing(int argc, char **argv, t_data data)
{
	char	*line;
	char	**copy_matrix;

	line = NULL;
	data.map->map_matrix = check_input(argc, argv, data, line);
	check_rect(data.map->map_matrix, data);
	check_cep(data.map->map_matrix, data, 0, 0);
	copy_matrix = make_matrix_solong(data.map->rows, argv[1]);
	flood_fill(copy_matrix, data.map, data.map->start_p[0],
		data.map->start_p[1]);
	floodfill_check(copy_matrix, data, 0, 0);
	free_matrix(copy_matrix, data.map->rows);
	return (data.map->map_matrix);
}

void	load_txr_and_open_window(t_data *data)
{
	load_textures(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			(data->map->col * SIZE), (data->map->rows * SIZE),
			"Stickman Adventure");
	if (!data->win_ptr)
	{
		destroy_textures(data);
		free(data->map);
		free(data->mlx_ptr);
		exit (1);
	}
	images_to_window(data->map->map_matrix, *data, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.map = init_map_struct();
	if (!data.map)
		return (1);
	data.map->map_matrix = parsing(argc, argv, data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		free(data.map);
		return (1);
	}
	load_txr_and_open_window(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, &on_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, &close_game, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
