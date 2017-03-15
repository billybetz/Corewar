/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:50:09 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/13 20:51:20 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

void	assembler(char *name)
{
	int		fd;
	char	*line;
	int		infos;
	t_commands *cmd;
	char	name_comment_str[3000];
	int		p;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Failed to open file\n");
		return ;
	}
	infos = 0;
	while (((infos & PARSE_ERROR) == 0) && ((infos & PARSE_comment) == 0) && (get_next_line(fd, &line) > 0))
	{
		trimard(line); 
		ft_putstr("reading\n");
		if ((line[0] != '#') && (line[0] != '\0'))
		{
			if (line[0] == '.')
			{
				ft_putstr("We found a '.'\n");
				name_comment(line, name_comment_str, &p, &infos);
				printf("infos %x\n", infos);
			}
			else if ((infos & PARSE_ERROR) == 0)
				infos = infos + PARSE_ERROR;
		}
	}
	cmd = get_commands(fd);
	/**/
	t_commands *tmp;
	tmp = cmd;
	while (tmp != NULL)
	{
		ft_putendl(tmp->line);
		tmp = tmp->nxt;
	}
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	/**/
	handle_commands(cmd, &infos);
	create_cor_file(cmd, name, name_comment_str, p);
}
