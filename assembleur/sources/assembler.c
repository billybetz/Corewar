/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:50:09 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/05 00:51:12 by mmatamou         ###   ########.fr       */
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
		i = i - 1;
		out = (char*)malloc(sizeof(char) * (i + 5));
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

void	trimard(char *line)
{
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	while (ft_isspace(line[i]) == 1)
		i = i + 1;
	j = ft_strlen(line) - 1;
	while (j >= 0  && (ft_isspace(line[j]) == 1))
		j--;
	j = j + 1;
	if (j < 0)
	{
		line[0] = '\0';
		return ;
	}
	while (i < j)
	{
		line[k] = line[i];
		k++;
		i++;
	}
	line[k] = '\0';
}

int		is_labelchars(char c)
{
	if ((c >= 'a') && (c <= 'z'))
		return (1);
	else if ((c >= '0') && (c <= '9'))
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

void	assembler(char *name)
{
	int		fd;
	int		cor_fd;
	char	*line;
	int		infos;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Failed to open file\n");
		return ;
	}
	cor_fd = open(executable_name(name), O_CREAT | O_TRUNC | O_WRONLY, 0777);
	infos = 0;
	while (((infos & PARSE_ERROR) == 0) && (get_next_line(fd, &line) > 0))
	{
		trimard(line); 
		ft_putstr("reading\n");
		if ((line[0] != '#') && (line[0] != '\0'))
		{
			if (line[0] == '.')
			{
				ft_putstr("We found a '.'\n");
				name_comment(line, cor_fd, &infos);
				printf("infos %x\n", infos);
			}
			else if ((is_labelchars(line[0]) == 1) && (infos & PARSE_name) && (infos & PARSE_comment))
			{
				check_commands(line, cor_fd, &infos);
			}
			else if ((infos & PARSE_ERROR) == 0)
				infos = infos + PARSE_ERROR;
		}
	}
}
