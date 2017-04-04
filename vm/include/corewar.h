/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:28:34 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/22 22:09:50 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../../include/global.h"
# include <ncurses.h>
# define BUF_S 4+PROG_NAME_LENGTH+8+COMMENT_LENGTH+CHAMP_MAX_SIZE+20


t_op g_op_tab[17];

typedef struct			s_file
{
	char				*name_of_file;
	int					fd;
	int					n;
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		champ[CHAMP_MAX_SIZE];
	int					chmp_size;
	struct s_file		*nxt;
	unsigned char		count;
	int					clr;
}						t_file;

typedef struct			s_arg
{
	int					dump;
	unsigned char		nb_players;
	t_file				*files;

}						t_arg;

typedef struct			s_process
{
	int					reg[REG_NUMBER + 1];
	unsigned int		lpc;
	int					pc;
	unsigned int		inst_per;
	char				carry;
	unsigned			lives_since_check;

	int					nb;
//	char				nw;
	int					clr;
	int					param;
	unsigned char		code;
	struct s_process	*prev;
	struct s_process	*nxt;
}						t_process;

typedef struct			s_curses
{
	WINDOW				*mem;
	WINDOW				*infos;
}						t_curses;

typedef struct			s_all
{
	unsigned char		mem[MEM_SIZE];
	unsigned char		clr[MEM_SIZE];
	t_process			*process_list;
	int					last_live;
	unsigned int		nb_lives_since_last;

	int					nxt_nb;
	t_curses			crs;
	unsigned char		tmp_clr;
	char				curses;
	int					*players_nb;
	unsigned char		how_many_players;
	unsigned int		cycle;
	unsigned int		next_check;
	unsigned int		cycle_to_die;
	int					non_dec_checks;
	t_arg				*arg;
}						t_all;


int		ft_corewar(int nb_args, char **args);
int		print_error(char *str);
int 	print_description(void);
int		arger(int nb_args, char **args, t_arg *a, t_all *gen);
int     arg_parser(int nb_args, char **args, t_arg *a, t_all *gen);
int     arg_parser5(t_arg *a, int i_n[2], t_file *tmp);
int		verify_files(t_arg *a);
void	write_to_mem(t_arg *a, t_all *gen);
void	dump_mem(unsigned char *mem, int size);
void	war(t_arg *a, t_all *gen);
void	war_while(t_all *gen);
void	cursed_war_while(t_all *gen);
int		is_command(t_all *gen, t_process *p);
void	apply_commands(t_all *gen, t_process *p);
char	*get_player_name(t_all *gen, int nb);
void	byte_reader(int *number, unsigned char *mem, int start, int len);
int		get_ind_address(unsigned char *mem, int start);
void	byte_writer(int number, t_all *gen, int start, int len);
void	change_carry(int result, char *carry);
void	cmd_live(t_all *gen, t_process *p);
void	cmd_ld(t_all *gen, t_process *p);
void	cmd_st(t_all *gen, t_process *p);
void	cmd_add(t_all *gen, t_process *p);
void	cmd_sub(t_all *gen, t_process *p);
void	cmd_and(t_all *gen, t_process *p);
void	cmd_or(t_all *gen, t_process *p);
void	cmd_xor(t_all *gen, t_process *p);
void	cmd_zjmp(t_all *gen, t_process *p);
void	cmd_ldi(t_all *gen, t_process *p);
void	cmd_sti(t_all *gen, t_process *p);
void	cmd_fork(t_all *gen, t_process *p);
void    cmd_lfork(t_all *gen, t_process *p);
void	cmd_lld(t_all *gen, t_process *p);
void	cmd_lldi(t_all *gen, t_process *p);
void	cmd_aff(t_all *gen, t_process *p);
int		check_player_nb(int nb, t_all *gen);
int		get_param(t_process *p, unsigned char *mem, int start, char dir2b_l);
void	move_pc(t_process *p, int delta);
int		c_b_quant(unsigned char coding_byte, t_op op);
void	to_kill_or_not_to_kill(t_all *gen, t_process **p);

void	get_name(t_file *f, unsigned char *buf);
int		verify_magic(unsigned char *buf);
void	get_ch_size(unsigned char *buf, unsigned int *ch_size);

void	start_tf(t_file **f);
int		ft_s_atoi(char *str, int *result);

void	players(t_all *gen);
void	find_winner(t_all *gen);

/*
 * cursed_functions.c
 */
void	init_display(t_all *gen);
void	put_membyte(int pc, t_all *gen, int reverse);
void	put_proc_nb(t_all *gen, t_process *p);

#endif
