/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 20:23:40 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/22 16:02:23 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		arg_parser4(t_arg *a, int i_n[2], t_file *tmp)
{
	if (((tmp->fd = open(tmp->name_of_file, O_RDONLY))) == -1)
	{
		ft_putendl(tmp->name_of_file);
		return (print_error("One of the players does not exist.\n"));
	}
	a->nb_players = a->nb_players + 1;
	i_n[0] = i_n[0] + 1;
	return (0);
}

int		arg_parser3(char **args, t_arg *a, int i_n[2], t_file *tmp)
{
	if (i_n[1] == 1)
		return (print_error("Either all files have '-n', or none do.\n"));
	tmp->name_of_file = args[i_n[0]];
	tmp->n = a->nb_players + 1;
	return (0);
}

void	arg_parser2(t_file **tmp, t_arg *a)
{
	if (a->files == NULL)
	{
		start_tf(&(a->files));
		(*tmp) = a->files;
		(*tmp)->count = 0;
	}
	else
	{
		(*tmp) = a->files;
		while ((*tmp)->nxt != NULL)
			(*tmp) = (*tmp)->nxt;
		start_tf(&((*tmp)->nxt));
		((*tmp)->nxt)->count = (*tmp)->count + 1;
		(*tmp) = (*tmp)->nxt;
	}
}

int		init_arg_parser(int nb_args, char **args, t_all *gen, int i_n[2])
{
	i_n[0] = 0;
	gen->curses = 0;
	if (ft_strcmp(args[i_n[0]], "-curses") == 0)
	{
		gen->curses = 1;
		i_n[0] = i_n[0] + 1;
	}
	if (ft_strcmp(args[i_n[0]], "-dump") == 0)
	{
		if ((i_n[0] + 1 >= nb_args) ||
		(ft_s_atoi(args[i_n[0] + 1], &((gen->arg)->dump)) == -1))
			return (print_error("Missing <number of cycles> after -dump.\n"));
		i_n[0] = i_n[0] + 2;
	}
	else
		(gen->arg)->dump = -1;
	(gen->arg)->nb_players = 0;
	(gen->arg)->files = NULL;
	i_n[1] = 0;
	return (0);
}

int		arg_parser(int nb_args, char **args, t_arg *a, t_all *gen)
{
	int		i_n[2];
	t_file	*tmp;

	if (init_arg_parser(nb_args, args, gen, i_n) == -1)
		return (-1);
	while (i_n[0] < nb_args)
	{
		arg_parser2(&tmp, a);
		if (ft_strcmp(args[i_n[0]], "-n") == 0)
		{
			if ((a->nb_players != 0) && (i_n[1] == 0))
				return (print_error("Either '-n' for all or no one.\n"));
			if ((i_n[0] + 2 >= nb_args) ||
			(ft_s_atoi(args[i_n[0] + 1], &(tmp->n)) == -1))
				return (print_error("Wrong params after '-n'\n"));
			i_n[0] = i_n[0] + 2;
			tmp->name_of_file = args[i_n[0]];
			i_n[1] = 1;
		}
		else if (arg_parser3(args, a, i_n, tmp) == -1)
			return (-1);
		if (arg_parser4(a, i_n, tmp) == -1)
			return (-1);
	}
	return (arg_parser5(a, i_n, tmp));
}
