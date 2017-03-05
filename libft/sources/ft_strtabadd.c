/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabadd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:01:16 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/01 18:06:28 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtabadd(char ***tab, char *str)
{
	char	**tab2;
	int		i;

	i = -1;
	if (!str)
		return ;
	if (!*tab || !((*tab)[0]))
	{
		*tab = malloc(sizeof(char *) * 2);
		(*tab)[0] = ft_strdup(str);
		(*tab)[1] = NULL;
		return ;
	}
	tab2 = malloc(sizeof(char *) * (ft_get_size_tab((void**)*tab) + 2));
	while ((*tab)[++i])
		tab2[i] = ft_strdup((*tab)[i]);
	tab2[i++] = ft_strdup(str);
	tab2[i] = NULL;
	ft_free_double_pointer((void ***)tab);
	*tab = tab2;
}
