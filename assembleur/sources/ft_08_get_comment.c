/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_07_get_comment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalmyko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:50:26 by akalmyko          #+#    #+#             */
/*   Updated: 2017/03/16 10:50:28 by akalmyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

static void			print_zero_comment(
								int j, char *n_c_str, int *p, int start_comment)
{
	while (j - start_comment < COMMENT_LENGTH + 5)
	{
		n_c_str[(*p)++] = 0x00;
		j++;
	}
}

static int			ft_set_i(int i, char *line)
{
	while (line[i] != '\0')
		i = i + 1;
	while (line[--i] != '"')
	{
		if (ft_isspace(line[i]) == 0)
			return (-5);
	}
	return (i);
}

static int			ft_set_j(int j, char *line)
{
	while (ft_isspace(line[j]) == 1)
		j++;
	return (j);
}

int					ft_comment(char *line, char *n_c_str, int *p, int *infos)
{
	int				i;
	int				j;
	int				start_comment;

	if ((*infos & PARSE_COMMENT) || ((*infos & PARSE_NAME) == 0))
		return (parse_error(infos, "err: Two comments in the file\n"));
	if ((i = ft_set_i(0, line)) == -5)
		return (parse_error(infos, "err: Letters/number after '\"' comment\n"));
	if ((i == 9) || (i - 9 > COMMENT_LENGTH))
		return (parse_error(infos, "err: comment too long\n"));
	j = ft_set_j(8, line);
	if (line[j] != '\"')
		return (parse_error(infos, "err: char before \" after comment\n"));
	start_comment = j;
	while (++j < i)
	{
		if (line[j] == '"')
			return (parse_error(infos, "err: '\"' in the comment\n"));
		n_c_str[(*p)++] = line[j];
	}
	print_zero_comment(j, n_c_str, p, start_comment);
	*infos = *infos + PARSE_COMMENT;
	return (0);
}
