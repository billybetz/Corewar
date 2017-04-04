/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:45:57 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/23 00:08:00 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cmd_aff(t_all *gen, t_process *p)
{
	unsigned int	coding_byte;
	int				param;

	coding_byte = (gen->mem)[(p->pc + 1) % MEM_SIZE];
	if ((coding_byte >> 6 != REG_CODE) || ((coding_byte & 0b111111) != 0))
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	byte_reader(&param, gen->mem, p->pc + 2, 1);
	if (param < 1 || param > 16)
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	if (gen->curses == 0)
		ft_putchar(p->reg[param % 256]);
	move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}
