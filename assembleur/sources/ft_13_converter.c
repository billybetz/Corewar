/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_17_converter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalmyko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 17:08:40 by akalmyko          #+#    #+#             */
/*   Updated: 2017/03/18 17:08:41 by akalmyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

static int		param_byte_num(unsigned int type, unsigned char dir_twoby)
{
	if (type == REG_CODE)
		return (1);
	else if (type == IND_CODE)
		return (2);
	else
	{
		if (dir_twoby == 1)
			return (2);
		return (4);
	}
}

void			countbytes(t_commands *cmd)
{
	int			i;
	int			byte_count;

	byte_count = 1 + ((cmd->p).tab)->coding_byte;
	i = 0;
	while (i < (cmd->p).count)
	{
		byte_count = byte_count +
				param_byte_num(((cmd->p).type)[i], ((cmd->p).tab)->dir_twoby);
		i = i + 1;
	}
	cmd->number_of_bytes = byte_count;
	cmd->output_to_file = (unsigned char*)malloc(
								sizeof(unsigned char) * (cmd->number_of_bytes));
}

static int		ft_set_i_and_cp(t_commands *cmd, int *cp)
{
	int			i;

	(cmd->output_to_file)[0] = (unsigned char)((cmd->p).tab)->opcode;
	i = 1;
	if (((cmd->p).tab)->coding_byte == 1)
	{
		(cmd->output_to_file)[i] = (unsigned char)((cmd->p).coding_byte);
		i = i + 1;
	}
	*cp = 0;
	return (i);
}

void			converter(t_commands *cmd, int *infos)
{
	int			i;
	int			cp;
	int			nb;
	int			bytes;
	int			tmp;

	i = ft_set_i_and_cp(cmd, &cp);
	while (cp < (cmd->p).count)
	{
		nb = 0;
		if ((cmd->p).lbels[cp] == NULL)
			tmp = ((cmd->p).value)[cp];
		else
			tmp = find_label_value(cmd, ((cmd->p).lbels)[cp], *&infos);
		if ((*infos & PARSE_ERROR) != 0)
			return ;
		bytes = param_byte_num(((cmd->p).type)[cp++], (cmd->p.tab)->dir_twoby);
		while (nb < bytes)
		{
			nb = nb + 1;
			(cmd->output_to_file)[i] = (unsigned char)(
													tmp >> (8 * (bytes - nb)));
			i = i + 1;
		}
	}
}
