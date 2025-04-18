NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -O3 -march=native #-fsanitize=address
MLX_FLAGS = -L ./includes/mlx/ -lmlx -lXext -lX11 -lm

#	decomment this to compile on mac
# LDL_FLAGS =  -L/opt/X11/lib -lX11
# CFLAGS += -I/opt/X11/include

PARSING = srcs/parsing/parsing.c \
		srcs/parsing/gnl.c \
		srcs/parsing/check.c \
		srcs/parsing/gnlv2.c \
		srcs/parsing/split.c \
		srcs/parsing/mapping.c \
		srcs/parsing/textures.c \
		srcs/parsing/FC_colors.c \

EXECUTION =  srcs/main.c \
		srcs/execution/tlib.c \
		srcs/execution/cub3D.c \
		srcs/execution/utils.c \
		srcs/execution/garbage.c \
		srcs/execution/processing.c \

RENDERER = srcs/renderer/map.c \
		srcs/renderer/dda.c \
		srcs/renderer/move.c \
		srcs/renderer/hook.c \
		srcs/renderer/raycasting.c \
		srcs/renderer/scaledTextures.c \

SRCS = $(PARSING) $(RENDERER) $(EXECUTION)

HIDDEN = .hidden
OBJS = $(SRCS:%.c=$(HIDDEN)/%.o) 

$(HIDDEN)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $< 

all: $(NAME)
        
$(NAME): $(OBJS)
	@$(MAKE) -C ./includes/mlx
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LDL_FLAGS)
	@echo "\033[1m		______     __  __     ______     _____    \n\
		       /\  ___\   /\ \/\ \   /\  == \   /\  __-.  \n\
		       \ \ \____  \ \ \_\ \  \ \  __<   \ \ \/\ \ \n\
			\ \_____\  \ \_____\  \ \_____\  \ \____- \n\
			 \/_____/   \/_____/   \/_____/   \/____/ \n\n\033[0m"


clean:
	@$(MAKE) clean -C ./includes/mlx
	@rm -rf $(OBJS)
	@rm -rf $(HIDDEN)
	@rm -rf .vscode
	@echo "c'est clean"

fclean: clean
	@rm -rf $(NAME)
	@echo "c'est fclean"

re: fclean
	@$(MAKE) all

.PHONY: all, clean, fclean, re
