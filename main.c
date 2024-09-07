/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:52:24 by scarlucc          #+#    #+#             */
/*   Updated: 2024/09/07 11:34:48 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	images_to_window(char	**map_matrix, t_data	data, int	row, int	col)
{
	while (map_matrix[row] != NULL)
	{
		col = 0;
		while (map_matrix[row][col] != '\0' && map_matrix[row][col] != '\n')
		{
			if (map_matrix[row][col] == '0')
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.textures[0], row * SIZE, col * SIZE);
			else if (map_matrix[row][col] == '1')
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.textures[1], row * SIZE, col * SIZE);
			else if (map_matrix[row][col] == 'C')
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.textures[2], row * SIZE, col * SIZE);
			else if (map_matrix[row][col] == 'E')
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.textures[4], row * SIZE, col * SIZE);
			else if (map_matrix[row][col] == 'P')
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.textures[5], row * SIZE, col * SIZE);
			col++;
		}
		row++;
	}
}

void	load_textures(t_data *data)
{
	int	size;

	size = SIZE;
	data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr, EMPTY, &size, &size);
	data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr, WALL, &size, &size);
	data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr, COLLECT, &size, &size);
	data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr, EXIT_OPEN, &size, &size);
	data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr, EXIT_CLOSED, &size, &size);
	data->textures[5] = mlx_xpm_file_to_image(data->mlx_ptr, PLAYER, &size, &size);
	data->textures[6] = mlx_xpm_file_to_image(data->mlx_ptr, ENEMY, &size, &size);
	data->textures[7] = NULL;
}

void	destroy_textures(t_data *data)
{
	int	textures_count;

	textures_count = 0;
	while (textures_count < NUM_ELE && data->textures[textures_count])
	{
		mlx_destroy_image(data->mlx_ptr, data->textures[textures_count]);
		textures_count++;
	}
}

int on_destroy(t_data *data)
{
	destroy_textures(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_matrix(data->map->map_matrix, data->map->rows);
	free(data->map);
	exit(0);
	return (0);
}

int on_keypress(int keysym, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\n", keysym);
	if (keysym == 65307)
		on_destroy(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.map = init_map_struct();
	if (!data.map)
		return (1);
	data.map->map_matrix = parsing(argc, argv, data);

	//apertura finestra e gestione
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		free(data.map);
		return (1);
	}

	load_textures(&data);//carica texture, amir lo fa dopo aver aperto finestra, ma pensa vada bene anche prima

	data.win_ptr = mlx_new_window(data.mlx_ptr, (data.map->rows * SIZE), (data.map->columns * SIZE), "I'm a window");
	if (!data.win_ptr)
	{
		destroy_textures(&data);
		free(data.map);
		return (free(data.mlx_ptr), 1);//controlla che sia compatibile con i free della matrice e della copia
	}

	images_to_window(data.map->map_matrix, data, 0, 0);

	// Register key press hook
	mlx_hook(data.win_ptr, 2, 1L << 0, &on_keypress, &data);

	// Register destroy hook
	mlx_hook(data.win_ptr, 17, 0, &on_destroy, &data);

	// Loop over the MLX pointer
	mlx_loop(data.mlx_ptr);
	
	destroy_textures(&data);
	free(data.mlx_ptr);
	free_matrix(data.map->map_matrix, data.map->rows);//creare una funzione che libera tutto e farla chiamare sia qui che in error_msg
	free(data.map);
	return (0);
}
