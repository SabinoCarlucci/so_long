/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:26:56 by scarlucc          #+#    #+#             */
/*   Updated: 2024/08/26 18:27:01 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_mlx(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	return (0);
}
/* tentativo di aprire una finestra preso da questo sito

https://reactive.so/post/42-a-comprehensive-guide-to-so_long
 */