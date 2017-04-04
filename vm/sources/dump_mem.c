/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 16:19:36 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/15 17:04:45 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	put_hexchar(unsigned char c)
{
	unsigned char	first;
	unsigned char	second;

	first = c >> 4;
	second = c & 0b00001111;
	if (first == 0 && second == 0)
	{
		ft_printf(GRY"");
		ft_putchar(first + 48);
		ft_putchar(second + 48);
		ft_printf(CLN"");
	}
	else
	{
		ft_printf(GRN"");
		if (first <= 9)
			ft_putchar(first + 48);
		else
			ft_putchar(first + 87);
		if (second <= 9)
			ft_putchar(second + 48);
		else
			ft_putchar(second + 87);
		ft_printf(""CLN);
	}
}

void	dump_mem(unsigned char *mem, int size)
{
	int i;
	int j;
	int c;

	i = 0;
	c = 0;
	while (i < size)
	{
		j = 0;
		if (c < 10)
			ft_printf("  ");
		else if (c < 100)
			ft_printf(" ");
		ft_printf(WHT"%d| "CLN, c);
		while ((j < 32) && (i < size))
		{
			put_hexchar(mem[i]);
			if (j != 31)
				ft_putchar(' ');
			j = j + 1;
			i = i + 1;
		}
		ft_putchar('\n');
		c = c + 1;
	}
}
