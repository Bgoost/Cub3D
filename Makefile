# Program name
NAME			= cub3D

# Compiler and CFlags
CC			= cc
#CFLAGS		= -g -O3 -Wall -Werror -Wextra -I$(MLX_DIR)/include
CFLAGS		= -O3 -Wall -Werror -Wextra -g -fsanitize=address -I$(MLX_DIR)/include
RM			= rm -f

# Directories
OBJ_DIR		    = obj/
INC_DIR			= inc/
SRC_DIR			= src/
BUILD_DIR		= MLX42/build

# Libraries and Includes
MLX_DIR			= MLX42
LIBFT_DIR		= libft
MLX				= $(MLX_DIR)/build/libmlx42.a
MLX_MAKE		= $(MLX) -ldl -lglfw -pthread -lm
INCLUDES        = $(INC_DIR)/cub3d.h
LIBFT			= $(LIBFT_DIR)/libft.a

# Colors for output
GREEN			= \033[32m
LGREEN			= \033[1;92m
ORANGE			= \033[33m
RED				= \033[1;91m
RESET			= \033[0m

# Source Files
SRC			=	main.c main_checker.c parser.c parser_utils.c parse_textures.c parse_map.c \
				test.c test_360.c init_raycasting.c pixels.c mini_map.c parse_map_utils.c parse_textures_utils.c \
				free_utils.c
SRCS		= $(addprefix $(SRC_DIR), $(SRC))

# Object Files
OBJ 		= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build Rules
all:		mlx makelibft $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_MAKE) $(LIBFT)
			@echo "\n$(LGREEN)Executable $(NAME) created ✔$(RESET)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile $(INCLUDES)
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -MMD -c $< -o $@
			@echo "$(GREEN)Compiled $< ✔$(RESET)"

makelibft:
			make -C libft

mlx:
			@echo "$(ORANGE)Configuring MLX42 with CMake...$(RESET)"
			cmake MLX42 -B MLX42/build 
			cmake --build MLX42/build -j4
			@echo "$(ORANGE)Compiling MLX42...$(RESET)"
			@make --no-print-directory -C $(MLX_DIR)/build

clean:
			@$(RM) -rf $(OBJ_DIR)
			@$(RM) -rf $(BUILD_DIR)
			@make clean -C $(LIBFT_DIR)
			@echo "$(RED)Deleted object files ✔$(RESET)"
			@echo "$(RED)Deleted build directory ✔$(RESET)"

fclean: clean
			@$(RM) $(NAME)
			@$(RM) $(LIBFT)
			@echo "$(RED)Executable $(NAME) deleted ✔$(RESET)"

re: fclean all

# Phony Targets
.PHONY: all clean fclean re mlx
