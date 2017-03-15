/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:31:59 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/13 20:36:04 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

void		create_cmd(t_commands **cmd, t_commands *previous)
{
	*cmd = (t_commands*)malloc(sizeof(t_commands));
	(*cmd)->gnl_ret = 0;
	(*cmd)->label = NULL;
	(*cmd)->line = NULL;
	(*cmd)->number_of_bytes = 0;
	(*cmd)->output_to_file = NULL;
	((*cmd)->p).tab = NULL;
	((*cmd)->p).count = 0;
	((*cmd)->p).coding_byte = 0;
	(((*cmd)->p).type)[0] = 0;
	(((*cmd)->p).type)[1] = 0;
	(((*cmd)->p).type)[2] = 0;
	(((*cmd)->p).value)[0] = 0;
	(((*cmd)->p).value)[1] = 0;
	(((*cmd)->p).value)[2] = 0;
	(((*cmd)->p).lbels)[0] = NULL;
	(((*cmd)->p).lbels)[1] = NULL;
	(((*cmd)->p).lbels)[2] = NULL;
	(*cmd)->prev = previous;
	(*cmd)->nxt = NULL;
}

void		add_cmd_link(t_commands **cmd)
{
	create_cmd(&((*cmd)->nxt), *cmd);
	*cmd = (*cmd)->nxt;
}

t_commands	*get_commands(int fd)
{
	t_commands *cmd;

	create_cmd(&cmd, NULL);
	while (((cmd->gnl_ret = get_next_line(fd, &(cmd->line)))) > 0)
	{
		trimard(cmd->line);
		if (comment_or_end((cmd->line)[0]) == 1)
			free(cmd->line);
		else
			add_cmd_link(&cmd);
	}
	if (cmd->gnl_ret != 1)
	{
		cmd = cmd->prev;
		free(cmd->nxt);
		cmd->nxt = NULL;
	}
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	return (cmd);
}
