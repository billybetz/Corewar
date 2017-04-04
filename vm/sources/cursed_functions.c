/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursed_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:10:46 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/23 00:51:54 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

WINDOW	*create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *out;

	out = newwin(height, width, starty, startx);
	box(out, 0, 0);
	wrefresh(out);
	return (out);
}

void	start_clrs(void)
{
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
}

void	init_display(t_all *gen)
{
	initscr();
	cbreak();
	noecho();
	start_clrs();
	attron(A_BOLD | COLOR_PAIR(6));
	mvprintw(1, (COLS - ft_strlen("THE FAMOUS COREWAR")) / 2,  "THE FAMOUS COREWAR");
	attroff(A_BOLD | COLOR_PAIR(6));
	refresh();
	(gen->crs).mem = create_newwin(66, 64 * 3 + 4, 2, 1);
	wrefresh((gen->crs).mem);
	(gen->crs).infos = create_newwin(66, 40, 2, 64 * 3 + 5);
	wattron((gen->crs).infos, A_BOLD);
	mvwprintw((gen->crs).infos, 1, 2, "Cycle: ");
	mvwprintw((gen->crs).infos, 2, 2, "Next check: ");
	mvwprintw((gen->crs).infos, 3, 2, "Processes alive: ");
	mvwprintw((gen->crs).infos, 4, 2, "Vulnerable processes: ");
	mvwprintw((gen->crs).infos, 5, 2, "Cycle to die: ");
	mvwprintw((gen->crs).infos, 6, 2, "Cycle delta: ");
	wattroff((gen->crs).infos, A_BOLD);
	mvwprintw((gen->crs).infos, 6, 24, "%d", CYCLE_DELTA);
	mvwprintw((gen->crs).infos, 10, 2, "Press 's' to start.");
	mvwprintw((gen->crs).infos, 11, 2, "Then:");
	mvwprintw((gen->crs).infos, 12, 4, "Press 's' to move one cycle.");
	mvwprintw((gen->crs).infos, 13, 4, "Press 'p' to move 100 cycles.");
	mvwprintw((gen->crs).infos, 14, 2, "Press 'q' at any time to quit.");
	wrefresh((gen->crs).infos);
	move(COLS + 1, LINES + 1);
}

void	put_proc_nb(t_all *gen, t_process *p)
{
	while (p->prev != NULL)
		p = p->prev;
	while (p != NULL)
	{
		wattron((gen->crs).mem, COLOR_PAIR(p->clr));
		wattron((gen->crs).mem, A_REVERSE);
		mvwprintw((gen->crs).mem, 1 + (p->pc % MEM_SIZE) / 64, 2 + ((p->pc % MEM_SIZE) % 64) * 3, "%2d", p->nb);
		wattroff((gen->crs).mem, COLOR_PAIR(p->clr));
		wattroff((gen->crs).mem, A_REVERSE);
		p = p->nxt;
	}
	wrefresh((gen->crs).mem);
}


void	put_membyte(int pc, t_all *gen, int reverse)
{
	pc = pc % MEM_SIZE;
	if (reverse == 1)
		wattron((gen->crs).mem, A_REVERSE);
	wattron((gen->crs).mem, COLOR_PAIR((gen->clr)[pc % MEM_SIZE]));
	mvwprintw((gen->crs).mem, 1 + (pc % MEM_SIZE) / 64, 2 + ((pc % MEM_SIZE) % 64) * 3, "%02x", (gen->mem)[pc % MEM_SIZE]);
	wattroff((gen->crs).mem, COLOR_PAIR((gen->clr)[pc % MEM_SIZE]));
	if (reverse == 1)
		wattroff((gen->crs).mem, A_REVERSE);
	wrefresh((gen->crs).mem);
}

