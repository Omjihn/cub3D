# Define your source files and target executable
SRC_DIR := ./src
SRC_FILES :=	main.c \
				parse_map.c \
				parse_map_utils.c \
				pathfinding.c \
				hooks.c \
				display.c \
				ft_free.c \
				ft_init.c \
				ft_raycasting_1.c \
				ft_raycasting_2.c


OBJ_DIR := ./obj
EXECUTABLE := cub3D

# Generate a list of object files with paths
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g

# Additional dependencies
#LFT := ./ft_printf/libftprintf.a
#LIB := -L./ft_printf -lftprintf
LMLX = ./minilibx-linux/libmlx.a
LFT := ./libft/libft.a
LIB := -L./libft -lft -L ./minilibx-linux/ -lmlx -lXext -lX11 -lm -lbsd -L ./libft -lft

RM := rm -f

all: $(OBJ_DIR) $(LFT) $(LMLX) $(EXECUTABLE)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

${LMLX}:
				@make -s -C ./minilibx-linux/ all

$(LFT):
#	@make -s -C ./ft_printf/ all
	@make -s -C ./libft/ all

$(EXECUTABLE): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ $(LIB) -lreadline -o $@
	@echo "\033[32m✅ Done! Executable $(EXECUTABLE) is ready.\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
#	@make -s -C ./ft_printf/ clean
	@make -s -C ./libft/ clean
	@echo "\033[32m✅ Done! Object files removed.\033[0m"

fclean: clean
	@$(RM) $(EXECUTABLE)
#	@make -s -C ./ft_printf/ fclean
	@make -s -C ./libft/ fclean
	@echo "\033[32m✅ Done! Executable $(EXECUTABLE) removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re
