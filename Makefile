# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/09 20:49:06 by sutku             #+#    #+#              #
#    Updated: 2023/06/03 22:23:37 by sutku            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

PHL_SRC		=	main.c philo_utils.c help_functions.c philos.c philo_utils_2.c \
				argument_control.c cleaning.c
PHL_OBJ		=	$(PHL_SRC:.c=.o)

CC		= 	cc
RM		=   rm -f
CFLAGS	=	-pthread -Wall -Werror -Wextra # -fsanitize=thread -g 

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
	
re: fclean all

.PHONY: all clean fclean re