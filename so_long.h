/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:16:08 by scarlucc          #+#    #+#             */
/*   Updated: 2024/09/06 11:49:32 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "Libft/libft.h"
# include "mlx_linux/mlx.h"
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

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

# define EMPTY "assets/0_empty.xpm"
# define WALL "assets/1_wall.xpm"
# define COLLECT "assets/C_collectible.xpm"
# define EXIT_OPEN "assets/E_exit(open).xpm"
# define EXIT_CLOSED "assets/E_exit(closed).xpm"
# define PLAYER "assets/P_player.xpm"
# define ENEMY "assets/N_enemy.xpm"

typedef struct map//metti qui dentro la matrice in cui copi la mappa, sara' piu' facile lavorarci
{
	int		rows;
	int		columns;
	int		collectible;
	int		player;
	int		exit;
	char	**map_matrix;
	char	**copy_matrix;
}				t_map;

typedef struct s_data
{
	void		*mlx_ptr; // MLX pointer
	void		*win_ptr; // MLX window pointer
	void		*textures[NUM_ELE]; // MLX image pointers (on the stack)
	t_map		*map; // Map pointer (contains map details - preferably kept on the stack)
}				t_data;

//checks.c
char		**parsing(int argc, char **argv, t_data data);
void		error_msg(char *msg);
char		**check_input(int argc, char **argv, t_map *map, char	*line);
void		check_rect(char	**map_matrix, t_map	*map_struct);
void		check_walls_and_chars(char	**mat, t_map *map, int l_cnt);
void		check_duplicates(char **map_matrix, t_map *map, int l_cnt);
void		flood_fill(char **map_matrix, t_map *map, int	l_cnt, int	c_cnt);
void		flood_fill_check(t_map *map, int	l_cnt, int	c_cnt);
char		**make_matrix_solong(size_t	map_rows, char	*map_file);

//utils.c
t_map		*init_map_struct(void);
size_t		ft_strlen_mod(const char *s);
void		load_textures(t_data *data);
void	images_to_window(char	**map_matrix, t_data	data, int	row, int	col);

#endif