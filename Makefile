NO_COLOR = '\033[0m'
YELLOW = '\033[0;33m'
GREEN = '\033[0;32m'

NAME = so_long

BONUS_NAME = so_long_bonus

MLX_DIR = minilibx-linux/
LFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -no-pie

SRCS = main.c checks.c leftover.c utils.c txr_and_movement.c
OBJS = ${SRCS:.c=.o}

BONUS = 
BONUS_OBJS = ${BONUS: .c=.o}

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

LIBFT_PATH = Libft/
LIBFT = Libft/libft.a

all: ${NAME}

${NAME}: ${OBJS} so_long.h
	@echo $(YELLOW) "compiling libft..."$(NO_COLOR)
	@make -C ${LIBFT_PATH} 1>/dev/null
	@echo $(GREEN)"compiled libft ✓"$(NO_COLOR)
	@echo $(YELLOW) "compiling MiniLibX..."$(NO_COLOR)
	@make -C $(MLX_DIR) 1>/dev/null
	@echo $(GREEN)"compiled MiniLibX ✓"$(NO_COLOR)
	@echo $(YELLOW) "compiling so_long..."$(NO_COLOR)
	@$(CC) ${CFLAGS} ${OBJS} ${LIBFT} $(LFLAGS) -o ${NAME}
	@echo $(GREEN)"compiled so_long ✓"$(NO_COLOR)

${BONUS_NAME}:

bonus: ${BONUS_NAME}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C ${LIBFT_PATH} 1>/dev/null
	@make clean -C $(MLX_DIR) 1>/dev/null
	@echo $(YELLOW) "removing .o files..."$(NO_COLOR)
	@rm -f ${OBJS}
	@echo $(GREEN)"removed .o files ✓"$(NO_COLOR)

fclean: clean
	@make fclean -C ${LIBFT_PATH} 1>/dev/null
	@echo $(YELLOW) "removing NAME file..."$(NO_COLOR)
	@rm -f ${NAME}
	@echo $(GREEN)"removed NAME file ✓"$(NO_COLOR)

re: fclean all

test: re 
	gdb ${NAME}

.PHONY: all clean fclean re