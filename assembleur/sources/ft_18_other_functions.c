/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_10.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalmyko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:12:32 by akalmyko          #+#    #+#             */
/*   Updated: 2017/03/17 13:12:33 by akalmyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

int					check_legality(
					t_op tab, unsigned char t_type, int nb_param, int *infos)
{
	if (nb_param == 0)
	{
		if ((t_type & (tab.param).p1) == 0)
			return (parse_error(infos, "err: Wrong parameter 1\n"));
	}
	else if (nb_param == 1)
	{
		if ((t_type & (tab.param).p2) == 0)
			return (parse_error(infos, "err: Wrong parameter 2\n"));
	}
	else if (nb_param == 2)
	{
		if ((t_type & (tab.param).p3) == 0)
		{
			ft_printf("\nt_tyoe %hhu\n\n", t_type);
			return (parse_error(infos, "err: Wrong parameter 3\n"));
		}
	}
	else if (nb_param >= 3)
		return (parse_error(infos, "err: Too many arguments\n"));
	return (1);
}

int					ft_specialatoi(char *str, int *result)
{
	int				i;
	int				j;
	int				sign;

	i = 0;
	*result = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '+') || (str[i] == '-'))
		i = i + 1;
	j = i;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		*result = (*result * 10) + str[i] - 48;
		i = i + 1;
	}
	*result = *result * sign;
	if (((str[i] == SEPARATOR_CHAR) || (str[i] == '\0')) && (i != j))
		return (i + 1);
	else
		return (-1);
}

int					param_computations(t_params *p, int *infos, t_op tab)
{
	int				i;
	unsigned char	c_b;
	unsigned char	type_tmp;

	if (p->count != tab.nb_param)
		return (parse_error(infos, "err: Not enough arguments\n"));
	c_b = 0;
	i = 0;
	while (i < p->count)
	{
		type_tmp = (unsigned char)(p->type)[i] << (6 - i * 2);
		c_b = c_b + type_tmp;
		i = i + 1;
	}
	p->coding_byte = c_b;
	return (2);
}

void				ft_free(void *pointer)
{
	free(pointer);
	pointer = NULL;
}
