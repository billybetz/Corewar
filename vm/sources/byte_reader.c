/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:37:12 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/22 22:15:05 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	byte_reader(int *number, unsigned char *mem, int start, int len)
{
	int i;

	i = 0;
	*number = 0;
	while (i < len)
	{
		if ((i == 0) && (len > 1))
		{
			if (mem[start % MEM_SIZE] & 0b10000000)
			{
				if (len == 2)
					*number = -0x8000;
				if (len == 4)
					*number = -0x80000000;
			}
			*number = *number + ((mem[(start + i) % MEM_SIZE] & 0b01111111)
					<< ((len - i - 1) * 8));
		}
		else
			*number = *number + (mem[(start + i) % MEM_SIZE]
					<< ((len - i - 1) * 8));
		i = i + 1;
	}
}

void	byte_writer(int number, t_all *gen, int start, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		(gen->clr)[(start + i) % MEM_SIZE] = gen->tmp_clr;
		(gen->mem)[(start + i) % MEM_SIZE] = (number >> (8 * (len - i - 1)));
		if (gen->curses == 1)
			put_membyte((start + i) % MEM_SIZE, gen, 0);
		i++;
	}
}

char	*get_player_name(t_all *gen, int nb)
{
	t_file *f;

	f = (gen->arg)->files;
	while (f != NULL)
	{
		if ((f != NULL) && (f->n == nb))
			return (f->prog_name);
		f = f->nxt;
	}
	return (NULL);
}

void	change_carry(int result, char *carry)
{
/*	if (*carry == 0)
		*carry = 1;
	else
		*carry = 0;*/
	if (result == 0)
		*carry = 1;
	else
		*carry = 0;
}
