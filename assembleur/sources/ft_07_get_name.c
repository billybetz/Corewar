/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_06_get_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalmyko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:50:17 by akalmyko          #+#    #+#             */
/*   Updated: 2017/03/16 10:50:18 by akalmyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

static void			print_corewar_exec_magic(char *n_c_str, int *p)
{
	unsigned int	mag;
	unsigned int	mask;

	mask = 0b11111111;
	mag = COREWAR_EXEC_MAGIC;
	n_c_str[(*p)++] = (mag >> 24) & mask;
	n_c_str[(*p)++] = (mag >> 16) & mask;
	n_c_str[(*p)++] = (mag >> 8) & mask;
	n_c_str[(*p)++] = mag & mask;
}

static void			print_zero_name(int j, char *n_c_str, int *p, int startname)
{
	while (j - startname < PROG_NAME_LENGTH + 6)
	{
		n_c_str[(*p)++] = 0x0;
		j++;
	}
}

static int			ft_set_i(int i, char *line)
{
	while (line[i] != '\0')
		i = i + 1;
	i = i - 1;
	while (line[i] != '"')
	{
		if (ft_isspace(line[i]) == 0)
			return (-5);
		i = i - 1;
	}
	return (i);
}

static int			ft_set_j(int j, char *line)
{
	while (ft_isspace(line[j]) == 1)
		j++;
	return (j);
}

int					ft_name(char *line, char *n_c_str, int *p, int *infos)
{
	int				i;
	int				j;
	int				start_name;

	print_corewar_exec_magic(n_c_str, p);
	if (*infos & PARSE_NAME)
		return (parse_error(infos, "err: Two names in the file\n"));
	i = ft_set_i(0, line);
	if (i == -5)
		parse_error(infos, "err: Letters or numbers after name '\"'\n");
	if ((i == 6) || (i - 6 > PROG_NAME_LENGTH))
		return (parse_error(infos, "err: Comment too long\n"));
	j = ft_set_j(5, line);
	if (line[j] != '\"')
		return (parse_error(infos, "err: Char before \" after name\n"));
	start_name = j;
	while (++j < i)
	{
		if (line[j] == '"')
			return (parse_error(infos, "err: '\"' in the name\n"));
		n_c_str[(*p)++] = line[j];
	}
	print_zero_name(j, n_c_str, p, start_name);
	*infos = *infos + PARSE_NAME;
	return (0);
}
