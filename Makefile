# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/09 20:49:06 by sutku             #+#    #+#              #
#    Updated: 2023/05/27 15:59:07 by sutku            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

PHL_SRC		=	main.c philo_utils.c help_functions.c philos.c philo_utils_2.c \
				argument_control.c cleaning.c
PHL_OBJ		=	$(PHL_SRC:.c=.o)


# BONUS_SRC	=	pipex_bonus/child_process_b.c pipex_bonus/here_doc_b.c \
# 				pipex_bonus/main_bonus.c pipex_bonus/pipex_utils_b.c
# BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

CC		= 	cc
RM		=   rm -f
CFLAGS	=	-pthread  -Wall -Werror -Wextra #-pthread -fsanitize=thread -g #-fsanitize=address -g3 

NAME	=	philo

DEF_COLOR = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;32m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(NAME)

$(NAME): $(PHL_OBJ)
	$(CC) $(CFLAGS) $(PHL_OBJ) -o $(NAME)
	echo "$(CYAN)Philosophers compiled successfully$(DEF_COLOR)"

clean:
	$(RM) $(PHL_OBJ)
	# $(RM) $(BONUS_OBJ)
	echo "$(MAGENTA)Object-Files are cleaned$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	echo "$(MAGENTA)Programs / Libraries are cleaned!$(DEF_COLOR)"

# bonus: $(PIP_OBJ) $(BONUS_OBJ) $(GNL_OBJ) $(PRINTF_LIB) $(LIBFT_LIB)
# 	$(CC) $(CFLAGS) $(PIP_OBJ) $(BONUS_OBJ) $(GNL_OBJ) $(PRINTF_LIB) $(LIBFT_LIB) -o $(NAME)
# 	echo "$(CYAN)Pipex_Bonus compiled successfully$(DEF_COLOR)"
	
re: fclean all

.PHONY: all clean fclean re bonus