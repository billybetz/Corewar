/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 23:04:09 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/22 20:29:26 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_comment(t_file *f, unsigned char *buf)
{
	int j;
	int i;

	j = 0;
	i = PROG_NAME_LENGTH + 4 + 8;
	while (j < COMMENT_LENGTH)
	{
		f->comment[j] = buf[i + j];
		j = j + 1;
	}
}

int		get_champ(t_file *f, unsigned int ch_size, unsigned char *buf, int ret)
{
	int i;
	int j;

	if ((int)ch_size != ret - 16 - PROG_NAME_LENGTH - COMMENT_LENGTH)
	{
		return (-1);
	}
	j = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	i = 0;
	while (j + i < ret)
	{
		(f->champ)[i] = buf[j + i];
		i = i + 1;
	}
	return (0);
}

int		verifier(t_file *f)
{
	int				ret;
	unsigned int	ch_size;
	unsigned char	buf[BUF_S];

	ret = read(f->fd, buf, 4 + PROG_NAME_LENGTH + 8 +
		COMMENT_LENGTH + CHAMP_MAX_SIZE + 20);
	if (ret > 4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH + CHAMP_MAX_SIZE + 20)
		return (print_error("One of the players is too big.\n"));
	if (ret < 4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH)
		return (print_error("One of the players is too small.\n"));
	if (verify_magic(buf) == -1)
		return (print_error("Magic number missing.\n"));
	get_name(f, buf);
	get_ch_size(buf, &ch_size);
	f->chmp_size = ch_size;
	get_comment(f, buf);
	if (get_champ(f, ch_size, buf, ret) == -1)
		return (-1);
	return (0);
}

int		verify_files(t_arg *a)
{
	t_file *tmp;

	tmp = a->files;
	while (tmp != NULL)
	{
		if (verifier(tmp) == -1)
			return (-1);
		tmp = tmp->nxt;
	}
	return (0);
}
