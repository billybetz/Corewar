/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_17_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalmyko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:43:08 by akalmyko          #+#    #+#             */
/*   Updated: 2017/03/18 18:43:09 by akalmyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

void			rec_label(t_commands *cmd, int i)
{
	int			j;
	t_commands	*tmp;

	cmd->label = (char*)malloc(sizeof(char) * (i + 1));
	j = 0;
	while ((cmd->line)[j] != LABEL_CHAR)
	{
		(cmd->label)[j] = (cmd->line)[j];
		j = j + 1;
	}
	(cmd->label)[j] = '\0';
	tmp = cmd->prev;
	while (tmp != NULL)
	{
		if ((tmp->label != NULL) && (ft_strcmp(tmp->label, cmd->label) == 0))
		{
			free(cmd->label);
			cmd->label = NULL;
			return ;
		}
		tmp = tmp->prev;
	}
}

int				param_label(t_commands *cmd, char *str)
{
	int			i;

	i = 1;
	while (is_labelchars(str[i]) == 1)
		i = i + 1;
	if (i == 1)
		return (-1);
	((cmd->p).lbels)[(cmd->p).count] = (char*)malloc(sizeof(char) * i);
	((cmd->p).lbels)[(cmd->p).count][i - 1] = '\0';
	i = 1;
	while (is_labelchars(str[i]) == 1)
	{
		((cmd->p).lbels)[(cmd->p).count][i - 1] = str[i];
		i = i + 1;
	}
	return (i + 1);
}

static void		move_forward(t_commands *tmp, int *found, int *out, char *str)
{
	while ((tmp != NULL) && (*found == 0))
	{
		*out = *out + tmp->number_of_bytes;
		if ((tmp->label != NULL) && (ft_strcmp(tmp->label, str) == 0))
			*found = 1;
		tmp = tmp->prev;
	}
}

static void		move_back(t_commands *tmp, int *found, int *out, char *str)
{
	while ((tmp != NULL) && (*found == 0))
	{
		*out = *out + tmp->number_of_bytes;
		if ((tmp->label != NULL) && (ft_strcmp(tmp->label, str) == 0))
			*found = 1;
		tmp = tmp->nxt;
	}
}

unsigned int	find_label_value(t_commands *cmd, char *str, int *infos)
{
	t_commands	*tmp;
	int			found;
	int			out;

	if ((cmd->label != NULL) && (ft_strcmp(cmd->label, str) == 0))
		return (0);
	tmp = cmd->prev;
	out = 0;
	found = 0;
	move_forward(tmp, &found, &out, str);
	if (found == 1)
		return (-out);
	tmp = cmd;
	out = 0;
	move_back(tmp, &found, &out, str);
	if (found == 1)
		return (out);
	else if ((*infos & PARSE_ERROR) == 0)
		*infos = *infos + PARSE_ERROR;
	return (0);
}
