/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:25:52 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/23 00:03:55 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cmd_add(t_all *gen, t_process *p)
{
	int				par[3];
	unsigned char	coding_byte;

	coding_byte = (gen->mem)[(p->pc + 1) % MEM_SIZE];
	if (coding_byte != 0b01010100)
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	byte_reader(&par[0], gen->mem, p->pc + 2, 1);
	byte_reader(&par[1], gen->mem, p->pc + 3, 1);
	byte_reader(&par[2], gen->mem, p->pc + 4, 1);
	if (par[0] >= 1 && par[0] <= 16 && par[1] >= 1 && par[1] <= 16
			&& par[2] >= 1 && par[2] <= 16)
	{
		(p->reg)[par[2]] = (p->reg)[par[0]] + (p->reg)[par[1]];
		change_carry((p->reg)[par[2]], &(p->carry));
	}
	move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}

void	cmd_sub(t_all *gen, t_process *p)
{
	int				par[3];
	unsigned char	coding_byte;

	coding_byte = (gen->mem)[(p->pc + 1) % MEM_SIZE];
	if (coding_byte != 0b01010100)
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	byte_reader(&par[0], gen->mem, p->pc + 2, 1);
	byte_reader(&par[1], gen->mem, p->pc + 3, 1);
	byte_reader(&par[2], gen->mem, p->pc + 4, 1);
	if (par[0] >= 1 && par[0] <= 16 && par[1] >= 1 && par[1] <= 16
			&& par[2] >= 1 && par[2] <= 16)
	{
		(p->reg)[par[2]] = (p->reg)[par[0]] - (p->reg)[par[1]];
		change_carry((p->reg)[par[2]], &(p->carry));
	}
	move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}

void	cmd_and2(t_all *gen, t_process *p, int ret[2], unsigned char c_byte)
{
	int		par[3];

	par[0] = p->param;
	if ((ret[1] = get_param(p, gen->mem, p->pc + 2 + ret[0], 0)) == -1)
	{
//		ft_printf("c\n");
		move_pc(p, c_b_quant(c_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	par[1] = p->param;
	byte_reader(&par[2], gen->mem, p->pc + ret[0] + ret[1] + 2, 1);
	if (par[2] < 1 || par[2] > 16)
	{
		ft_printf("d\n");
		move_pc(p, c_b_quant(c_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	(p->reg)[par[2]] = par[0] & par[1];
//
//	ft_printf("and%dand\n", (p->reg)[par[2]]);
//
	change_carry((p->reg)[par[2]], &(p->carry));
	move_pc(p, c_b_quant(c_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}

void	cmd_and(t_all *gen, t_process *p)
{
	unsigned char	coding_byte;
	unsigned char	code[2];
	int				ret[2];

	coding_byte = (gen->mem)[(p->pc + 1) % MEM_SIZE];
	code[0] = (coding_byte >> 6);
	code[1] = (coding_byte >> 4) & 0b11;
	if (((coding_byte >> 2) & 0b11) != REG_CODE || code[1] == 0 || code[0] == 0)
	{
//		ft_printf("a\n");
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = code[0];
	if ((ret[0] = get_param(p, gen->mem, p->pc + 2, 0)) == -1)
	{
//		ft_printf("b\n");
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = code[1];
	cmd_and2(gen, p, ret, coding_byte);
}
