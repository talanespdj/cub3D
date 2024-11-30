NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -lm
MLX_FLAGS = -L ./mlx -lm -Ilmlx -lXext -lX11 

CFLAGS += -Wno-unused-command-line-argument

EXEC =  srcs/main.c \
	srcs/execution/gnl.c \
	srcs/execution/tlib.c \
	srcs/execution/split.c \
	srcs/execution/gnlv2.c \
	srcs/execution/utils.c \
	srcs/execution/cub3D.c \
	srcs/execution/processing.c \

PARSING = srcs/parsing/parsing.c \
		srcs/parsing/ltoa.c \
		srcs/parsing/mapping.c \
		srcs/parsing/textures.c \
		srcs/parsing/FC_colors.c \

RAYCASTING = 

SRCS = $(EXEC) $(PARSING)


OBJS = $(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $< 

all: $(NAME)
        
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)
	@echo "\033[1m		______     __  __     ______     _____    \n\
		       /\  ___\   /\ \/\ \   /\  == \   /\  __-.  \n\
		       \ \ \____  \ \ \_\ \  \ \  __<   \ \ \/\ \ \n\
			\ \_____\  \ \_____\  \ \_____\  \ \____- \n\
			 \/_____/   \/_____/   \/_____/   \/____/ \n\n\033[0m"


clean:
	@rm -rf $(OBJS)
	@echo "c'est clean"

fclean: clean
	@rm -rf $(NAME)
	@echo "c'est fclean"

re: fclean all

.PHONY: all, clean, fclean, re
