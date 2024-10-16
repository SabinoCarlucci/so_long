/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:16:08 by scarlucc          #+#    #+#             */
/*   Updated: 2024/10/11 19:15:20 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

//error_msg
# define ERR_ARGS ": incorrect arguments number"
# define ERR_EMPTY_OR_FOLDER ": file empty or directory"
# define ERR_FORMAT ": incorrect file format"
# define ERR_OPEN ": open failed"
# define ERR_RECT ": map not rectangular"
# define ERR_CHAR ": invalid character in map"
# define ERR_DUP_OR_MISS ": map needs at least 1 C and exactly 1 P and E"
# define ERR_PATH ": no valid path from Player to Collectibles and Exit"

# define SIZE 50
# define NUM_ELE 8

//allowed characters
# define ALLOWED "10CEP\0"
# define ALLOWED_BONUS "10CEPN\0"
# define ONLY_WALL "1\0"

//textures
# define EMPTY "assets/0_empty.xpm"
# define WALL "assets/1_wall.xpm"
# define COLLECT "assets/C_collectible.xpm"
# define EXIT_OPEN "assets/E_exit_open.xpm"
# define EXIT_CLOSED "assets/E_exit_closed.xpm"
# define PLAYER "assets/P_player.xpm"
# define ENEMY "assets/N_enemy.xpm"

//keysym
# define KEY_ESC 65307
# define KEY_A 97
# define ARROW_LEFT 65361
# define KEY_W 119
# define ARROW_UP 65362
# define KEY_D 100
# define ARROW_RIGHT 65363
# define KEY_S 115
# define ARROW_DOWN 65364

typedef struct map
{
	int		rows;
	int		col;
	int		collect;
	int		player;
	int		exit;
	char	**map_matrix;
	int		moves;
	int		start_p[2];
	int		exit_p[2];
}				t_map;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*txr[NUM_ELE];
	t_map		*map;
}				t_data;

//main.c
int			close_game(t_data *data);
int			on_keypress(int keysym, t_data *data);
char		**parsing(int argc, char **argv, t_data data);
void		load_txr_and_open_window(t_data *data);
//main

//checks.c
char		**check_input(int argc, char **argv, t_data data, char	*line);
void		check_rect(char	**map_matrix, t_data data);
void		check_walls_and_chars(char	**mat, t_data data, int l_cnt);
void		check_cep(char **map_matrix, t_data data, int l_cnt, int count);
void		flood_fill(char **map_matrix, t_map *map, int l_cnt, int c_cnt);

//leftover.c
void		floodfill_check(char **copy_matrix, t_data data,
				int l_cnt, int c_cnt);
void		update_map_check(t_data *data, char end, int exit_x, int exit_y);

//utils.c
void		free_map(t_data *data);
void		error_msg(char *msg, t_data data);
char		**make_matrix_solong(size_t	map_rows, char	*map_file);
t_map		*init_map_struct(void);
size_t		ft_strlen_mod(const char *s);

//txr_and_movement.c
void		images_to_window(char **map_matrix, t_data	data, int row, int col);
void		load_textures(t_data *data);
void		destroy_textures(t_data *data);
void		movement(int x, int y, t_data *data);
void		update_map(char end, int finish_x, int finish_y, t_data *data);

#endif