/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 23:04:09 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/13 16:18:40 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		verify_magic(unsigned char *buf)
{
	if (buf[0] != ((COREWAR_EXEC_MAGIC >> 24) & 0xff))
		return (-1);
	if (buf[1] != ((COREWAR_EXEC_MAGIC >> 16) & 0xff))
		return (-1);
	if (buf[2] != ((COREWAR_EXEC_MAGIC >> 8) & 0xff))
		return (-1);
	if (buf[3] != (COREWAR_EXEC_MAGIC & 0xff))
		return (-1);
	return (0);
}

void	get_name(t_file *f, unsigned char *buf)
{
	i = 4;
	while (i < PROG_NAME_LENGTH + 4)
	{
		(f->prog_name)[i - 4] = buf[i];
		i = i + 1;
	}
}

void	get_ch_size(buf, unsigned int *ch_size)
{
	unsigned int tmp;

	*ch_size = 0;
	tmp = 0;
	tmp = buf[4 + PROG_NAME_LENGTH + 0];
	*ch_size = (*ch_size) | (tmp << 24);
	tmp = buf[4 + PROG_NAME_LENGTH + 1];
	*ch_size = (*ch_size) | (tmp << 16);
	tmp = buf[4 + PROG_NAME_LENGTH + 2];
	*ch_size = (*ch_size) | (tmp << 8);
	tmp = buf[4 + PROG_NAME_LENGTH + 3];
	*ch_size = (*ch_size) | tmp;
}

void	get_comment(t_file *f, unsigned char *buf)
{
	int j;

	j = 0;
	i = 4 + PROG_NAME_LENGTH + 4;
	while (j < COMMENT_LENGTH)
	{
		(f->prog_name)[j] = buf[i + j];
		j = j + 1;
	}
}

int		get_chmap(t_file *f, )
{
}

int		verifier(t_file *f)
{
	unsigned char	buf[4 + PROG_NAME_LENGTH + 4 +
		COMMENT_LENGTH + CHAMP_MAX_SIZE + 20];
	int 			ret;
	unsigned int	ch_size;

	ret = read(f->fd, buf, 4 + PROG_NAME_LENGTH + 4 +
		COMMENT_LENGTH + CHAMP_MAX_SIZE + 20);
	if (ret > 4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH + CHAMP_MAX_SIZE + 20)
		return (print_error("One of the players is too big.\n"));
	if (ret < 4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH)
		return (print_error("One of the players is too small.\n"));
	if (verify_magic(buf) == -1)
		return (print_error("Magic number missing.\n"));
	get_name(f, buf);
	get_ch_size(buf, &ch_size);
	get_comment(f, buf);
	get_champ(f, ch_size, buf);
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
}
