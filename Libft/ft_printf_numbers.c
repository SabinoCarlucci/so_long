/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:09:29 by scarlucc          #+#    #+#             */
/*   Updated: 2024/07/24 17:09:50 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_printf(int n, int *printed)
{
	char	digit;
	long	l;

	l = n;
	if (l < 0)
	{
		ft_putchar_printf('-', printed);
		l = -l;
	}
	digit = '0' + (l % 10);
	if (l > 9)
		ft_putnbr_printf((l / 10), printed);
	write(1, &digit, 1);
	*printed += 1;
}

void	ft_uns_printf(unsigned int l, int *printed)
{
	char	digit;

	digit = '0' + (l % 10);
	if (l > 9)
		ft_uns_printf((l / 10), printed);
	write(1, &digit, 1);
	*printed += 1;
}

void	ft_convert_hex(unsigned int number, char low_up, int *printed)
{
	char	*tab;

	if (low_up == 'x')
		tab = "0123456789abcdef";
	else
		tab = "0123456789ABCDEF";
	if (number >= 16)
		ft_convert_hex((number / 16), low_up, printed);
	ft_putchar_printf(tab[number % 16], printed);
}

void	ft_pointer(uintptr_t point, int *printed)
{
	char	*tab;

	tab = "0123456789abcdef";
	if (point >= 16)
		ft_pointer((point / 16), printed);
	ft_putchar_printf(tab[point % 16], printed);
}

void	ft_start_pointer(uintptr_t point, int *printed)
{
	if (point == 0)
	{
		ft_putstr_printf("(nil)", printed);
		return ;
	}
	ft_putchar_printf('0', printed);
	ft_putchar_printf('x', printed);
	ft_pointer(point, printed);
}
