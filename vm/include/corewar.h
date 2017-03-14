/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:28:34 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/12 23:16:11 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../../include/global.h"

typedef struct		s_file
{
	char			*name_of_file;
	int				fd;
	int				n;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned char	champ[CHAMP_MAX_SIZE];
	struct s_file	*nxt;
}					t_file;

typedef struct		s_arg
{
	int				dump;
	unsigned char	nb_players;
	t_file			*files;
/*	char			*fst;
	int				first_fd;
	int				first_n;
	char			*scnd;
	int				second_fd;
	int				second_n;*/
}					t_arg;

typedef struct		s_process
{
	int				reg[REG_NUMBER];
	unsigned int	pc;
	char			carry;
}					t_process;

typedef struct		s_plst
{
	t_process		p;

	struct s_plist	*prev;
	struct s_plist	*nxt;
}					t_plst;

typedef struct		s_all
{
	unsigned char	mem[MEM_SIZE];
	t_plst			*process_list;
	unsigned int	cycle;
	unsigned int	cycle_to_die;
}					t_all;


int		ft_corewar(int nb_args, char **args);
int		print_error(char *str);
int 	print_description(void);

int		arger(int nb_args, char **args, t_arg *a);
int		verify_files(t_arg *a);

#endif
