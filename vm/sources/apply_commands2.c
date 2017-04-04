/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:02:53 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/22 21:39:55 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/global.h"

int		check_player_nb(int nb, t_all *gen)
{
	int i;

	i = 0;
	while (i < gen->how_many_players)
	{
		if ((gen->players_nb)[i] == nb)
			return (1);
		i = i + 1;
	}
	return (0);
}

void	move_pc(t_process *p, int delta)
{
	p->lpc = p->pc;
	p->pc = p->pc + delta;
}

int		c_b_quant(unsigned char coding_byte, t_op op)
{
	int				i;
	int				ret;
	unsigned char	code;

	i = 0;
	ret = 0;
	while (i < op.nb_param)
	{
		code = (coding_byte >> (6 - i * 2)) & 0b11;
		if (code == REG_CODE)
			ret = ret + 1;
		else if (code == IND_CODE)
			ret = ret + 2;
		else if (code == DIR_CODE)
		{
			if (op.dir_twoby == 1)
				ret = ret + 2;
			else
				ret = ret + 4;
		}
		i = i + 1;
	}
	return (ret);
}
