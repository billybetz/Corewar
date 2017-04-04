/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:21:42 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/21 19:21:44 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_dir_code(t_process *p, unsigned char *mem, int start, char dir2b_l)
{
	int j;

	j = 4;
	if ((dir2b_l & 0b10) != 0)
		j = 2;
	byte_reader(&(p->param), mem, start, j);
	return (j);
}

int		get_ind_address(unsigned char *mem, int start)
{
	int out;

	out = 0;
	if (mem[start % MEM_SIZE] & 0b10000000)
		out = -0x8000;
	out = out + ((mem[start % MEM_SIZE] & 0b01111111) << 8);
	out = out + mem[(start + 1) % MEM_SIZE];
	return (out);
}

int		get_param(t_process *p, unsigned char *mem, int start, char dir2b_l)
{
	int out;

	out = 0;
	if (p->code == REG_CODE)
	{
		byte_reader(&(p->param), mem, start, 1);
		if (p->param < 1 || p->param > 16)
			return (-1);
		p->param = p->reg[p->param];
		out = 1;
	}
	else if (p->code == DIR_CODE)
		out = get_dir_code(p, mem, start, dir2b_l);
	else if (p->code == IND_CODE)
	{
//		ft_printf("olaolaola\n");
//		byte_reader(&(p->param), mem, start, 2);
		p->param = get_ind_address(mem, start);
//		ft_printf("%d\n", p->param);
		if ((dir2b_l & 0b1) != 0)
			byte_reader(&(p->param), mem, start + p->param, REG_SIZE);
		else
			byte_reader(&(p->param), mem,
					start + (p->param % IDX_MOD), REG_SIZE);
		out = 2;
	}
	return (out);
}
