/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembleur.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:03:26 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/21 16:18:39 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLEUR_H
# define ASSEMBLEUR_H

# include "../../include/global.h"

# define PARSE_ERROR	0b1
# define PARSE_NAME		0b10
# define PARSE_COMMENT	0b100
# define FIRST_OPCODE	0b1000
# define ERR_MESS1 "Should have either an r or a % in cmd n˚"

# define WRITER_SIZE	500

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define NAM_COM_STR_BUFSIZE 3000

# define I_T 0
# define J_T 1
# define OPCODE 2
# define LEN_T 3
# define FREE_ALL 1

# define TRUE 1
# define FALSE 0

/*
** define
*/
t_op g_op_tab[17];

typedef struct			s_params
{
	t_op				*tab;
	int					count;
	unsigned char		coding_byte;
	unsigned int		type[3];
	int					value[3];
	char				*(lbels[3]);
}						t_params;

typedef struct			s_writer
{
	int					char_counter;
	unsigned char		storer[WRITER_SIZE];
	struct s_writer		*prev;
	struct s_writer		*nxt;
}						t_writer;

typedef struct			s_commands
{
	int					gnl_ret;
	char				*label;
	char				*line;
	int					line_nb;
	unsigned char		number_of_bytes;
	unsigned char		*output_to_file;
	t_params			p;

	struct s_commands	*prev;
	struct s_commands	*nxt;
}						t_commands;
/*
** main.c
*/
void					ft_show_error_and_exit(char *str);
/*
** name_comment.c
*/
int						ft_name(char *line, char *n_c_str, int *p,
									int *infos);
int						ft_comment(char *line, char *n_c_str, int *p,
									int *infos);
/*
** <writer.c> Recording what will be written to the file and writing it
*/
void					writer_init(t_writer **w, t_writer *previous);
void					putchar_to_w(t_writer **w, unsigned char c);
void					putstr_to_w(t_writer **w, unsigned char *str);
void					put_w_to_file(t_writer *w, int cor_fd);
/*
** <check_commands.c> Record the lines after .name and .comment
*/
void					create_cmd(t_commands **cmd, t_commands *prev, int a);
t_commands				*get_commands(int fd);
/*
** <chars_strs.c>
*/
int						comment_or_end(char c);
int						is_labelchars(char c);
void					trimard(char *line);
/*
** <handle_commands.c>
*/
void					handle_commands(t_commands *cmd, int *infos);
/*
** <create_cor_file.c>
*/
void					create_cor_file(t_commands *cmd, char *n,
								char *n_c_str, int p);

void					name_comment(char *line, char *n_c_str,
								int *p, int *infos);
void					assembler(char *name);
int						parse_error(int	*infos, char *error_message);
int						parse_error2(int *infos, char *error_mess, int line);
void					handle_instructions(char *str, int *inf,
								t_commands *cmd);
void					rec_label(t_commands *cmd, int i);
void					converter(t_commands *cmd, int *infos);
int						handle_params(t_commands *cmd, char *str,
								int *infos, int opcode);
int						param_computations(t_params *p, int *infos, t_op tab);
void					countbytes(t_commands *cmd);

int						check_legality(t_op tab, unsigned char t_type,
								int nb_param, int *infos);
int						ft_specialatoi(char *str, int *result);
int						param_label(t_commands *cmd, char *str);

int						**ft_init_tab(int opcode, int **tab_free,
								int len, int option);
unsigned int			find_label_value(t_commands *cmd, char *str, int *inf);
void					ft_free(void *pointer);

/*
** op_tab
*/

#endif
