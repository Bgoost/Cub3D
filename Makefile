# Program name
NAME			= cub3D
NAME_BONUS		= cub3D_bonus

# Compiler and CFlags
CC			= cc
CFLAGS		= -g -O3 -Wall -Werror -Wextra -I$(MLX_DIR)/include
#CFLAGS		= -O3 -Wall -Werror -Wextra -fsanitize=address -LSAN_OPTIONS=verbosity=1:log_threads=1 -I$(MLX_DIR)/include
RM			= rm -f

# Directories
OBJ_DIR		    = obj/
INC_DIR			= inc/
SRC_DIR			= src/
SRC_DIR_BONUS	= src_bonus/
BUILD_DIR		= MLX42/build

# Libraries and Includes
MLX_DIR			= MLX42
LIBFT_DIR		= libft
MLX				= $(MLX_DIR)/build/libmlx42.a
MLX_MAKE		= $(MLX) -ldl -lglfw -pthread -lm
INCLUDES        = $(INC_DIR)/cub3d.h
INCLUDES_BONUS  = $(INC_DIR)/cub3d_bonus.h
LIBFT			= $(LIBFT_DIR)/libft.a

# Colors for output
GREEN			= \033[32m
LGREEN			= \033[1;92m
ORANGE			= \033[33m
RED				= \033[1;91m
RESET			= \033[0m

# Source Files
SRC			=	main.c main_checker.c parser.c parser_utils.c parse_textures.c parse_map.c \
				raycasting.c init_raycasting.c pixels.c parse_map_utils.c parse_textures_utils.c \
				free_utils.c init_raycasting2.c player_movements.c ray_utils.c ray_printing.c \
				vertical_hits.c horizontal_hits.c

SRC_BONUS	=	main_bonus.c main_checker_bonus.c parser_bonus.c parser_utils_bonus.c parse_textures_bonus.c parse_map_bonus.c \
				raycasting_bonus.c init_raycasting_bonus.c pixels_bonus.c minimap_bonus.c minimap_rays_bonus.c parse_map_utils_bonus.c parse_textures_utils_bonus.c \
				free_utils_bonus.c init_raycasting2_bonus.c animation_bonus.c player_movements_bonus.c ray_utils_bonus.c ray_printing_bonus.c \
				vertical_hits_bonus.c horizontal_hits_bonus.c init_animation_bonus.c

SRCS		= $(addprefix $(SRC_DIR), $(SRC))
SRCS_BONUS	= $(addprefix $(SRC_DIR_BONUS), $(SRC_BONUS))

# Object Files
OBJ 		= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
OBJ_BONUS	= $(patsubst $(SRC_DIR_BONUS)%.c,$(OBJ_DIR)%.o,$(SRCS_BONUS))

# Build Rules
all:		mlx makelibft $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_MAKE) $(LIBFT)
			@echo "\n$(LGREEN)Executable $(NAME) created ✔$(RESET)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile $(INCLUDES)
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -MMD -c $< -o $@
			@echo "$(GREEN)Compiled $< ✔$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR_BONUS)%.c Makefile $(INCLUDES_BONUS)
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -MMD -c $< -o $@
			@echo "$(GREEN)Compiled $< ✔$(RESET)"

makelibft:
			make -C libft

bonus: mlx makelibft .bonus

.bonus: 		$(OBJ_BONUS)
			$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(MLX_MAKE) $(LIBFT)
			@echo "\n$(LGREEN)Executable $(NAME) created ✔$(RESET)\n"
			@touch .bonus

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
			@$(RM) $(NAME_BONUS)
			@$(RM) $(LIBFT)
			@$(RM) .bonus
			@echo "$(RED)Executable $(NAME) deleted ✔$(RESET)"

re: fclean all

# Phony Targets
.PHONY: all clean fclean re mlx bonus
