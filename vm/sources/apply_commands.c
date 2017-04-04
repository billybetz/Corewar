/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 00:28:14 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/19 21:03:37 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR, 0, 0}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR, 0, 0}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR, 0, 0}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG, 0, 0}, 16, 2, "aff", 1, 0},
	{0, 0, {0, 0, 0}, 0, 0, 0, 0, 0}
};

void	apply_commands2(t_all *gen, t_process *p)
{
	if ((gen->mem)[p->pc % MEM_SIZE] == 11)
		cmd_sti(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 12)
		cmd_fork(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 13)
		cmd_lld(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 14)
		cmd_lldi(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 15)
		cmd_lfork(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 16)
		cmd_aff(gen, p);
}

void	apply_commands(t_all *gen, t_process *p)
{
	if ((gen->mem)[p->pc % MEM_SIZE] == 1)
		cmd_live(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 2)
		cmd_ld(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 3)
		cmd_st(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 4)
		cmd_add(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 5)
		cmd_sub(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 6)
		cmd_and(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 7)
		cmd_or(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 8)
		cmd_xor(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 9)
		cmd_zjmp(gen, p);
	else if ((gen->mem)[p->pc % MEM_SIZE] == 10)
		cmd_ldi(gen, p);
	else
		apply_commands2(gen, p);
}
