NO_COLOR = '\033[0m'
YELLOW = '\033[0;33m'
GREEN = '\033[0;32m'

NAME = so_long

BONUS_NAME = so_long_bonus

MLX_DIR = minilibx-linux/
LFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -no-pie

SRCS = main.c checks.c leftover.c utils.c txr_and_movement.c
FOLDER_MANDATORY = mandatory/
PATH_MANDATORY = $(addprefix $(FOLDER_MANDATORY), $(SRCS))
OBJS = ${PATH_MANDATORY:.c=.o}
PATH_HEADER = $(addprefix $(FOLDER_MANDATORY), so_long.h)

SRCS_BONUS = main_bonus.c checks_bonus.c leftover_bonus.c utils_bonus.c txr_and_movement_bonus.c
FOLDER_BONUS = bonus/
PATH_BONUS = $(addprefix $(FOLDER_BONUS), $(SRCS_BONUS))
BONUS_OBJS = ${PATH_BONUS:.c=.o}
PATH_HEADER_BONUS = $(addprefix $(FOLDER_BONUS), so_long_bonus.h)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

LIBFT_PATH = Libft/
LIBFT = Libft/libft.a

all: ${NAME}

${NAME}: ${OBJS} ${PATH_HEADER}
	@echo $(YELLOW) "compiling libft..."$(NO_COLOR)
	@make -C ${LIBFT_PATH} 1>/dev/null
	@echo $(GREEN)"compiled libft ✓"$(NO_COLOR)
	@echo $(YELLOW) "compiling MiniLibX..."$(NO_COLOR)
	@make -C $(MLX_DIR) 1>/dev/null
	@echo $(GREEN)"compiled MiniLibX ✓"$(NO_COLOR)
	@echo $(YELLOW) "compiling so_long..."$(NO_COLOR)
	@$(CC) ${CFLAGS} ${OBJS} ${LIBFT} $(LFLAGS) -o ${NAME}
	@echo $(GREEN)"compiled so_long ✓"$(NO_COLOR)

${BONUS_NAME}: ${BONUS_OBJS} ${PATH_HEADER_BONUS}
	@echo $(YELLOW) "compiling libft..."$(NO_COLOR)
	@make -C ${LIBFT_PATH} 1>/dev/null
	@echo $(GREEN)"compiled libft ✓"$(NO_COLOR)
	@echo $(YELLOW) "compiling MiniLibX..."$(NO_COLOR)
	@make -C $(MLX_DIR) 1>/dev/null
	@echo $(GREEN)"compiled MiniLibX ✓"$(NO_COLOR)
	@echo $(YELLOW) "compiling so_long_bonus..."$(NO_COLOR)
	@$(CC) ${CFLAGS} ${BONUS_OBJS} ${LIBFT} $(LFLAGS) -o ${BONUS_NAME}
	@echo $(GREEN)"compiled so_long_bonus ✓"$(NO_COLOR)

bonus: ${BONUS_NAME}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C ${LIBFT_PATH} 1>/dev/null
	@make clean -C $(MLX_DIR) 1>/dev/null
	@echo $(YELLOW) "removing .o files..."$(NO_COLOR)
	@rm -f ${OBJS}
	@rm -f ${BONUS_OBJS}
	@echo $(GREEN)"removed .o files ✓"$(NO_COLOR)

fclean: clean
	@make fclean -C ${LIBFT_PATH} 1>/dev/null
	@echo $(YELLOW) "removing NAME file..."$(NO_COLOR)
	@rm -f ${NAME}
	@rm -f ${BONUS_NAME}
	@echo $(GREEN)"removed NAME file ✓"$(NO_COLOR)

re: fclean all

rebonus: fclean bonus

test: re 
	gdb ${NAME}

testbonus: rebonus 
	gdb --args ${BONUS_NAME} maps/prova.ber

.PHONY: all clean fclean re rebonus test testbonus