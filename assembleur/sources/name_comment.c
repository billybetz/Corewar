/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:01:43 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/13 20:51:18 by bbetz            ###   ########.fr       */
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

void	print_corewar_exec_magic(char n_c_str[3000], int *p)
{
	unsigned int mag;
	unsigned int mask;

	mask = 0b11111111;
	mag = COREWAR_EXEC_MAGIC;
	n_c_str[(*p)++] = (mag >> 24) & mask;
	n_c_str[(*p)++] = (mag >> 16) & mask;
	n_c_str[(*p)++] = (mag >> 8) & mask;
	n_c_str[(*p)++] = mag & mask;
}

void	print_zero_name(int j, char n_c_str[3000], int *p, int start_name)
{
	while (j - start_name < PROG_NAME_LENGTH + 8)
	{
		n_c_str[(*p)++] = 0x00;
		j++;
	}
}

int		name(char *line, char n_c_str[3000], int *p, int *infos)
{
	int i;
	int j;
	int	start_name;

	i = 0;
	print_corewar_exec_magic(n_c_str, p);
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
		n_c_str[(*p)++] = line[j];
	}
	print_zero_name(j, n_c_str, p, start_name);
	*infos = *infos + PARSE_name;
	return (0);
}

void	print_zero_comment(int j, char n_c_str[3000], int *p, int start_comment)
{
	while (j - start_comment < COMMENT_LENGTH + 6)
	{
		n_c_str[(*p)++] = 0x00;
		j++;
	}
}


int     comment(char *line, char n_c_str[3000], int *p, int *infos)
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
		n_c_str[(*p)++] = line[j];
	}
	print_zero_comment(j, n_c_str, p, start_comment);
	*infos = *infos + PARSE_comment;
	return (0);
}

void	name_comment(char *line, char n_c_str[3000], int *p, int *infos)
{
	*p = 0;
	ft_putendl(line);
	if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
		name(line, n_c_str, p, infos);
	else if (ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
		comment(line, n_c_str, p, infos);
	else if ((*infos & PARSE_ERROR) == 0)
		*infos = *infos + PARSE_ERROR;
}
