/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_15_handle_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalmyko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:49:02 by akalmyko          #+#    #+#             */
/*   Updated: 2017/03/21 16:28:10 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

static int		ft_if_str_r(t_commands *cmd, int **tab, int *infos, char *str)
{
	if (check_legality(
				g_op_tab[*tab[OPCODE]], T_REG, (cmd->p).count, infos) == 0)
		return (10);
	((cmd->p).type)[(cmd->p).count] = REG_CODE;
	if (((*tab[J_T] = ft_specialatoi(&(str[*tab[I_T] + 1]),
								&(((cmd->p).value)[(cmd->p).count])))) == -1)
		return (11);
	*tab[I_T] = *tab[I_T] + *tab[J_T] + 1;
	(cmd->p).count = (cmd->p).count + 1;
	return (0);
}

static int		str_percent(t_commands *cmd, int **tab, int *infos, char *str)
{
	if (check_legality(
				g_op_tab[*tab[OPCODE]], T_DIR, (cmd->p).count, infos) == 0)
	{
		ft_putnbr(*tab[I_T]);
		ft_putstr("   Should not have put a %\n");
		return (12);
	}
	((cmd->p).type)[(cmd->p).count] = DIR_CODE;
	if (str[*tab[I_T] + 1] == LABEL_CHAR)
		*tab[J_T] = param_label(cmd, &(str[*tab[I_T] + 1]));
	else
		*tab[J_T] = ft_specialatoi(
					&(str[*tab[I_T] + 1]), &(((cmd->p).value)[(cmd->p).count]));
	if (*tab[J_T] == -1)
		return (13);
	*tab[I_T] = *tab[I_T] + *tab[J_T] + 1;
	(cmd->p).count = (cmd->p).count + 1;
	return (0);
}

static int		ft_else_if(t_commands *cmd, int **tab, int *infos, char *str)
{
	if (check_legality(
				g_op_tab[*tab[OPCODE]], T_IND, (cmd->p).count, infos) == 0)
		return (14);
	((cmd->p).type)[(cmd->p).count] = IND_CODE;
	if (str[*tab[I_T]] == LABEL_CHAR)
		*tab[J_T] = param_label(cmd, &(str[*tab[I_T]]));
	else
		*tab[J_T] = ft_specialatoi(
						&(str[*tab[I_T]]), &(((cmd->p).value)[(cmd->p).count]));
	if (*tab[J_T] == -1)
		return (15);
	*tab[I_T] = *tab[I_T] + *tab[J_T];
	(cmd->p).count = (cmd->p).count + 1;
	return (0);
}

static int		ft_check_error(int error, int *infos, t_commands *cmd)
{
	if (error < 10)
		return (FALSE);
	if (error == 10)
		parse_error2(infos, "Should not have an r in cmd n˚", cmd->line_nb);
	else if (error == 11)
	{
		ft_putendl(cmd->line);
		parse_error2(infos, "ilegal symbol after r in cmd n˚", cmd->line_nb);
	}
	else if (error == 12)
		;
	else if (error == 13)
		parse_error2(infos, "ilegal symbol after % in cmd n˚", cmd->line_nb);
	else if (error == 14)
		parse_error2(infos, ERR_MESS1, cmd->line_nb);
	else if (error == 15)
		parse_error2(infos, "ilegal symbol after IND in cmd n˚", cmd->line_nb);
	else if (error == 16)
		parse_error2(infos, "ilegal symbol in cmd n˚", cmd->line_nb);
	return (TRUE);
}

int				handle_params(t_commands *cmd, char *str, int *info, int opcode)
{
	int			**tab;
	int			error;

	tab = ft_init_tab(opcode, NULL, (int)ft_strlen(str), 0);
	(cmd->p).count = 0;
	error = 0;
	while (*tab[I_T] < *tab[LEN_T])
	{
		while (ft_isspace(str[*tab[I_T]]) == 1)
			*tab[I_T] = *tab[I_T] + 1;
		if (str[*tab[I_T]] == 'r')
			error = ft_if_str_r(cmd, tab, *&info, str);
		else if (str[*tab[I_T]] == '%')
			error = str_percent(cmd, tab, *&info, str);
		else if ((ft_isdigit(str[*tab[I_T]])) || (str[*tab[I_T]] == '+')
				|| (str[*tab[I_T]] == '-') || (str[*tab[I_T]] == LABEL_CHAR))
			error = ft_else_if(cmd, tab, *&info, str);
		else if (str[*tab[I_T]] != '\0')
			ft_printf("%c", str[*tab[I_T]], error = 16);
		if (ft_check_error(error, *&info, cmd) == TRUE)
			return ((int)ft_init_tab(opcode, tab, 0, FREE_ALL));
	}
	ft_init_tab(opcode, tab, 0, FREE_ALL);
	return (0);
}
