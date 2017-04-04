/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars_strs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:24:18 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/07 15:04:01 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

int				comment_or_end(char c)
{
	if ((c == COMMENT_CHAR) || (c == ';') || (c == '\0'))
		return (1);
	return (0);
}

int				is_labelchars(char c)
{
	if ((c >= 'a') && (c <= 'z'))
		return (1);
	else if ((c >= '0') && (c <= '9'))
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

void			trimard(char *line)
{
	int			i;
	int			j;
	int			k;

	k = 0;
	i = 0;
	while (ft_isspace(line[i]) == 1)
		i = i + 1;
	j = ft_strlen(line) - 1;
	while (j >= 0 && (ft_isspace(line[j]) == 1))
		j--;
	if (j < 0)
	{
		line[0] = '\0';
		return ;
	}
	while (i <= j)
	{
		line[k] = line[i];
		k++;
		i++;
	}
	line[k] = '\0';
}
