/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatamou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:02:54 by mmatamou          #+#    #+#             */
/*   Updated: 2017/03/05 00:56:04 by mmatamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"

void				ft_show_error_and_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

static void			ft_show_usage(void)
{
	ft_printf("usage: ./asm <file name with .s extension>\n");
	exit(EXIT_FAILURE);
}

static void			ft_check_extension(char *str)
{
	size_t			len;

	len = ft_strlen(str);
	if (len < 3)
		ft_show_usage();
	if (str[len - 2] == '.')
	{
		if (str[len - 1] != 's')
			ft_show_usage();
	}
	else
		ft_show_usage();
}

static void			ft_check_file(char *str)
{
	int				fd;
	ssize_t			size;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		ft_show_error_and_exit("err: Failed to open file\n");
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (size < 15)
		ft_show_error_and_exit("err: Bad file\n");
	close(fd);
}

int					main(int argc, char **argv)
{
	if (argc != 2)
		ft_show_usage();
	ft_check_extension(argv[1]);
	ft_check_file(argv[1]);
	assembler(argv[1]);
	return (EXIT_SUCCESS);
}
