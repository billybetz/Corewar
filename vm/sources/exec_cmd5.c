/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:28:44 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/23 00:07:34 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cmd_lfork(t_all *gen, t_process *p)
{
	int			param;
	t_process	*new;
	t_process	*tmp;
	int			i;

	byte_reader(&param, gen->mem, p->pc + 1, 2);
	new = (t_process*)malloc(sizeof(t_process));
	i = 0;
	while (i <= REG_NUMBER)
	{
		(new->reg)[i] = (p->reg)[i];
		i = i + 1;
	}
	new->pc = p->pc + param;
	new->lpc = new->pc;
	new->inst_per = 0;
	new->carry = p->carry;
	new->lives_since_check = 0;
	new->clr = p->clr;
	new->prev = p;
	new->nxt = p->nxt;
//	new->nw = 1;
	new->nb = gen->nxt_nb;
	gen->nxt_nb = gen->nxt_nb + 1;

	tmp = p;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	new->prev = NULL;
	new->nxt = tmp;
	tmp->prev = new;

/*	if (p->nxt != NULL)
		(p->nxt)->prev = new;
	p->nxt = new;*/
	p->lpc = p->pc;
	p->pc = p->pc + 3;
}

void	ind_code_cmd_lld(t_all *gen, t_process *p, int *par)
{
	byte_reader(&par[0], gen->mem, p->pc + 2, 2);
	byte_reader(&par[0], gen->mem, p->pc + par[0], REG_SIZE);
	byte_reader(&par[1], gen->mem, p->pc + 4, 1);
	if ((par[1] >= 1) && (par[1] <= REG_NUMBER))
	{
		change_carry(par[0], &(p->carry));
		(p->reg)[par[1]] = par[0];
	}
}

void	cmd_lld(t_all *gen, t_process *p)
{
	int				par[2];
	unsigned char	coding_byte;
	unsigned char	first_code;

	coding_byte = (gen->mem)[(p->pc + 1) % MEM_SIZE];
	first_code = coding_byte >> 6;
	if (((first_code != DIR_CODE) && (first_code != IND_CODE)) ||
(((coding_byte >> 4) & 0b11) != REG_CODE) || ((coding_byte & 0b00001111) != 0))
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	if (first_code == DIR_CODE)
	{
		byte_reader(&par[0], gen->mem, p->pc + 2, 4);
		byte_reader(&par[1], gen->mem, p->pc + 6, 1);
		if ((par[1] >= 1) && (par[1] <= REG_NUMBER))
		{
			change_carry(par[0], &(p->carry));
			(p->reg)[par[1]] = par[0];
		}
	}
	else if (first_code == IND_CODE)
		ind_code_cmd_lld(gen, p, par);
	move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}

void	cmd_lldi2(t_all *gen, t_process *p, unsigned char code_byte, int ret[2])
{
	int		par[3];

	par[0] = p->param;
	if ((ret[1] = get_param(p, gen->mem, p->pc + 2 + ret[0], 3)) == -1)
	{
		move_pc(p, c_b_quant(code_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	par[1] = p->param;
	byte_reader(&par[2], gen->mem, p->pc + 2 + ret[0] + ret[1], 1);
	if (par[2] < 1 || par[2] > 16)
	{
		move_pc(p, c_b_quant(code_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	(p->reg)[par[2]] = par[0] + par[1];
	change_carry((p->reg)[par[2]], &(p->carry));
	move_pc(p, c_b_quant(code_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}

void	cmd_lldi(t_all *gen, t_process *p)
{
	unsigned char	coding_byte;
	unsigned char	code[2];
	int				ret[2];

	coding_byte = (gen->mem)[(p->pc + 1) % MEM_SIZE];
	code[0] = (coding_byte >> 6);
	code[1] = (coding_byte >> 4) & 0b11;
	if ((((coding_byte >> 2) & 0b11) != REG_CODE) ||
(code[0] == 0) || ((code[1] != DIR_CODE) && (code[1] != REG_CODE)))
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = code[0];
	if ((ret[0] = get_param(p, gen->mem, p->pc + 2, 3)) == -1)
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = code[1];
	cmd_lldi2(gen, p, coding_byte, ret);
}
