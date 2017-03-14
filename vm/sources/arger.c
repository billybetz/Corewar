/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arger.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:26:05 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/12 23:03:44 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_s_atoi(char *str, int *result)
{
	int i;

	i = 0;
	*result = 0;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		*result = (*result * 10) + str[i] - 48;
		i = i + 1;
	}
	if (i == 0)
		return (-1);
	return (0);
}

void	start_tf(t_file **f)
{
	*f = (t_file*)malloc(sizeof(t_file));
	(*f)->name_of_file = NULL;
	(*f)->fd = -1;
	(*f)->n = -1;
	(*f)->nxt = NULL;
}

int		arg_parser(int nb_args, char **args, t_arg *a)
{
	int		i;
	t_file	*tmp;

	i = 0;
	if (ft_strcmp(args[i], "-dump") == 0)
	{
		if ((i + 1 >= nb_args) || (ft_s_atoi(args[i + 1], &(a->dump)) == -1))
			return (print_error(
						"Missing <number of clycles> after -dump.\n"));
		i = 2;
	}
	else
		a->dump = -1;
	a->nb_players = 0;
	a->files = NULL;
	while (i < nb_args)
	{
		if (a->files == NULL)
		{
			start_tf(&(a->files));
			tmp = a->files;
		}
		else
		{
			tmp = a->files;
			while (tmp->nxt != NULL)
				tmp = tmp->nxt;
			start_tf(&(tmp->nxt));
			tmp = tmp->nxt;
		}
		if (ft_strcmp(args[i], "-n") == 0)
		{
			if ((i + 2 >= nb_args) || (ft_s_atoi(args[i + 1], &(tmp->n)) == -1))
				return (print_error("Wrong params after '-n'\n"));
			i = i + 2;
		}
//		if (tmp->n == -1)
//			tmp->n = a->nb_players + 1;
		tmp->name_of_file = args[i];
		if (((tmp->fd = open(tmp->name_of_file, O_RDONLY))) == -1)
			return (print_error("One of the players does not exist.\n"));
		a->nb_players = a->nb_players + 1;
		i = i + 1;
	}
	if (a->nb_players < 2)
		return (print_error("Not enough players.\n"));
	if (a->nb_players > 6)
		return (print_error("Too many players.\n"));
	ft_putnbr(a->nb_players);
	ft_putstr("\n");
	tmp = a->files;
	while (tmp != NULL)
	{
		ft_putnbr(tmp->fd);
		ft_putendl(tmp->name_of_file);
		tmp = tmp->nxt;
	}
	return (0);
}

int		arger(int nb_args, char **arg, t_arg *a)
{
	if (arg_parser(nb_args, arg, a) == -1)
		return (-1);
	return (0);
}
