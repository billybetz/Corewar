/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:16:26 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/07 23:37:31 by mmatamou         ###   ########.fr       */
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

int		check_instruction2(char *line)
{
	if (ft_strncmp(line, "fork ", 5) == 0)
		return (11);
	else if (ft_strncmp(line, "lldi ", 5) == 0)
		return (13);
	else if (ft_strncmp(line, "lld ", 5) == 0)
		return (12);
	else if (ft_strncmp(line, "lfork ", 5) == 0)
		return (14);
	else if (ft_strncmp(line, "aff ", 4) == 0)
		return (15);
	else
		return (-1);
}

int		check_instruction(char *line)
{
	if (ft_strncmp(line, "live ", 5) == 0)
		return (0);
	else if (ft_strncmp(line, "ldi ", 4) == 0)
		return (9);
	else if (ft_strncmp(line, "sti ", 4) == 0)
		return (10);
	else if (ft_strncmp(line, "st ", 3) == 0)
		return (2);
	else if (ft_strncmp(line, "add ", 4) == 0)
		return (3);
	else if (ft_strncmp(line, "sub ", 4) == 0)
		return (4);
	else if (ft_strncmp(line, "and ", 4) == 0)
		return (5);
	else if (ft_strncmp(line, "or ", 3) == 0)
		return (6);
	else if (ft_strncmp(line, "xor ", 4) == 0)
		return (7);
	else if (ft_strncmp(line, "zjmp ", 5) == 0)
		return (8);
	else if (ft_strncmp(line, "ld ", 3) == 0)
		return (1);
	else
		return (check_instruction2(line));
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
		{
			printf("\nt_tyoe %hhu\n\n", t_type);
			return (parse_error(infos, "Wrong parameter 3\n"));
		}
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

void	rec_label(t_commands *cmd, int i)
{
	int j;
	t_commands *tmp;

	cmd->label = (char*)malloc(sizeof(char) * (i + 1));
	j = 0;
	while ((cmd->line)[j] != LABEL_CHAR)
	{
		(cmd->label)[j] = (cmd->line)[j];
		j = j + 1;
	}
	(cmd->label)[j] = '\0';
	tmp = cmd->prev;
	while (tmp != NULL)
	{
		if ((tmp->label != NULL) && (ft_strcmp(tmp->label, cmd->label) == 0))
		{
				free(cmd->label);
				cmd->label = NULL;
				return ;
		}
		tmp = tmp->prev;
	}
}

int		param_label(t_commands *cmd, char *str)
{
	int i;

	i = 1;
	while (is_labelchars(str[i]) == 1)
		i = i + 1;
	if (i == 1)
		return (-1);
	((cmd->p).lbels)[(cmd->p).count] = (char*)malloc(sizeof(char) * i);
	((cmd->p).lbels)[(cmd->p).count][i - 1] = '\0';
	i = 1;
	while (is_labelchars(str[i]) == 1)
	{
		((cmd->p).lbels)[(cmd->p).count][i - 1] = str[i];
		i = i + 1;
	}
	return (i + 1);
}

int		handle_params(t_commands *cmd, char *str, int *infos, int opcode)
{
	int i;
	int j;
	int len;

	i = 0;
	len = ft_strlen(str);
	(cmd->p).count = 0;
	while (i < len)
	{
		while (ft_isspace(str[i]) == 1)
			i = i + 1;
		if (str[i] == 'r')
		{
			if (check_legality(op_tab[opcode], T_REG, (cmd->p).count, infos) == 0)
			{
				ft_putstr("Should not have put an r\n");
				return (0);
			}
			((cmd->p).type)[(cmd->p).count] = REG_CODE;
			if (((j = ft_specialatoi(&(str[i + 1]), &(((cmd->p).value)[(cmd->p).count])))) == -1)
				return (parse_error(infos, "<- Found ilegal symbol after r\n"));
			i = i + j + 1;
			(cmd->p).count = (cmd->p).count + 1;

		}
		else if (str[i] == '%')
		{
			if (check_legality(op_tab[opcode], T_DIR, (cmd->p).count, infos) == 0)
			{
				ft_putnbr(i);
				ft_putstr("   Should not have put a %\n");
				return (0);
			}
			((cmd->p).type)[(cmd->p).count] = DIR_CODE;
			if (str[i + 1] == LABEL_CHAR)
				j = param_label(cmd, &(str[i + 1]));
			else
				j = ft_specialatoi(&(str[i + 1]), &(((cmd->p).value)[(cmd->p).count]));
			if (j == -1)
				return (parse_error(infos, "<- Found ilegal symbol after %\n"));
			i = i + j + 1;
			(cmd->p).count = (cmd->p).count + 1;
		}
		else if ((ft_isdigit(str[i])) || (str[i] == '+') || (str[i] == '-') || (str[i] == LABEL_CHAR))
		{
			if (check_legality(op_tab[opcode], T_IND, (cmd->p).count, infos) == 0)
			{
				ft_putstr("Should have put either an r or a %\n");
				return (0);
			}
			((cmd->p).type)[(cmd->p).count] = IND_CODE;
			if (str[i] == LABEL_CHAR)
				j = param_label(cmd, &(str[i]));
			else
				j = ft_specialatoi(&(str[i]), &(((cmd->p).value)[(cmd->p).count]));
			if (j == -1)
				return (parse_error(infos, "<- Found ilegal symbol after IND\n"));
			i = i + j;
			(cmd->p).count = (cmd->p).count + 1;
		}
		else if (str[i] != '\0')
		{
			ft_putchar(str[i]);
			return (parse_error(infos, "<- Found ilegal symbol\n"));
		}
	}
	return (0);
}

int		param_byte_num(unsigned int type, unsigned char dir_twoby)
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

unsigned int		find_label_value(t_commands *cmd, char *str, int *infos)
{
	t_commands *tmp;
	int			found;
	int			out;

	if ((cmd->label != NULL) && (ft_strcmp(cmd->label, str) == 0))
		return (0);
	tmp = cmd->prev;
	out = 0;
	found = 0;
	while ((tmp != NULL) && (found == 0))
	{
		out = out + tmp->number_of_bytes;
		if ((tmp->label != NULL) && (ft_strcmp(tmp->label, str) == 0))
			found = 1;
		tmp = tmp->prev;
	}
	if (found == 1)
		return (-out);
	tmp = cmd;
	out = 0;
	while ((tmp != NULL) && (found == 0))
	{
		out = out + tmp->number_of_bytes;
		if ((tmp->label != NULL) && (ft_strcmp(tmp->label, str) == 0))
			found = 1;
		tmp = tmp->nxt;
	}
	if (found == 1)	
		return (out);
	else if ((*infos & PARSE_ERROR) == 0)
		*infos = *infos + PARSE_ERROR;
	return (0);
}

void	countbytes(t_commands *cmd)
{
	int i;
	int byte_count;

	byte_count = 1 + ((cmd->p).tab)->coding_byte;
	i = 0;
	while (i < (cmd->p).count)
	{
		byte_count = byte_count +
			param_byte_num(((cmd->p).type)[i], ((cmd->p).tab)->dir_twoby);
		i = i + 1;
	}
	cmd->number_of_bytes = byte_count;
	cmd->output_to_file = (unsigned char*)malloc(sizeof(unsigned char) * (cmd->number_of_bytes));
}

void	converter(t_commands *cmd, int *infos)
{
	int i;
	int cp;
	int nb; // number of bytes (decalage binaire)
	int bytes;
	int tmp;

	(cmd->output_to_file)[0] = (unsigned char)((cmd->p).tab)->opcode;
	i = 1;
	if (((cmd->p).tab)->coding_byte == 1)
	{
		(cmd->output_to_file)[i] = (unsigned char)((cmd->p).coding_byte);
		i = i + 1;
	}
	cp = 0;
	while (cp < (cmd->p).count)
	{
		nb = 0;
		tmp = ((cmd->p).lbels)[cp] == NULL ? ((cmd->p).value)[cp] : find_label_value(cmd, ((cmd->p).lbels)[cp], infos);
		if ((*infos & PARSE_ERROR) != 0)
			return ;
		bytes = param_byte_num(((cmd->p).type)[cp], ((cmd->p).tab)->dir_twoby);
		while (nb < bytes)
		{
			nb = nb + 1;
			(cmd->output_to_file)[i] = (unsigned char)(tmp >> (8 * (bytes - nb)));
			i = i + 1;
		}
		cp = cp + 1;
	}
}

void	handle_instructions(char *str, int *infos, t_commands *cmd)
{
	int opcode;
	int i;

	if (str[0] == '\0')
		return ;
	if ((((opcode = check_instruction(str))) == -1) && ((*infos & PARSE_ERROR) == 0))
		*infos = *infos + PARSE_ERROR;
	if ((*infos & PARSE_ERROR) != 0)
		return ;
	(cmd->p).tab = &(op_tab[opcode]);
	i = 0;
	while (ft_isalpha(str[i]) == 1)
		i = i + 1;
	handle_params(cmd, &(str[i]), infos, opcode);
	if ((*infos & PARSE_ERROR) != 0)
	{
		ft_putendl("Error in handle_params");
		return ;
	}
	if (param_computations(&(cmd->p), infos, op_tab[opcode]) != 2)
	{
		ft_putendl("Error in coding byte computations");
		if ((*infos & PARSE_ERROR) == 0)
			*infos = *infos + PARSE_ERROR;
		return ;
	}
	printf("!!\n");
	countbytes(cmd);
/*	if ((*infos & PARSE_ERROR) != 0)
	{
		ft_putendl("Error in converter");
	}*/
}

void	handle_commands(t_commands *cmd, int *infos)
{
	int i;
	int j;
	//	int exit;
	t_commands *tmp;

	int k;

	//	exit = 0;

	tmp = cmd;
	while (tmp != NULL)
	{
		ft_putstr(tmp->line);
		i = 0;
		while (is_labelchars((tmp->line)[i]) == 1)
			i = i + 1;
		if (((tmp->line)[i] == LABEL_CHAR) && ((i = i + 1)))
		{
			rec_label(tmp, i);
			while (ft_isspace((tmp->line)[i]) == 1)
				i = i + 1;
			j = i;
		}
		else
			j = 0;
		handle_instructions(&((tmp->line)[j]), infos, tmp);
		if (*infos & PARSE_ERROR)
		{
			ft_putstr("Houve um erro algures\n");
			return ;
		}
		/**********************************************
		printf("\n");
		if ((cmd->p).count >= 1)
		{
			if (((cmd->p).lbels)[0] != NULL)
				printf("1 type %d value(label) %s\n", ((cmd->p).type)[0], ((cmd->p).lbels)[0]);
			else
				printf("1 type %d value %d\n", ((cmd->p).type)[0], ((cmd->p).value)[0]);
		}
		if ((cmd->p).count >= 2)
		{
			if (((cmd->p).lbels)[1] != NULL)
				printf("2 type %d value(label) %s\n", ((cmd->p).type)[1], ((cmd->p).lbels)[1]);
			else
				printf("2 type %d value %d\n", ((cmd->p).type)[1], ((cmd->p).value)[1]);
		}
		if ((cmd->p).count == 3)
		{
			if (((cmd->p).lbels)[2] != NULL)
				printf("3 type %d value(label) %s\n", ((cmd->p).type)[2], ((cmd->p).lbels)[2]);
			else
				printf("3 type %d value %d\n", ((cmd->p).type)[2], ((cmd->p).value)[2]);
		}
		printf("CODING_BYTE %02x\n", (cmd->p).coding_byte);
		k = 0;
		while (k < cmd->number_of_bytes)
		{
			printf("%02hhx ", (cmd->output_to_file)[k]);
			k = k + 1;
		}
		printf("\n");
		*********************************************/

/*		if (cmd->nxt == NULL)
			exit = 1;
		else
			cmd = cmd->nxt;*/
		tmp = tmp->nxt;
	}
	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->number_of_bytes > 0)
		{
			converter(tmp, infos);
			if ((*infos & PARSE_ERROR) != 0)
			{
				ft_putstr("Error in converter\n");
				return ;
			}
			printf("\n");
			if ((tmp->p).count >= 1)
			{
				if (((tmp->p).lbels)[0] != NULL)
					printf("1 type %d value(label) %s\n", ((tmp->p).type)[0], ((tmp->p).lbels)[0]);
				else
					printf("1 type %d value %d\n", ((tmp->p).type)[0], ((tmp->p).value)[0]);
			}
			if ((tmp->p).count >= 2)
			{
				if (((tmp->p).lbels)[1] != NULL)
					printf("2 type %d value(label) %s\n", ((tmp->p).type)[1], ((tmp->p).lbels)[1]);
				else
					printf("2 type %d value %d\n", ((tmp->p).type)[1], ((tmp->p).value)[1]);
			}
			if ((tmp->p).count == 3)
			{
				if (((tmp->p).lbels)[2] != NULL)
					printf("3 type %d value(label) %s\n", ((tmp->p).type)[2], ((tmp->p).lbels)[2]);
				else
					printf("3 type %d value %d\n", ((tmp->p).type)[2], ((tmp->p).value)[2]);
			}
			printf("CODING_BYTE %02x\n", (tmp->p).coding_byte);
			k = 0;
			printf("NUMBER OF BYTES %hhu\n", tmp->number_of_bytes);
			while (k < tmp->number_of_bytes)
			{
				printf("%02hhx ", (tmp->output_to_file)[k]);
				k = k + 1;
			}
			printf("\n");
		}
		tmp = tmp->nxt;
	}
}
