/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 17:42:25 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/23 00:01:10 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_process(t_process **p, int nb, t_process *previous, int prog_cnt)
{
	int i;

	*p = (t_process*)malloc(sizeof(t_process));
	if (previous == NULL)
		(*p)->clr = 1;
	else
		(*p)->clr = previous->clr + 1;
	(*p)->lpc = MEM_SIZE + prog_cnt;
	(*p)->pc = MEM_SIZE + prog_cnt;
	(*p)->inst_per = 0;
	(*p)->carry = 0;
	(*p)->lives_since_check = 0;
	(*p)->prev = previous;
	(*p)->nxt = NULL;
	i = 0;
	while (i < REG_NUMBER)
	{
		((*p)->reg)[i] = 0;
		i = i + 1;
	}
	((*p)->reg)[1] = nb;
}

void	invert_processes(t_all *gen)
{
	t_process 	*p;
	t_process 	*tmp;
	int			n;

	p = gen->process_list;
	while (p != NULL)
	{
		tmp = p->prev;
		p->prev = p->nxt;
		p->nxt = tmp;
		p = p->prev;
	}
	while ((gen->process_list)->prev != NULL)
		gen->process_list = (gen->process_list)->prev;
	p = gen->process_list;
	n = 1;
	while (p != NULL)
	{
		p->nb = n;
		n = n + 1;
		p = p->nxt;
	}
	gen->nxt_nb = n;
}

void	init_war(t_all *gen, int *inter, t_file **f, t_arg *a)
{
	gen->last_live = 0;
	gen->nb_lives_since_last = 0;
	gen->cycle = 0;
	gen->next_check = CYCLE_TO_DIE;
	gen->cycle_to_die = CYCLE_TO_DIE;
	gen->process_list = NULL;
	gen->non_dec_checks = 0;
	*inter = MEM_SIZE / a->nb_players;
	*f = a->files;
}

void	war(t_arg *a, t_all *gen)
{
	int			i;
	int			inter;
	t_file		*f;
	t_process	*tmp;

	init_war(gen, &inter, &f, a);
	i = -1;
	while (++i < a->nb_players)
	{
		if (gen->process_list == NULL)
			init_process(&(gen->process_list), f->n, NULL, 0);
		else
		{
			tmp = gen->process_list;
			while (tmp->nxt != NULL)
				tmp = tmp->nxt;
			init_process(&(tmp->nxt), f->n, tmp, 0 + i * inter);
		}
		f = f->nxt;
	}
	invert_processes(gen);
	gen->last_live = ((gen->process_list)->reg)[1];
	gen->arg = a;
	cursed_war_while(gen);
}
