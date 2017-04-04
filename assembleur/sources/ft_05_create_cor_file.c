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

void		add_cor(char *new_name)
{
	int				i;

	i = 0;
	while (new_name[i] != '\0')
		i = i + 1;
	new_name[i] = '.';
	new_name[i + 1] = 'c';
	new_name[i + 2] = 'o';
	new_name[i + 3] = 'r';
	new_name[i + 4] = '\0';
}

char		*executable_name(char *name)
{
	int				i;
	char			*out;

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

int			count_total_bytes(t_commands *cmd)
{
	int total;

	total = 0;
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		total += cmd->number_of_bytes;
		cmd = cmd->nxt;
	}
	return (total);
}

void		print_total_bytes(int total, int cor_fd)
{
	unsigned int	mag;
	unsigned int	mask;
	unsigned int	i[4];

	mask = 0b11111111;
	mag = total;
	i[0] = (mag >> 24) & mask;
	i[1] = (mag >> 16) & mask;
	i[2] = (mag >> 8) & mask;
	i[3] = mag & mask;
	write(cor_fd, &i[0], 1);
	write(cor_fd, &i[1], 1);
	write(cor_fd, &i[2], 1);
	write(cor_fd, &i[3], 1);
}

void		create_cor_file(t_commands *cmd, char *name, char *n_c_str, int p)
{
	int				cor_fd;
	int				i;
	char			*tmp;

	(void)p;
	(void)n_c_str;
	i = -1;
	tmp = executable_name(name);
	cor_fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	while (++i < 136)
		write(cor_fd, &n_c_str[i], 1);
	print_total_bytes(count_total_bytes(cmd), cor_fd);
	while (++i < p)
		write(cor_fd, &n_c_str[i], 1);
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		write(cor_fd, cmd->output_to_file, cmd->number_of_bytes);
		ft_strdel((char **)&(cmd->output_to_file));
		cmd = cmd->nxt;
	}
	ft_strdel(&tmp);
	close(cor_fd);
}
