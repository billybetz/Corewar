/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:05:21 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/22 15:51:29 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_corewar(int nb_args, char **args)
{
	t_arg a;
	t_all gen;

	gen.arg = &a;
	if (arger(nb_args, args, &a, &gen) == -1)
		return (-1);
	if (verify_files(&a) == -1)
		return (-1);
	write_to_mem(&a, &gen);
	war(&a, &gen);
	return (0);
}
