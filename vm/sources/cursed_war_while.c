/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursed_war_while.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:08:11 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/23 01:08:29 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	into_the_cursed_while(t_all *gen)
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
		if (p->inst_per != 0)
		{
			p->inst_per = p->inst_per - 1;
			if (p->inst_per == 0)
				apply_commands(gen, p);
		}
		p = p->nxt;
	}
}

void	show_processes(t_all *gen, t_process *p)
{
	int p_count;
	int	vul_count;

	p_count = 0;
	vul_count = 0;
	while (p != NULL)
	{
		put_membyte(p->lpc, gen, 0);
		if (p->inst_per == 1)
			wattron((gen->crs).mem, A_BOLD);
		put_membyte(p->pc, gen, 1);
		if (p->inst_per == 1)
			wattroff((gen->crs).mem, A_BOLD);
		if (p->lives_since_check != 0)
			wattron((gen->crs).infos, A_BOLD);
		if (p_count < 57)
		{
			wattron((gen->crs).infos, COLOR_PAIR(p->clr));
			mvwprintw((gen->crs).infos, p_count + 8, 2, "                                    ");
			mvwprintw((gen->crs).infos, p_count + 8, 2, "%3dP(%3u)(%d) line %2d,  col %2d", p->nb, p->inst_per, p->carry, (p->pc % MEM_SIZE) / 64, (p->pc % MEM_SIZE) % 64);
			wattroff((gen->crs).infos, COLOR_PAIR(p->clr));
		}
		if (p->lives_since_check == 0)
			vul_count = vul_count + 1;
		else
			wattroff((gen->crs).infos, A_BOLD);
		p_count = p_count + 1;
		p = p->nxt;
	}
	wattron((gen->crs).infos, A_BOLD);
	mvwprintw((gen->crs).infos, 1, 24, "%d", gen->cycle);
	wattroff((gen->crs).infos, A_BOLD);
	mvwprintw((gen->crs).infos, 2, 24, "%u", gen->next_check);
	mvwprintw((gen->crs).infos, 3, 24, "       ");
	mvwprintw((gen->crs).infos, 3, 24, "%d        ", p_count);
	mvwprintw((gen->crs).infos, 4, 24, "       ");
	mvwprintw((gen->crs).infos, 4, 24, "%d        ", vul_count);
	mvwprintw((gen->crs).infos, 5, 24, "%d        ", gen->cycle_to_die);
	while (p_count < 57)
	{
		mvwprintw((gen->crs).infos, p_count + 8, 2, "                                    ");
		p_count = p_count + 1;
	}
	wrefresh((gen->crs).infos);
}


void	wait_for_key(char key)
{
	int ext;
	char c;

	ext = 0;
	while (ext == 0)
	{
		c = getch();
		if (c == key)
			ext = 1;
		else if (c == 'q')
		{
			endwin();
			exit(0);
		}
	}
}

void	cursed_war_while(t_all *gen)
{
	int		ext;
	char	c;
	unsigned int		step;

	if (gen->curses == 1)
		wait_for_key('s');
	players(gen);
	step = 0;
	while (gen->process_list != NULL)
	{
		if (gen->curses == 1)
			show_processes(gen, gen->process_list);
		if (gen->cycle == gen->next_check)
		{
			to_kill_or_not_to_kill(gen, &(gen->process_list));
			if ((gen->nb_lives_since_last > NBR_LIVE) || (gen->non_dec_checks >= MAX_CHECKS))
			{
				gen->non_dec_checks = 0;
				if (CYCLE_DELTA < gen->cycle_to_die)
					gen->cycle_to_die = gen->cycle_to_die - CYCLE_DELTA;
				else
					gen->cycle_to_die = 1;
			}
			else
				gen->non_dec_checks = gen->non_dec_checks + 1;
			gen->nb_lives_since_last = 0;
			gen->next_check = gen->cycle + gen->cycle_to_die;
		}
		into_the_cursed_while(gen);
		if (gen->curses == 1)
			refresh();
		ext = 0;
		while ((gen->curses == 1) && (step < gen->cycle) && (ext == 0))
		{
			c = getch();
			if (c == 'p')
			{
				step = gen->cycle + 99;
				ext = 1;
			}
			else if (c == 's')
				ext = 1;
			else if (c == 'q')
			{
				endwin();
				exit(0);
			}
			else if (c == 'w')
				put_proc_nb(gen, gen->process_list);
		}
		if (gen->cycle == (unsigned int)(gen->arg)->dump)
		{
			dump_mem(gen->mem, MEM_SIZE);
			exit(1);
		}
		gen->cycle = gen->cycle + 1;
	}
	find_winner(gen);
	if (gen->curses == 1)
	{
		wait_for_key('q');
		endwin();
	}
}
