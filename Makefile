# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 18:31:23 by scarlucc          #+#    #+#              #
#    Updated: 2024/06/24 11:24:09 by scarlucc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NO_COLOR = '\033[0m'
YELLOW = '\033[0;33m'
GREEN = '\033[0;32m'

NAME = so_long

BONUS_NAME = 

SRCS = 

BONUS = 

OBJS = ${SRCS:.c=.o}

BONUS_OBJS = ${BONUS: .c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = Libft/
LIBFT = Libft/libft.a

all: ${NAME}

${NAME}: ${OBJS} so_long.h
	@echo $(YELLOW) "compiling libft..."$(NO_COLOR)
	@make -C ${LIBFT_PATH} 1>/dev/null
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}
	@echo $(GREEN)"compiled libft ✓"$(NO_COLOR)
	@echo $(YELLOW) "compiling so_long..."$(NO_COLOR)
	@echo $(GREEN)"compiled so_long ✓"$(NO_COLOR)

${BONUS_NAME}:

bonus: ${BONUS_NAME}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C ${LIBFT_PATH} 1>/dev/null
	@echo $(YELLOW) "removing .o files..."$(NO_COLOR)
	@rm -f ${OBJS} ${BONUS_OBJS}
	@echo $(GREEN)"removed .o files ✓"$(NO_COLOR)

fclean: clean
	@echo $(YELLOW) "removing NAME and BONUS_NAME file..."$(NO_COLOR)
	@make fclean -C ${LIBFT_PATH} 1>/dev/null
	@rm -f ${NAME} ${BONUS_NAME}
	@echo $(GREEN)"removed NAME and BONUS_NAME file ✓"$(NO_COLOR)

re: fclean all

.PHONY: all clean fclean