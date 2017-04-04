/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:25:59 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/23 00:05:02 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cmd_or2(t_all *gen, t_process *p, int ret[2], unsigned char c_byte)
{
	int		par[3];

	par[0] = p->param;
	if ((ret[1] = get_param(p, gen->mem, p->pc + 2 + ret[0], 0)) == -1)
	{
		move_pc(p, c_b_quant(c_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	par[1] = p->param;
	byte_reader(&par[2], gen->mem, p->pc + ret[0] + ret[1] + 2, 1);
	if (par[2] < 1 || par[2] > 16)
	{
		move_pc(p, c_b_quant(c_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	(p->reg)[par[2]] = par[0] | par[1];
	change_carry((p->reg)[par[2]], &(p->carry));
	move_pc(p, c_b_quant(c_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}

void	cmd_or(t_all *gen, t_process *p)
{
	unsigned char	coding_byte;
	unsigned char	code[2];
	int				ret[2];

	coding_byte = (gen->mem)[(p->pc + 1) % MEM_SIZE];
	code[0] = (coding_byte >> 6);
	code[1] = (coding_byte >> 4) & 0b11;
	if (((coding_byte >> 2) & 0b11) != REG_CODE || code[1] == 0 || code[0] == 0)
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = code[0];
	if ((ret[0] = get_param(p, gen->mem, p->pc + 2, 0)) == -1)
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = code[1];
	cmd_or2(gen, p, ret, coding_byte);
}

void	cmd_xor2(t_all *gen, t_process *p, int ret[2], unsigned char c_byte)
{
	int		par[3];

	par[0] = p->param;
	if ((ret[1] = get_param(p, gen->mem, p->pc + 2 + ret[0], 0)) == -1)
	{
		move_pc(p, c_b_quant(c_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	par[1] = p->param;
	byte_reader(&par[2], gen->mem, p->pc + ret[0] + ret[1] + 2, 1);
	if (par[2] < 1 || par[2] > 16)
	{
		move_pc(p, c_b_quant(c_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	(p->reg)[par[2]] = par[0] | par[1];
	change_carry((p->reg)[par[2]], &(p->carry));
	move_pc(p, c_b_quant(c_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}

void	cmd_xor(t_all *gen, t_process *p)
{
	unsigned char	coding_byte;
	unsigned char	code[2];
	int				ret[2];

	coding_byte = (gen->mem)[(p->pc + 1) % MEM_SIZE];
	code[0] = (coding_byte >> 6);
	code[1] = (coding_byte >> 4) & 0b11;
	if (((coding_byte >> 2) & 0b11) != REG_CODE || code[1] == 0 || code[0] == 0)
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = code[0];
	if ((ret[0] = get_param(p, gen->mem, p->pc + 2, 0)) == -1)
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = code[1];
	cmd_xor2(gen, p, ret, coding_byte);
}

void	cmd_zjmp(t_all *gen, t_process *p)
{
	int param;

	p->lpc = p->pc;
	if (p->carry == 0)
	{
		p->pc = p->pc + 3;
		return ;
	}
	byte_reader(&param, gen->mem, p->pc + 1, 2);
	p->pc = p->pc + (param % IDX_MOD);
}
