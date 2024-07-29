/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:11:44 by scarlucc          #+#    #+#             */
/*   Updated: 2024/07/29 19:16:54 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	init_map_struct(void)
{
	t_map	map_struct;

	map_struct.rows = 0;
	map_struct.columns = 0;
	return (map_struct);
}
