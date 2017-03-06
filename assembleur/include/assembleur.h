/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembleur.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:03:26 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/05 23:06:33 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLEUR_H
# define ASSEMBLEUR_H

#include "../../include/corewar.h"

/**/
#include <stdio.h>
/**/

#define PARSE_ERROR		0b1
#define PARSE_name		0b10
#define PARSE_comment	0b100
#define	FIRST_OPCODE	0b1000

#define WRITER_SIZE		500
/*
#define 
*/
typedef struct		s_params
{
	int				count;
	unsigned char	coding_byte;	
	unsigned int	type[3];
	int				value[3];
}					t_params;

typedef struct		s_writer
{
	int				char_counter;
	unsigned char	storer[WRITER_SIZE];
	struct s_writer	*prev;
	struct s_writer	*nxt;
}					t_writer;

/*
 * Recording what will be written to the file and writing it
 */
void	writer_init(t_writer **w, t_writer *previous);
void	putchar_to_w(t_writer **w, unsigned char c);
void	putstr_to_w(t_writer **w, unsigned char *str);
void	put_w_to_file(t_writer *w, int cor_fd);

/*
 *
 */

void	name_comment(char *line, int fd, int *infos);
void	assembler(char *name);
int		check_commands(char *line, int cor_fd, int *infos);
int		is_labelchars(char c);
int		parse_error(int	*infos, char *error_message);

#endif
