/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_15_handle_params_02.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalmyko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:23:47 by akalmyko          #+#    #+#             */
/*   Updated: 2017/03/18 16:23:49 by akalmyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

int		**ft_init_tab(int opcode, int **tab_free, int len, int option)
{
	int			**tab;

	if (option == FREE_ALL)
	{
		free(tab_free[0]);
		free(tab_free[1]);
		free(tab_free[2]);
		free(tab_free[3]);
		free(tab_free);
		return (NULL);
	}
	tab = (int**)malloc(sizeof(int*) * 4);
	tab[I_T] = (int*)malloc(sizeof(int) * 1);
	tab[J_T] = (int*)malloc(sizeof(int) * 1);
	tab[OPCODE] = (int*)malloc(sizeof(int) * 1);
	tab[LEN_T] = (int*)malloc(sizeof(int) * 1);
	*tab[I_T] = 0;
	*tab[J_T] = 0;
	*tab[OPCODE] = opcode;
	*tab[LEN_T] = len;
	return (tab);
}
