/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 20:28:47 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/21 20:28:47 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		arg_parser5(t_arg *a, int i_n[2], t_file *tmp)
{
	t_file	*t2;

	if (i_n[1] == 1)
	{
		tmp = a->files;
		while (tmp != NULL)
		{
			t2 = tmp->nxt;
			while (t2 != NULL)
			{
				if (t2->n == tmp->n)
					return (print_error("Two players with the same number.\n"));
				t2 = t2->nxt;
			}
			tmp = tmp->nxt;
		}
	}
	if (a->nb_players < 1)
		return (print_error("Not enough players.\n"));
	if (a->nb_players > MEM_SIZE / CHAMP_MAX_SIZE)
		return (print_error("Too many players.\n"));
	tmp = a->files;
	// while (tmp != NULL)
	// {
	// 	ft_putnbr(tmp->n);
	// 	ft_putendl(tmp->name_of_file);
	// 	tmp = tmp->nxt;
	// }
	return (0);
}
