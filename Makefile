NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
MLX_FLAGS = -L ./includes/mlx/ -lmlx -lXext -lX11 -lm

CFLAGS += -Wno-unused-command-line-argument

PARSING = srcs/parsing/parsing.c \
		srcs/parsing/gnl.c \
		srcs/parsing/ltoa.c \
		srcs/parsing/gnlv2.c \
		srcs/parsing/split.c \
		srcs/parsing/mapping.c \
		srcs/parsing/textures.c \
		srcs/parsing/FC_colors.c \

EXEC =  srcs/main.c \
	srcs/execution/tlib.c \
	srcs/execution/utils.c \
	srcs/execution/event.c \
	srcs/execution/cub3D.c \
	srcs/execution/processing.c \

RAYCASTING = 

SRCS = $(EXEC) $(PARSING)

OBJS = $(SRCS:.c=.o) 

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $< 

all: $(NAME)
        
$(NAME): $(OBJS)
	make -C ./includes/mlx
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)
	@echo "\033[1m		______     __  __     ______     _____    \n\
		       /\  ___\   /\ \/\ \   /\  == \   /\  __-.  \n\
		       \ \ \____  \ \ \_\ \  \ \  __<   \ \ \/\ \ \n\
			\ \_____\  \ \_____\  \ \_____\  \ \____- \n\
			 \/_____/   \/_____/   \/_____/   \/____/ \n\n\033[0m"


clean:
	@make clean -C ./includes/mlx
	@rm -rf $(OBJS)
	@echo "c'est clean"

fclean: clean
	@rm -rf $(NAME)
	@echo "c'est fclean"

re: fclean all

.PHONY: all, clean, fclean, re
