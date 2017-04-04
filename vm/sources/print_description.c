/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_description.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:34:44 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/10 21:52:47 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_description(void)
{
	ft_putstr("> ./corewar [[-n <number of player>] player.cor]");
	ft_putstr(" [[-n <number of player>]player.cor]\n");
	return (0);
}
