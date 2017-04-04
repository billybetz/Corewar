/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:39:15 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/23 00:02:22 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cmd_live(t_all *gen, t_process *p)
{
	int		player;

//	ft_printf("live");
//	gen->nb_lives_since_last++;
	byte_reader(&player, gen->mem, p->pc + 1, 4);
	if (check_player_nb(player, gen) == 1)
	{
		gen->last_live = player;
		if (gen->curses == 0)
			ft_printf("un processus dit que le joueur %d (%s) est en vie.\n",
		player, get_player_name(gen, player));
	}
	gen->nb_lives_since_last = gen->nb_lives_since_last + 1;
	p->lives_since_check = p->lives_since_check + 1;
	move_pc(p, 5);
}

void	ind_code_cmd_ld(t_all *gen, t_process *p, int *par)
{
	byte_reader(&(par[0]), gen->mem, p->pc + 2, 2);
	byte_reader(&(par[0]), gen->mem, p->pc + (par[0] % IDX_MOD), REG_SIZE);
	byte_reader(&(par[1]), gen->mem, p->pc + 4, 1);
	if ((par[1] >= 1) && (par[1] <= REG_NUMBER))
	{
		change_carry(par[0], &(p->carry));
		(p->reg)[par[1]] = par[0];
	}
}

void	cmd_ld(t_all *gen, t_process *p)
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
		byte_reader(&(par[0]), gen->mem, p->pc + 2, 4);
		byte_reader(&(par[1]), gen->mem, p->pc + 6, 1);
		if ((par[1] >= 1) && (par[1] <= REG_NUMBER))
		{
			change_carry(par[0], &(p->carry));
			(p->reg)[par[1]] = par[0];
		}
	}
	else if (first_code == IND_CODE)
		ind_code_cmd_ld(gen, p, par);
	move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}

void	code2_cmd_st(int par[2], t_all *g, t_process *p, unsigned char s_code)
{
//	int ret;

	if (s_code == IND_CODE)
	{
		par[1] = get_ind_address(g->mem, p->pc + 3);
//		byte_reader(&(par[1]), g->mem, p->pc + 3, 2);
		g->tmp_clr = p->clr;
		byte_writer((p->reg)[par[0]], g, p->pc +
			(par[1] % IDX_MOD), REG_SIZE);
	}
	else if (s_code == REG_CODE)
	{
//		ft_printf("reg_code\n");
		par[1] = (g->mem)[(p->pc + 3) % MEM_SIZE];
		if (par[1] >= 1 && par[1] <= 16)
			(p->reg)[par[1]] = (p->reg)[par[0]];
//		ft_printf("reg[%d] = %d\n", par[1], (p->reg)[par[1]]);
	}
}

void	cmd_st(t_all *gen, t_process *p)
{
	int				par[2];
	unsigned char	coding_byte;
	unsigned char	second_code;

	coding_byte = (gen->mem)[(p->pc + 1) % MEM_SIZE];
	second_code = (coding_byte >> 4) & 0b11;
	if (((coding_byte >> 6) != REG_CODE) || ((second_code != IND_CODE) &&
(second_code != REG_CODE)) || ((coding_byte & 0b1111) != 0))
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	par[0] = (gen->mem)[(p->pc + 2) % MEM_SIZE];
	if ((par[0] < 1) || (par[0] > 16))
	{
		move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
		return ;
	}
	code2_cmd_st(par, gen, p, second_code);
	move_pc(p, c_b_quant(coding_byte, g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1]) + 2);
}
