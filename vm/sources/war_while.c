/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war_while.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 00:55:31 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/21 23:41:43 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_command(t_all *gen, t_process *p)
{
	t_op o;

	if (((gen->mem)[p->pc % MEM_SIZE] >= 1) &&
		((gen->mem)[p->pc % MEM_SIZE] <= 16))
	{
		o = g_op_tab[(gen->mem)[p->pc % MEM_SIZE] - 1];
		p->inst_per = o.inst_cycles;
		return (1);
	}
	return (0);
}

void	into_the_while(t_all *gen)
{
	t_process *p;

	p = gen->process_list;
	while (p != NULL)
	{
		if (p->inst_per == 0)
		{
			if (is_command(gen, p) == 0)
			{
				p->lpc = p->pc;
				p->pc = p->pc + 1;
			}
		}
		else if (p->inst_per != 0)
		{
			p->inst_per = p->inst_per - 1;
			if (p->inst_per == 0)
				apply_commands(gen, p);
		}
		p = p->nxt;
	}
}

void	war_while(t_all *gen)
{
	while (gen->process_list != NULL)
	{
		if (gen->cycle == gen->next_check)
		{
			to_kill_or_not_to_kill(gen, &(gen->process_list));
			if ((gen->nb_lives_since_last > NBR_LIVE) || (gen->non_dec_checks >= MAX_CHECKS))
			{
				gen->non_dec_checks = 0;
				if (CYCLE_DELTA < gen->cycle_to_die)
					gen->cycle_to_die -= CYCLE_DELTA;
				else
					gen->cycle_to_die = 1;
			}
			else
				gen->non_dec_checks = gen->non_dec_checks + 1;
			gen->nb_lives_since_last = 0;
			gen->next_check = gen->cycle + gen->cycle_to_die;
		}
		into_the_while(gen);
		ft_printf("%d\n", gen->cycle);
		if (gen->cycle % 100 == 0)
			dump_mem(gen->mem, MEM_SIZE);
		if (gen->cycle == (unsigned int)(gen->arg)->dump)
		{
			dump_mem(gen->mem, MEM_SIZE);
			exit(1);
		}
		gen->cycle = gen->cycle + 1;
	}
	find_winner(gen);
}
