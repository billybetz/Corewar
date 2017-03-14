/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:05:21 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/13 00:19:10 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_corewar(int nb_args, char **args)
{
	t_arg a;

	if (arger(nb_args, args, &a) == -1)
		return (-1);
/*	if (verify_files(g) == -1)
		return (-1);
	write_to_mem();*/
	return (0);
}
