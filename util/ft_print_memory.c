/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:55:34 by jihalee           #+#    #+#             */
/*   Updated: 2023/02/13 09:54:13 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	putstr_hex(void *addr, int size, char *hex)
{
	int		i;

	i = 0;
	while (i < size)
	{
		ft_putchar(hex[*(unsigned char *)(addr + i) / 16]);
		ft_putchar(hex[*(unsigned char *)(addr + i) % 16]);
		if (i % 2 == 1)
			ft_putchar (' ');
		i++;
	}
	while (i < 16)
	{
		ft_putchar(' ');
		ft_putchar(' ');
		if (i % 2 == 1)
			ft_putchar (' ');
		i++;
	}
}

void	putstr_non_printable(void *addr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (*((unsigned char *)(addr + i)) >= 32
			&& *((unsigned char *)(addr + i)) <= 126)
			ft_putchar(*((unsigned char *)(addr + i)));
		else
			ft_putchar('.');
		i++;
	}
	ft_putchar('\n');
}

void	print_address(void *addr, char *hex)
{
	char			result[16];
	unsigned long	long_addr;
	int				i;

	long_addr = (unsigned long)addr;
	i = 15;
	while (i >= 0)
	{
		result[i] = hex[long_addr % 16];
		long_addr /= 16;
		i--;
	}
	i = 0;
	while (i < 16)
	{
		ft_putchar(result[i]);
		i++;
	}
	ft_putchar(':');
	ft_putchar(' ');
	return ;
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	i;
	char			*hex;

	hex = "0123456789abcdef";
	i = 0;
	while (i < size)
	{
		if (size - i >= 16)
		{
			print_address(addr + i, hex);
			putstr_hex(addr + i, 16, hex);
			putstr_non_printable(addr + i, 16);
			i += 16;
		}
		else if (size - i < 16)
		{
			print_address(addr + i, hex);
			putstr_hex(addr + i, size - i, hex);
			putstr_non_printable(addr + i, size - i);
			break ;
		}
	}
	return (addr);
}
