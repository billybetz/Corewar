/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:01:43 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/21 16:14:49 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

int		parse_error(int *infos, char *error_message)
{
	if ((*infos & PARSE_ERROR) == 0)
		*infos = *infos + PARSE_ERROR;
	ft_putstr_fd(error_message, 2);
	return (0);
}

int		parse_error2(int *infos, char *error_message, int line)
{
	if ((*infos & PARSE_ERROR) == 0)
		*infos = *infos + PARSE_ERROR;
	ft_putstr_fd(error_message, 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(".\n", 2);
	return (0);
}

void	name_comment(char *line, char *n_c_str, int *p, int *infos)
{
	size_t		name_len;
	char		*name;
	size_t		comment_len;
	char		*comment;

	name = NAME_CMD_STRING;
	name_len = ft_strlen(NAME_CMD_STRING);
	comment = COMMENT_CMD_STRING;
	comment_len = ft_strlen(COMMENT_CMD_STRING);
	if (ft_strncmp(line, name, name_len) == 0)
		ft_name(line, n_c_str, p, infos);
	else if (ft_strncmp(line, comment, comment_len) == 0)
		ft_comment(line, n_c_str, p, infos);
	else if ((*infos & PARSE_ERROR) == 0)
	{
		ft_printf("err: entry not recognize : %s\n", line);
		*infos = *infos + PARSE_ERROR;
	}
}
