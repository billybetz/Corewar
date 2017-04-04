/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 22:31:54 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/22 22:13:52 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	write_to_mem2(t_arg *a, t_all *gen)
{
	int				j;
	int				k;
	int				i;
	unsigned short	inter;
	t_file			*tmp;

	i = 0;
	tmp = a->files;
	inter = MEM_SIZE / a->nb_players;
	while (i < a->nb_players)
	{
		j = 0 + i * inter;
		k = 0;
		tmp->clr = i + 1;
		while (k < tmp->chmp_size)
		{
			(gen->mem)[j] = (tmp->champ)[k];
			(gen->clr)[j] = tmp->clr;
			if (gen->curses == 1)
				put_membyte(j, gen, 0);
			j = j + 1;
			k = k + 1;
		}
		tmp = tmp->nxt;
		i = i + 1;
	}
}

void		write_to_mem(t_arg *a, t_all *gen)
{
	int				i;
	t_file			*tmp;

	i = 0;
/*	while (i < MEM_SIZE)
	{
		(gen->mem)[i] = 0;
		i = i + 1;
	}*/
	if (gen->curses == 1)
		init_display(gen);
	i = 0;
	while (i < MEM_SIZE)
	{
		(gen->mem)[i] = 0;
		(gen->clr)[i] = 0;
		if (gen->curses == 1)
			put_membyte(i, gen, 0);
		i = i + 1;
	}
//	getch();
	write_to_mem2(a, gen);
//	if (gen->curses == 1)
//		getch();
	gen->how_many_players = a->nb_players;
	gen->players_nb = (int*)malloc(sizeof(int) * gen->how_many_players);
	tmp = a->files;
	i = 0;
	while (tmp != NULL)
	{
		(gen->players_nb)[i] = tmp->n;
		i = i + 1;
		tmp = tmp->nxt;
	}
//	dump_mem(gen->mem, MEM_SIZE);
}
