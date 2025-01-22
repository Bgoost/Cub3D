# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crmanzan <crmanzan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 14:55:40 by crmanzan          #+#    #+#              #
#    Updated: 2024/05/09 17:42:58 by crmanzan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -I

OBJ_DIR = obj/
SRC_DIR	= src/
INC		= inc/
HEADERS = $(INC)libft.h $(INC)get_next_line.h
COMPILED_FILES := 4

LGREEN			= \033[1;92m
GREEN			= \033[32m
YELLOW			= \033[33m
LYELLOW			= \033[1;93m
BLUE			= \033[34m
RED 			= \033[31m
LRED			= \033[1;91m
RESET			= \033[0m

FT_IS		=	$(SRC_DIR)ft_is/ft_isalnum.c \
					$(SRC_DIR)ft_is/ft_isalpha.c \
					$(SRC_DIR)ft_is/ft_isascii.c \
					$(SRC_DIR)ft_is/ft_isdigit.c \
					$(SRC_DIR)ft_is/ft_isprint.c 

FT_MEM		=	$(SRC_DIR)ft_mem/ft_bzero.c \
					$(SRC_DIR)ft_mem/ft_calloc.c \
					$(SRC_DIR)ft_mem/ft_realloc.c \
					$(SRC_DIR)ft_mem/ft_memchr.c \
					$(SRC_DIR)ft_mem/ft_memcmp.c \
					$(SRC_DIR)ft_mem/ft_memcpy.c \
					$(SRC_DIR)ft_mem/ft_memmove.c \
					$(SRC_DIR)ft_mem/ft_memset.c 

FT_PUT		=	$(SRC_DIR)ft_put/ft_putchar_fd.c \
					$(SRC_DIR)ft_put/ft_putendl_fd.c \
					$(SRC_DIR)ft_put/ft_putnbr_fd.c \
					$(SRC_DIR)ft_put/ft_putstr_fd.c 

FT_TO		=	$(SRC_DIR)ft_to/ft_atoi.c \
					$(SRC_DIR)ft_to/ft_itoa.c \
					$(SRC_DIR)ft_to/ft_tolower.c \
					$(SRC_DIR)ft_to/ft_toupper.c

FT_STR		=	$(SRC_DIR)ft_str/ft_split.c \
					$(SRC_DIR)ft_str/ft_strchr.c \
					$(SRC_DIR)ft_str/ft_strdup.c \
					$(SRC_DIR)ft_str/ft_striteri.c \
					$(SRC_DIR)ft_str/ft_strjoin.c \
					$(SRC_DIR)ft_str/ft_strlcat.c \
					$(SRC_DIR)ft_str/ft_strlcpy.c \
					$(SRC_DIR)ft_str/ft_strcpy.c \
					$(SRC_DIR)ft_str/ft_strlen.c \
					$(SRC_DIR)ft_str/ft_strmapi.c \
					$(SRC_DIR)ft_str/ft_strncmp.c \
					$(SRC_DIR)ft_str/ft_strnstr.c \
					$(SRC_DIR)ft_str/ft_strrchr.c \
					$(SRC_DIR)ft_str/ft_strtrim.c \
					$(SRC_DIR)ft_str/ft_substr.c

GNL_DIR			=	$(SRC_DIR)get_next_line/get_next_line.c \
					$(SRC_DIR)get_next_line/get_next_line_utils.c 

SRC 			= $(FT_IS) $(FT_MEM) $(FT_PUT) $(FT_TO) $(FT_TO) $(FT_STR) $(FT_PRINTF) $(GNL_DIR)
TOTAL_FILES		:= $(words $(SRC))

OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))
DEP = $(SRC:.c=.d)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(LGREEN)[$(COMPILED_FILES)/$(TOTAL_FILES)] All library done!!✅$(RESET)"

						
$(OBJ_DIR)%.o : $(SRC_DIR)%.c Makefile $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES)+1))))
	$(eval PERCENT := $(shell echo $$(($(COMPILED_FILES)*100/$(TOTAL_FILES)))))
	@COLOR=$$( \
		if [ $(PERCENT) -lt 25 ]; then echo "$(RED)"; \
		elif [ $(PERCENT) -lt 50 ]; then echo "$(YELLOW)"; \
		elif [ $(PERCENT) -lt 75 ]; then echo "$(BLUE)"; \
		else echo "$(GREEN)"; \
		fi); \
	echo "$${COLOR}Compiling...[$(COMPILED_FILES)/$(TOTAL_FILES)] ($(PERCENT)%)$(RESET) $< ✅ "

clean:
	@rm -rf $(OBJ_DIR) $(DEP)
	@echo "$(GREEN)All libft cleaned 💩🗑$(RESET)"

fclean: clean
	@rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re

-include $(DEP)