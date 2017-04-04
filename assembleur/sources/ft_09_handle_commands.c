/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:16:26 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/21 15:51:43 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

static void		ft_convert_to(t_commands *cmd, int *infos)
{
	t_commands		*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->number_of_bytes > 0)
		{
			converter(tmp, infos);
			if ((*infos & PARSE_ERROR) != 0)
			{
				ft_putstr("err: in converter\n");
				return ;
			}
		}
		tmp = tmp->nxt;
	}
}

int				handle_commands2(int *i, t_commands *tmp)
{
	int			j;
	t_commands	*new;

	if (((tmp->line)[*i] == LABEL_CHAR) && ((*i = *i + 1)))
	{
		rec_label(tmp, *i);
		while (ft_isspace((tmp->line)[*i]) == 1)
			*i = *i + 1;
		j = *i;
		if ((tmp->line)[*i] != '\0')
		{
			create_cmd(&new, tmp, tmp->line_nb);
			new->line = ft_strdup(&((tmp->line)[*i]));
			new->nxt = tmp->nxt;
			tmp->nxt = new;
			if (new->nxt)
				(new->nxt)->prev = new;
			(tmp->line)[*i] = '\0';
		}
	}
	else
		j = 0;
	return (j);
}

void			handle_commands(t_commands *cmd, int *infos)
{
	int				i;
	int				j;
	t_commands		*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp && tmp->line && (is_labelchars((tmp->line)[i])) == 1)
			i = i + 1;
		j = handle_commands2(&i, tmp);
		handle_instructions(&((tmp->line)[j]), infos, tmp);
		if (*infos & PARSE_ERROR)
			return ;
		tmp = tmp->nxt;
	}
	ft_convert_to(cmd, *&infos);
}
