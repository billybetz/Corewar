/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 19:30:38 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/15 15:34:12 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

void	add_cor(char *new_name)
{
	int i;

	i = 0;
	while (new_name[i] != '\0')
		i = i + 1;
	new_name[i] = '.';
	new_name[i + 1] = 'c';
	new_name[i + 2] = 'o';
	new_name[i + 3] = 'r';
	new_name[i + 4] = '\0';
}

char	*executable_name(char *name)
{
	int		i;
	char	*out;

	i = 0;
	while (name[i] != '\0')
		i = i + 1;
	while ((i >= 0) && (name[i] != '.'))
		i = i - 1;
	if (i == -1)
		out = (char*)malloc(sizeof(char) * (ft_strlen(name) + 5));
	else
	{
		out = (char*)malloc(sizeof(char) * (i + 5));
		i = i - 1;
	}
	out[i + 1] = '\0';
	while (i >= 0)
	{
		out[i] = name[i];
		i = i - 1;
	}
	add_cor(out);
	return (out);
}

void	create_cor_file(t_commands *cmd, char *name, char n_c_str[3000], int p)
{
	int cor_fd;

	(void)n_c_str;
	(void)p;
	cor_fd = open(executable_name(name), O_CREAT | O_TRUNC | O_WRONLY, 0777);
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
	//	printf ("ecrit : %x\n", cmd->output_to_file[0]);
		write(cor_fd, cmd->output_to_file, cmd->number_of_bytes);
		cmd = cmd->nxt;
	}
	close(cor_fd);
}
