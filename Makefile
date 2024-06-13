NAME = fdf
DEBUG_NAME = debug.out

SRC_DIR = src/mandatory
OBJ_DIR = obj
INC_DIR = includes
DEP_DIR = deps
LIB_DIR = libs

LIBFT_DIR = $(DEP_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = $(DEP_DIR)/MLX42
MLX = $(MLX_DIR)/build/libmlx42.a

SRC_NAMES =	main.c				\
			read_map.c			\
			fdf.c				\
			utils/err.c			\
			utils/arr_len.c		\
			utils/arr_free.c

CC = gcc
CC_EXT_SRCS = -L$(LIB_DIR) $(LIBFT) -lft -lmlx42 -lm -lglfw
FLAGS = -fPIE -I$(INC_DIR) # -Wall -Wextra -Werror
DEBUG_FLAGS = -I$(INC_DIR) -g -fsanitize=address,undefined,integer

################################################################################

OBJS = $(SRC_NAMES:%.c=$(OBJ_DIR)/mandatory/%.o)
OBJS_DEBUG = $(SRC_NAMES:%.c=$(OBJ_DIR)/debug/%.o)

.PHONY: all debug \
clean .clean fclean re

################################################################################

all: $(NAME)

$(OBJ_DIR)/debug/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREY)$(NAME) $(DEFAULT)| $(GREEN)$< $(PURPLE)$(DEBUG_FLAGS) $(RED)> $(GREY)$@$(DEFAULT)"
	@$(CC) $(DEBUG_FLAGS) -c $< -o $@

$(OBJ_DIR)/mandatory/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREY)$(NAME) $(DEFAULT)| $(GREEN)$< $(PURPLE)$(FLAGS) $(RED)> $(GREY)$@$(DEFAULT)"
	@$(CC) $(FLAGS) -c $< -o $@

################################################################################

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR) bonus
	@cp $(LIBFT) $(LIB_DIR)

$(MLX):
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@make --no-print-directory -C $(MLX_DIR)/build -j4
	@cp $(MLX) $(LIB_DIR)

################################################################################

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(CC_EXT_SRCS) -o $(NAME)
	@echo "$(GREY)$(NAME) $(DEFAULT)| $(GREEN)Mandatory done$(DEFAULT)"

################################################################################

$(DEBUG_NAME): $(LIBFT) $(MLX) $(OBJS_DEBUG)
	@$(CC) $(DEBUG_FLAGS) $(CC_EXT_SRCS) $(OBJS_DEBUG) -o $(DEBUG_NAME)
	@echo "$(GREY)$(NAME) $(DEBUG_NAME) $(DEFAULT)| $(GREEN)Mandatory done$(DEFAULT)"

debug: $(DEBUG_NAME)

################################################################################

.clean:
	@echo "$(GREY)$(NAME) $(DEFAULT)| $(RED)Removing $(DEFAULT)$(OBJ_DIR)"
	@rm -rf $(OBJ_DIR) .bonus .debug_bonus

clean: .clean
	@make --no-print-directory -C $(LIBFT_DIR) clean
	
fclean: .clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "$(GREY)$(NAME) $(DEFAULT)| $(RED)Removing $(DEFAULT)$(NAME) and $(DEBUG_NAME)"
	@rm -f $(NAME) $(DEBUG_NAME)

re: fclean all

################################################################################

GREEN = \033[38;5;84m
RED = \033[38;5;9m
BLUE = \033[38;5;45m
#PURPLE = \033[38;5;63m
PINK = \033[38;5;207m
PURPLE = \033[38;5;165m
BLACK = \033[38;5;0m
BG_WHITE = \033[48;5;15m
BG_GREEN = \033[48;5;84m
BG_RED = \033[48;5;9m
BG_PURPLE = \033[48;5;54m
GREY = \033[38;5;8m
BOLD = \033[1m
DEFAULT = \033[0m
CHECKMARK = \xE2\x9C\x93
