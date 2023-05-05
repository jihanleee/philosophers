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

void	print_ulong(unsigned long nbr, int radix, char *base, int *n_bytes)
{
	if (nbr >= (unsigned long)radix)
		print_ulong(nbr / radix, radix, base, n_bytes);
	ft_putchar_count(base[nbr % radix], n_bytes);
}

void	print_nbr_base_u(unsigned int nbr, int radix, char *base, int *n_bytes)
{
	if (nbr >= (unsigned int)radix)
		print_nbr_base(nbr / radix, radix, base, n_bytes);
	ft_putchar_count(base[nbr % radix], n_bytes);
}

void	print_nbr_base(int nbr, int radix, char *base, int *n_bytes)
{
	long	nbr_long;

	nbr_long = (long)nbr;
	if (nbr_long < 0)
	{
		ft_putchar_count('-', n_bytes);
		nbr_long *= -1;
	}
	if (nbr_long >= radix)
		print_nbr_base(nbr_long / radix, radix, base, n_bytes);
	ft_putchar_count(base[nbr_long % radix], n_bytes);
}

void	ft_putnbr_base_count(int nbr, char *base, int *n_bytes)
{
	int	radix;

	radix = 0;
	while (base[radix])
		radix++;
	print_nbr_base(nbr, radix, base, n_bytes);
}
