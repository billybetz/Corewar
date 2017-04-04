/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_winner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:37:12 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/22 22:15:05 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		players(t_all *gen)
{
	t_file *f;

	if (gen->curses == 1)
		return ;
	f = (gen->arg)->files;
//	while (f->prev != NULL)
//		f = f->prev;
	while (f != NULL)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")!\n",
				f->n, f->chmp_size, f->prog_name, f->comment);
		f = f->nxt;
	}
}

void		find_winner(t_all *gen)
{
	char *winner;

	winner = get_player_name(gen, gen->last_live);

	if (gen->curses == 0)
		ft_printf("Contestant %d, \"%s\", has won!\n",
				gen->last_live, winner);
	else
	{
		mvwprintw((gen->crs).mem, 1, 2,
				"Contestant %d, \"%s\", has won! ", gen->last_live, winner);
		mvwprintw((gen->crs).mem, 1, 2, "Press 'q' to quit ");
		wrefresh((gen->crs).mem);
		while (getch() != 'q')
		{}
	}
}
