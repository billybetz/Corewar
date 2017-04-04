# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akalmyko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/15 16:16:00 by akalmyko          #+#    #+#              #
#    Updated: 2017/03/15 19:05:40 by akalmyko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

ASM = assembleur/
VM = vm/
LIBFT = libft/
GRN = \033[1;32m
CLN = \033[m
WHT = \033[1;37m
COMPILED = $(GRN)"compiled"$(CLN)
RECOMPILED = $(GRN)"project recompiled"$(CLN)

all:
	@make -C $(LIBFT)
	@make -C $(ASM)
	@#@echo "vm compiling \c"
	@#@make -C $(VM)
	@#@echo "vm compiled"
	@echo "project $(COMPILED)"

clean:
	@make -C $(LIBFT) clean
	@make -C $(ASM) clean
	@#make -C $(VM) clean

fclean:
	@make -C $(LIBFT) fclean
	@make -C $(ASM) fclean
	@#make -C $(VM) fclean

re: fclean all

