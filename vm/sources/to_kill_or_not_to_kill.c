/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_kill_or_not_to_kill.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:41:47 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/21 18:43:09 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_free_p(t_all *gen, t_process **p)
{
	if (gen->curses == 1)
	{
		put_membyte((*p)->lpc, gen, 0);
		put_membyte((*p)->pc, gen, 0);
	}
	free(*p);
	*p = NULL;
}

void	to_kill_or_not_to_kill(t_all *gen, t_process **p)
{
	int			exit;
	t_process	*tmp;

	exit = 0;
	while (exit == 0)
	{
		if ((*p)->lives_since_check == 0)
		{
//			ft_printf("oalaaaaaaaaaaaaaaaaaaaaaaaowksoooookkkwkwokoko\n|||||||||||||||");
			if (((*p)->nxt == NULL) && ((*p)->prev == NULL))
			{
//				ft_printf("aaaaaaaaaaaaaaaaaaaaaaaa");
				exit = 1;
				ft_free_p(gen, p);
			}
			else if ((*p)->nxt == NULL)
			{
//				ft_printf("bbbbbbbbbbbbbbbbbbbbbbbbbb");
				*p = (*p)->prev;
				ft_free_p(gen, &((*p)->nxt));
				(*p)->nxt = NULL;
				exit = 1;
			}
			else if ((*p)->prev == NULL)
			{
//				ft_printf("ccccccccccccccccccccccccccc");
				*p = (*p)->nxt;
				ft_free_p(gen, &((*p)->prev));
				(*p)->prev = NULL;
			}
			else
			{
//				ft_printf("dddddddddddddddddddddddddd");
				tmp = *p;
				*p = (*p)->nxt;
				(*p)->prev = tmp->prev;
				((*p)->prev)->nxt = *p;
				ft_free_p(gen, &tmp);
			}
		}
		else
		{
			(*p)->lives_since_check = 0;
			if ((*p)->nxt == NULL)
				exit = 1;
			else
				*p = (*p)->nxt;
		}
	}
	while ((*p != NULL) && ((*p)->prev != NULL))
		*p = (*p)->prev;
}
