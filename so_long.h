/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:16:08 by scarlucc          #+#    #+#             */
/*   Updated: 2024/07/31 18:15:55 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "Libft/libft.h"
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# define ERR_ARGS ": incorrect arguments number"
# define ERR_EMPTY_OR_FOLDER ": file empty or directory"
# define ERR_FORMAT ": incorrect file format"
# define ERR_OPEN ": open failed"
# define ERR_ROWS ": map needs 3 or more rows"
# define ERR_RECT ": map not rectangular"
# define ERR_CHAR ": invalid character in map"

typedef struct map
{
	int	rows;
	int	columns;
}				t_map;

//checks.c
void	error_msg(char *msg);
void	check_input(int argc, char **argv);
void	check_map(char	*map_file, t_map	map_struct);
void	check_line(char	*line, t_map	map, int rows);
void	check_walls_and_chars(char	*map_file, t_map	map);

//utils.c
t_map	init_map_struct(void);
size_t	ft_strlen_mod(const char *s);

#endif