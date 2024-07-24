/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:52:24 by scarlucc          #+#    #+#             */
/*   Updated: 2024/07/24 18:21:34 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main()
{
	int	fd;
	char	*line;
	//stampa fd di file
	fd = open("map.ber", O_RDONLY);
	if (fd == -1)
		ft_printf("errore apertura file");
	else
	{
		ft_printf("fd file e' %i\n", fd);
		for (int i = 0; i < 8; ++i) {
			line = get_next_line(fd);
			ft_printf("%s", line);
			free(line);
		}
	}
	close(fd);
	return (0);
}