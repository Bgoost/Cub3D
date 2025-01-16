# Program name
NAME			= cub3D

# Compiler and CFlags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I$(MLX_DIR)/include
# CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address -I$(MLX_DIR)/include
RM			= rm -f

# Directories
OBJ_DIR		    = obj/
INC_DIR			= inc/
SRC_DIR			= src/

# Libraries and Includes
MLX_DIR			= MLX42
MLX				= $(MLX_DIR)/libmlx42.a
MLX_MAKE		= $(MLX) -ldl -lglfw -pthread -lm
INCLUDES        = $(INC_DIR)/cub3d.h

# Colors for output
GREEN			= \033[32m
LGREEN			= \033[1;92m
ORANGE			= \033[33m
RED				= \033[1;91m
RESET			= \033[0m

# Source Files
SRC			= main.c
SRCS		= $(addprefix $(SRC_DIR), $(SRC))

# Object Files
OBJ 		= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build Rules
all:			mlx $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_MAKE)
			@echo "\n$(LGREEN)Executable $(NAME) created ✔$(RESET)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES)
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -MMD -c $< -o $@
			@echo "$(GREEN)Compiled $< ✔$(RESET)"

mlx:
			@echo "$(ORANGE)Configuring MLX42 with CMake...$(RESET)"
			@cd $(MLX_DIR) && cmake .
			@echo "$(ORANGE)Compiling MLX42...$(RESET)"
			@make --no-print-directory -C $(MLX_DIR)

clean:
			@$(RM) -r $(BUILD_DIR)
			@make clean -C $(MLX_DIR)
			@echo "$(RED)Deleted object files ✔$(RESET)"

fclean: clean
			@$(RM) $(NAME)
			@make clean -C $(MLX_DIR)
			@echo "$(RED)Executable $(NAME) deleted ✔$(RESET)"

re: fclean all

# Phony Targets
.PHONY: all clean fclean re mlx
