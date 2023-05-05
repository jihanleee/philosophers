/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:28:06 by jihalee           #+#    #+#             */
/*   Updated: 2023/05/04 17:55:46 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

void	ft_putchar_count(char c, int *n_bytes)
{
	write(1, &c, 1);
	(*n_bytes)++;
}

void	ft_putstr_count(char *str, int *n_bytes)
{
	int	i;

	if (str == 0)
	{
		ft_putstr_count("(null)", n_bytes);
		return ;
	}
	i = 0;
	while (str[i])
	{
		ft_putchar_count(str[i], n_bytes);
		i++;
	}
}

void	print_p(void *addr, int *n_bytes)
{
	char			*hex;
	unsigned long	long_addr;

	hex = "0123456789abcdef";
	if (addr == 0)
	{
		ft_putstr_count("(nil)", n_bytes);
		return ;
	}
	long_addr = (unsigned long)addr;
	ft_putstr_count("0x", n_bytes);
	print_ulong(long_addr, 16, hex, n_bytes);
}
