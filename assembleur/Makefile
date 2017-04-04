# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbetz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/14 19:46:58 by bbetz             #+#    #+#              #
#    Updated: 2017/03/22 18:26:08 by bbetz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= asm
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g
EXTRA_FLAGS		= 
OPTI			= -I

LS      		= ls -1
GREP			= grep
MKDIR			= mkdir -p
RM				= rm -rf

SRC_PATH		= sources
LIB_PATH		= ../libft
INC_PATH		= include
INC_LIB_PATH	= include \
							$(LIB_PATH)/include
DOBJ			= objets

SRC_FILES		:= $(shell $(LS) $(SRC_PATH) | $(GREP) .c$)
OBJ_FILES		:= $(SRC_FILES:.c=.o)
LIBFT			:= libft.a

SRC_FILES		:= $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ_FILES		:= $(addprefix $(DOBJ)/, $(OBJ_FILES))
FINCLIB			:= $(addprefix $(OPTI) , $(INC_LIB_PATH))
LIBFT			:= $(addprefix $(LIB_PATH)/, $(LIBFT))

GRN = \033[1;32m
CLN = \033[m
WHT = \033[1;37m
CLEANED = $(WHT)"cleaned"$(CLN)
FCLEANED = $(WHT)"fcleaned"$(CLN)
COMPILED = $(GRN)"compiled"$(CLN)

all: libft $(OBJ_FILES) $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	@echo "assembleur compiling ... \c"
	@$(CC) $(CFLAGS) $(EXTRA_FLAGS) $(OBJ_FILES) $(LIBFT) -lncurses -o $@
	@echo "$(COMPILED)"

$(DOBJ)/%.o: $(SRC_PATH)/%.c $(INC_PATH)
	@$(MKDIR) $(DOBJ)
	@$(CC) $(CFLAGS) -c $< $(FINCLIB) -o $@

libft:
	 @if [ ! -e $(LIBFT) ]; then \
     	make -C $(LIB_PATH); \
     fi

clean:
	@make -C $(LIB_PATH) clean
	@$(RM) $(DOBJ)
	@echo "assembleur $(CLEANED)"

fclean: clean
	@make -C $(LIB_PATH) fclean
	@$(RM) $(NAME)
	@echo "assembleur $(FCLEANED)"

re: fclean all

.PHONY: all libft clean fclean re
