/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 23:33:24 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/05 17:24:00 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

t_op    op_tab[17] =
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

int		check_instruction2(char *line, int cor_fd, int i)
{
	(void)cor_fd;
	if (ft_strncmp(line + i, "fork ", 5) == 0)
		return (11);
	else if (ft_strncmp(line + i, "lldi ", 5) == 0)
		return (13);
	else if (ft_strncmp(line + i, "lld ", 5) == 0)
		return (12);
	else if (ft_strncmp(line + i, "lfork ", 5) == 0)
		return (14);
	else if (ft_strncmp(line + i, "aff ", 4) == 0)
		return (15);
	else
		return (-1);
}

int		check_instruction(char *line, int cor_fd, int i)
{
	if (ft_strncmp(line + i, "live ", 5) == 0)
		return (0);
	else if (ft_strncmp(line + i, "ldi ", 4) == 0)
		return (9);
	else if (ft_strncmp(line + i, "sti ", 4) == 0)
		return (10);
	else if (ft_strncmp(line + i, "st ", 3) == 0)
		return (2);
	else if (ft_strncmp(line + i, "add ", 4) == 0)
		return (3);
	else if (ft_strncmp(line + i, "sub ", 4) == 0)
		return (4);
	else if (ft_strncmp(line + i, "and ", 4) == 0)
		return (5);
	else if (ft_strncmp(line + i, "or ", 3) == 0)
		return (6);
	else if (ft_strncmp(line + i, "xor ", 4) == 0)
		return (7);
	else if (ft_strncmp(line + i, "zjmp ", 5) == 0)
		return (8);
	else if (ft_strncmp(line + i, "ld ", 3) == 0)
		return (1);
	else
		return (check_instruction2(line, cor_fd, i));
}

int		check_legality(t_op tab, unsigned char t_type, int nb_param, int *infos)
{
	if (nb_param == 0)
	{
		if ((t_type & (tab.param).p1) == 0)
			return (parse_error(infos, "Wrong parameter 1\n"));
	}
	else if (nb_param == 1)
	{
		if ((t_type & (tab.param).p2) == 0)
			return (parse_error(infos, "Wrong parameter 2\n"));
	}
	else if (nb_param == 2)
	{
		if ((t_type & (tab.param).p3) == 0)
			return (parse_error(infos, "Wrong parameter 3\n"));
	}
	else if (nb_param >= 3)
		return (parse_error(infos, "Too many arguments!!!!\n"));
	return (1);
}

int		ft_specialatoi(char *str, int *result)
{
	int i;
	int sign;
	int j;

	i = 0;
	*result = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '+') || (str[i] == '-'))
		i = i + 1;
	j = i;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		*result = (*result * 10) + str[i] - 48;
		i = i + 1;
	}
	*result = *result * sign;
	if (((str[i] == SEPARATOR_CHAR) || (str[i] == '\0')) && (i != j))
		return (i + 1);
	else
		return (-1);
}

int		param_computations(t_params *p, int *infos, t_op tab)
{
	int i;
	unsigned char c_b;
	unsigned char type_tmp;

	if (p->count != tab.nb_param)
		return (parse_error(infos, "Not enough arguments!!!!\n"));
	c_b = 0;
	i = 0;
	while (i < p->count)
	{
		type_tmp = (unsigned char)(p->type)[i] << (6 - i * 2);
		c_b = c_b + type_tmp;
		i = i + 1;
	}
	p->coding_byte = c_b;
	return (2);
}

int		check_commands(char *line, int cor_fd, int *infos)
{
	int			i;
	int			j;
	int			ret;
	t_params	p;

	i = 0;
	while (is_labelchars(line[i]) == 1)
		i = i + 1;
	if (line[i] == LABEL_CHAR)
		i += 1;
	else
		i = 0;
	while (ft_isspace(line[i]) == 1)
		i = i + 1;
	if (((ret = check_instruction(line, cor_fd, i))) == -1)
		return (parse_error(infos, "bad instruction\n"));
	while (line[i] && ft_isspace(line[i]) == 0)
		i++;
	p.count = 0;
	while (line[i] != '\0')
	{
		while (ft_isspace(line[i]) == 1)
			i = i + 1;
		if (line[i] == 'r')
		{
			if (check_legality(op_tab[ret], T_REG, p.count, infos) == 0)
				return (0);
			(p.type)[p.count] = REG_CODE;
			if (((j = ft_specialatoi(&(line[i + 1]), &((p.value)[p.count])))) == -1)
				return (parse_error(infos, "<- Found ilegal symbol after r\n"));
			i = i + j + 1;
			p.count = p.count + 1;

		}
		else if ((line[i] == '%') && (ft_isdigit(line[i + 1])))
		{
			if (check_legality(op_tab[ret], T_DIR, p.count, infos) == 0)
				return (0);
			(p.type)[p.count] = DIR_CODE;
			if (((j = ft_specialatoi(&(line[i + 1]), &((p.value)[p.count])))) == -1)
				return (parse_error(infos, "<- Found ilegal symbol after %\n"));
			i = i + j + 1;
			p.count = p.count + 1;
		}
		else if ((ft_isdigit(line[i])) || (line[i] == '+') || (line[i] == '-'))
		{
			if (check_legality(op_tab[ret], T_IND, p.count, infos) == 0)
				return (0);
			(p.type)[p.count] = IND_CODE;
			if (((j = ft_specialatoi(&(line[i]), &((p.value)[p.count])))) == -1)
				return (parse_error(infos, "<- Found ilegal symbol after IND\n"));
			i = i + j;
			p.count = p.count + 1;
		}
		else if (line[i] != '\0')
			return (parse_error(infos, "<- Found ilegal symbol\n"));
	}
	ft_putstr("<<<<<<<<<<<");
	ft_putstr((op_tab[ret]).e);
	ft_putstr(">>>>>>>>>>>\n");
	if (p.count >= 1)
		printf("type %d value %d\n", (p.type)[0], (p.value)[0]);
	if (p.count >= 2)
		printf("type %d value %d\n", (p.type)[1], (p.value)[1]);
	if (p.count == 3)
		printf("type %d value %d\n", (p.type)[2], (p.value)[2]);
	if (param_computations(&p, infos, op_tab[ret]) != 2)
		return (0);
	printf("\nCODING_BYTE %x\n", p.coding_byte);
	return (0);
}
