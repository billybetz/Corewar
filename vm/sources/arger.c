/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arger.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:26:05 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/22 15:59:34 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_s_atoi(char *str, int *result)
{
	int	i;
	int	sig;

	i = 0;
	*result = 0;
	sig = 1;
	if (str[i] == '-')
	{
		i = i + 1;
		sig = -1;
	}
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		*result = (*result * 10) + str[i] - 48;
		i = i + 1;
	}
	if ((i == 0) || ((i == 1) && (str[0] == '-')))
		return (-1);
	*result = (*result) * sig;
	return (0);
}

void	start_tf(t_file **f)
{
	int i;

	*f = (t_file*)malloc(sizeof(t_file));
	(*f)->name_of_file = NULL;
	(*f)->fd = -1;
	(*f)->n = -1;
	i = 0;
	while ((i < PROG_NAME_LENGTH + 1) && ((i = i + 1)))
		((*f)->prog_name)[i - 1] = 0;
	i = 0;
	while ((i < COMMENT_LENGTH + 1) && ((i = i + 1)))
		((*f)->comment)[i - 1] = 0;
	i = 0;
	while ((i < CHAMP_MAX_SIZE) && ((i = i + 1)))
		((*f)->champ)[i] = 0;
	(*f)->nxt = NULL;
}

int		arger(int nb_args, char **arg, t_arg *a, t_all *gen)
{
	if (arg_parser(nb_args, arg, a, gen) == -1)
		return (-1);
	return (0);
}
