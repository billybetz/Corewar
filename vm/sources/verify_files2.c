/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_files2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:27:33 by bbetz             #+#    #+#             */
/*   Updated: 2017/03/21 19:27:34 by bbetz            ###   ########.fr       */
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
	int i;

	i = 4;
	while (i < PROG_NAME_LENGTH + 4)
	{
		f->prog_name[i - 4] = buf[i];
		i = i + 1;
	}
}

void	get_ch_size(unsigned char *buf, unsigned int *ch_size)
{
	unsigned int tmp;

	*ch_size = 0;
	tmp = (unsigned int)buf[8 + PROG_NAME_LENGTH + 0];
	*ch_size = (*ch_size) + (tmp << 24);
	tmp = (unsigned int)buf[8 + PROG_NAME_LENGTH + 1];
	*ch_size = (*ch_size) + (tmp << 16);
	tmp = (unsigned int)buf[8 + PROG_NAME_LENGTH + 2];
	*ch_size = (*ch_size) + (tmp << 8);
	tmp = (unsigned int)buf[8 + PROG_NAME_LENGTH + 3];
	*ch_size = (*ch_size) + tmp;
}
