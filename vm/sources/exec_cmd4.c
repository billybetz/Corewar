/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:27:58 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/23 00:06:21 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cmd_ldi2(t_all *gen, t_process *p, unsigned char code_byte, int ret[2])
{
	int		par[3];

	par[0] = p->param;
	if ((ret[1] = get_param(p, gen->mem, p->pc + 2 + ret[0], 2)) == -1)
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

void	cmd_ldi(t_all *gen, t_process *p)
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
	if ((ret[0] = get_param(p, gen->mem, p->pc + 2, 2)) == -1)
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = code[1];
	cmd_ldi2(gen, p, coding_byte, ret);
}

void	cmd_sti2(t_all *gen, t_process *p, unsigned char code_byte, int ret[3])
{
	int	a[3];

	a[0] = p->param;
	if ((ret[1] = get_param(p, gen->mem, p->pc + 2 + ret[0], 2)) == -1)
	{
		move_pc(p, c_b_quant(code_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	a[1] = p->param;
	p->code = (code_byte >> 2) & 0b11;
	if ((ret[2] = get_param(p, gen->mem, p->pc + 2 + ret[0] + ret[1], 2)) == -1)
	{
		move_pc(p, c_b_quant(code_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	a[2] = p->param;
//	printf("p%d, p%d, p%d\n", a[0], a[1], a[2]);
	gen->tmp_clr = p->clr;
	byte_writer(a[0], gen, p->pc + ((a[1] + a[2]) % MEM_SIZE), REG_SIZE);
	move_pc(p, c_b_quant(code_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}

void	cmd_sti(t_all *gen, t_process *p)
{
	unsigned char	coding_byte;
	unsigned char	code_2_3[2];
	int				ret[3];

	coding_byte = (gen->mem)[(p->pc + 1) % MEM_SIZE];
	code_2_3[0] = (coding_byte >> 4) & 0b11;
	code_2_3[1] = (coding_byte >> 2) & 0b11;
	if ((coding_byte >> 6) != REG_CODE ||
code_2_3[0] == 0 || (code_2_3[1] != DIR_CODE && code_2_3[1] != REG_CODE))
	{
//		ft_printf("erro\n");
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = REG_CODE;
	if ((ret[0] = get_param(p, gen->mem, p->pc + 2, 2)) == -1)
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	p->code = code_2_3[0];
	cmd_sti2(gen, p, coding_byte, ret);
}

void	cmd_fork(t_all *gen, t_process *p)
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
	new->pc = p->pc + (param % IDX_MOD);
	new->lpc = new->pc;
	new->inst_per = 0;
	new->carry = p->carry;
	new->lives_since_check = 0;
	new->clr = p->clr;
//	new->nw = 0/*1*/;
	new->nb = gen->nxt_nb;
	gen->nxt_nb = gen->nxt_nb + 1;

	tmp = p;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	new->prev = NULL;
	new->nxt = tmp;
	tmp->prev = new;

	while ((gen->process_list)->prev != NULL)
		gen->process_list = (gen->process_list)->prev;
	p->lpc = p->pc;
	p->pc = p->pc + 3;
}
