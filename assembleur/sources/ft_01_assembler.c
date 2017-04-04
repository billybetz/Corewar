/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:50:09 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/21 15:10:16 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

static void			ft_get_name_comment_str(int *infos, int fd, int *p,
											char *name_comment_str)
{
	char			*line;

	while (((*infos & PARSE_ERROR) == 0)
		&& ((*infos & PARSE_COMMENT) == 0) && (get_next_line(fd, &line) > 0))
	{
		trimard(line);
		if ((line[0] != '#') && (line[0] != '\0'))
		{
			if (line[0] == '.')
				name_comment(line, name_comment_str, *&p, *&infos);
			else if ((*infos & PARSE_ERROR) == 0)
			{
				ft_putstr("err: The file should contain a name first of all\n");
				*infos = *infos + PARSE_ERROR;
			}
		}
		free(line);
	}
}

static void			ft_free_cmd(t_commands *cmd)
{
	t_commands		*tmp;

	while (cmd)
	{
		tmp = cmd;
		ft_strdel(&(cmd->line));
		ft_strdel(&(cmd->label));
		ft_strdel(&(cmd->p.lbels[0]));
		ft_strdel(&(cmd->p.lbels[1]));
		ft_strdel(&(cmd->p.lbels[2]));
		ft_strdel((char **)&(cmd->output_to_file));
		cmd = cmd->nxt;
		free(tmp);
	}
}

void				assembler(char *name)
{
	int				fd;
	int				p;
	int				infos;
	char			name_comment_str[NAM_COM_STR_BUFSIZE];
	t_commands		*cmd;

	p = 0;
	fd = open(name, O_RDONLY);
	if (fd < 0)
		ft_show_error_and_exit("err: Failed to open file\n");
	infos = 0;
	ft_get_name_comment_str(&infos, fd, &p, name_comment_str);
	if ((infos & PARSE_ERROR))
		return ;
	if (!(cmd = get_commands(fd)))
		ft_show_error_and_exit("Error: no cmd in the file\n");
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	handle_commands(cmd, &infos);
	if ((infos & PARSE_ERROR) == 0)
	{
		create_cor_file(cmd, name, name_comment_str, p);
		ft_printf("*--------------*\n* .cor created *\n*--------------*\n");
	}
	ft_free_cmd(cmd);
}
