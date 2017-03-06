/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:01:43 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/05 18:15:14 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

int		parse_error(int *infos, char *error_message)
{
	if ((*infos & PARSE_ERROR) == 0)
		*infos = *infos + PARSE_ERROR;
	ft_putstr(error_message);
	return (0);
}

void	print_corewar_exec_magic(int cor_fd)
{
	unsigned int mag;
	unsigned int mask;

	mask = 0b11111111;
	mag = COREWAR_EXEC_MAGIC;
	ft_putchar_fd((mag >> 24) & mask, cor_fd);
	ft_putchar_fd((mag >> 16) & mask, cor_fd);
	ft_putchar_fd((mag >> 8) & mask, cor_fd);
	ft_putchar_fd(mag & mask, cor_fd);
}

void	print_zero_name(int j, int cor_fd, int start_name)
{
	while (j - start_name < PROG_NAME_LENGTH + 8)
	{
		ft_putchar_fd(0x00, cor_fd);
		j++;
	}
}

int		name(char *line, int cor_fd, int *infos)
{
	int i;
	int j;
	int	start_name;

	i = 0;
	print_corewar_exec_magic(cor_fd);
	if (*infos & PARSE_name)
		return (parse_error(infos, "Two names in the file\n"));
	while (line[i] != '\0')
		i = i + 1;
	i = i - 1;
	while (line[i] != '"')
	{
		if (ft_isspace(line[i]) == 0)
		{
			ft_putchar(line[i]);
			ft_putchar('\n');
			return (parse_error(infos, "<name>Letters or numbers after the final '\"'\n"));
		}
		i = i - 1;
	}
	if ((i == 6) || (i - 6 > PROG_NAME_LENGTH))
		return (parse_error(infos, "Too big or only one '\"'\n"));
	j = 5;
	while (ft_isspace(line[j]) == 1)
		j++;
	if (line[j] != '\"')
		return (parse_error(infos, "character before double quote after name\n"));
	start_name = j;
	while (++j < i)
	{
		if (line[j] == '"')
			return (parse_error(infos, "'\"' in the name\n"));
		ft_putchar_fd(line[j], cor_fd);
	}
	print_zero_name(j, cor_fd, start_name);
	*infos = *infos + PARSE_name;
	return (0);
}

void	print_zero_comment(int j, int cor_fd, int start_comment)
{
	while (j - start_comment < COMMENT_LENGTH + 6)
	{
		ft_putchar_fd(0x00, cor_fd);
		j++;
	}
}


int     comment(char *line, int cor_fd, int *infos)
{
	int i;
	int j;
	int start_comment;

	i = 0;
	if ((*infos & PARSE_comment) || ((*infos & PARSE_name) == 0))
		return (parse_error(infos, "Two comments in the file or no name before comment\n"));
	while (line[i] != '\0')
		i = i + 1;
	while (line[--i] != '"')
	{
		if (ft_isspace(line[i]) == 0)
			return (parse_error(infos, "<comment>Letters or numbers after the final '\"'\n"));
	}
	if ((i == 9) || (i - 9 > COMMENT_LENGTH))
		return (parse_error(infos, "Too big or only one '\"'\n"));
	j = 8;
	while (ft_isspace(line[j]) == 1)
		j++;
	if (line[j] != '\"')
		return (parse_error(infos, "character before double quote after name\n"));
	start_comment = j;
	while (++j < i)
	{
		if (line[j] == '"')
			return (parse_error(infos, "'\"' in the comment\n"));
		ft_putchar_fd(line[j], cor_fd);
	}
	print_zero_comment(j, cor_fd, start_comment);
	*infos = *infos + PARSE_comment;
	return (0);
}

void	name_comment(char *line, int cor_fd, int *infos)
{
	ft_putendl(line);
	if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
		name(line, cor_fd, infos);
	else if (ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
		comment(line, cor_fd, infos);
	else if ((*infos & PARSE_ERROR) == 0)
		*infos = *infos + PARSE_ERROR;
}
