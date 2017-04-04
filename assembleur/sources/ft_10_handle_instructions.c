/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_09.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalmyko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 12:21:36 by akalmyko          #+#    #+#             */
/*   Updated: 2017/03/17 12:21:38 by akalmyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR, 0, 0}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR, 0, 0}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR, 0, 0}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG, 0, 0}, 16, 2, "aff", 1, 0},
	{0, 0, {0, 0, 0}, 0, 0, 0, 0, 0}
};

int				check_instruction2(char *line, t_commands *cmd)
{
	int			(*cmp)(const char*, const char*, size_t);

	cmp = ft_strncmp;
	if (cmp(line, "ld ", 3) == 0 || cmp(line, "ld\t", 3) == 0)
		return (1);
	else if (cmp(line, "fork ", 5) == 0 || cmp(line, "fork\t", 5) == 0)
		return (11);
	else if (cmp(line, "lldi ", 5) == 0 || cmp(line, "lldi\t", 5) == 0)
		return (13);
	else if (cmp(line, "lld ", 4) == 0 || cmp(line, "lld\t", 4) == 0)
		return (12);
	else if (cmp(line, "lfork ", 6) == 0 || cmp(line, "lfork\t", 6) == 0)
		return (14);
	else if (cmp(line, "aff ", 4) == 0 || cmp(line, "aff\t", 4) == 0)
		return (15);
	else
	{
		ft_printf("err: bad instruction #%d\n", cmd->line_nb);
		ft_printf("\"%s\" bad name\n", line);
		return (-1);
	}
}

int				check_instruction(char *line, t_commands *cmd)
{
	int			(*cmp)(const char*, const char*, size_t);

	cmp = ft_strncmp;
	if (cmp(line, "live ", 5) == 0 || cmp(line, "live\t", 5) == 0)
		return (0);
	else if (cmp(line, "ldi ", 4) == 0 || cmp(line, "ldi\t", 4) == 0)
		return (9);
	else if (cmp(line, "sti ", 4) == 0 || cmp(line, "sti\t", 4) == 0)
		return (10);
	else if (cmp(line, "st ", 3) == 0 || cmp(line, "st\t", 3) == 0)
		return (2);
	else if (cmp(line, "add ", 4) == 0 || cmp(line, "add\t", 4) == 0)
		return (3);
	else if (cmp(line, "sub ", 4) == 0 || cmp(line, "sub\t", 4) == 0)
		return (4);
	else if (cmp(line, "and ", 4) == 0 || cmp(line, "and\t", 4) == 0)
		return (5);
	else if (cmp(line, "or ", 3) == 0 || cmp(line, "or\t", 3) == 0)
		return (6);
	else if (cmp(line, "xor ", 4) == 0 || cmp(line, "xor\t", 4) == 0)
		return (7);
	else if (cmp(line, "zjmp ", 5) == 0 || cmp(line, "zjmp\t", 5) == 0)
		return (8);
	else
		return (check_instruction2(line, cmd));
}

static void		ft_just_print(void)
{
	ft_printf("err: in handle_params\n");
}

void			handle_instructions(char *str, int *infos, t_commands *cmd)
{
	int			opcode;
	int			i;

	if (str[0] == '\0')
		return ;
	if ((((opcode = check_instruction(str, cmd))) == -1)
			&& ((*infos & PARSE_ERROR) == 0))
		*infos = *infos + PARSE_ERROR;
	if ((*infos & PARSE_ERROR) != 0)
		return ;
	(cmd->p).tab = &(g_op_tab[opcode]);
	i = 0;
	while (ft_isalpha(str[i]) == 1)
		i = i + 1;
	handle_params(cmd, &(str[i]), infos, opcode);
	if ((*infos & PARSE_ERROR) != 0)
		return (ft_just_print());
	if (param_computations(&(cmd->p), infos, g_op_tab[opcode]) != 2)
	{
		ft_printf("err: in coding byte computations\n");
		if ((*infos & PARSE_ERROR) == 0)
			*infos = *infos + PARSE_ERROR;
		return ;
	}
	countbytes(cmd);
}
