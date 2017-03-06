/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 17:31:30 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/06 11:27:48 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

void	writer_init(t_writer **w, t_writer *previous)
{
	*w = (t_writer*)malloc(sizeof(t_writer));
	(*w)->char_counter = 0;
	(*w)->nxt = NULL;
	(*w)->prev = previous;
}

void	putchar_to_w(t_writer **w, unsigned char c)
{
	if ((*w)->char_counter == WRITER_SIZE)
	{
		writer_init(&((*w)->nxt), *w);
		*w = (*w)->nxt;
	}
	((*w)->storer)[(*w)->char_counter] = c;
	(*w)->char_counter = (*w)->char_counter + 1;
}

void	putstr_to_w(t_writer **w, unsigned char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		putchar_to_w(w, str[i]);
		i = i + 1;
	}
}

void	put_w_to_file(t_writer *w, int cor_fd)
{
	int sair;

	while (w->prev != NULL)
		w = w->prev;
	sair = 0;
	while (sair == 0)
	{
		write(cor_fd, w->storer, w->char_counter);
		if (w->nxt != NULL)
		{
			w = w->nxt;
			free(w->prev);
		}
		else
			sair = 1;
	}
	free(w);
}
