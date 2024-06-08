NAME = fdf
DEBUG_NAME = debug.out

SRC_DIR = src
OBJ_DIR = obj
PATH_MANDATORY = mandatory
PATH_BONUS = bonus
INC_DIR = includes
DEP_DIR = deps

LIBFT_DIR = $(DEP_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = $(DEP_DIR)/MLX42
MLX = $(MLX_DIR)/build/libmlx42.a

SRC_NAMES_SHARED =
SRC_NAMES_MANDATORY =	main.c				\
						read_map.c			\
						fdf.c				\
						utils/err.c			\
						utils/arr_len.c		\
						utils/arr_free.c
SRC_NAMES_BONUS =

CC = cc
CC_EXT_SRCS = $(LIBFT) $(MLX) -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
FLAGS = -I$(INC_DIR) # -Wall -Wextra -Werror
DEBUG_FLAGS = -I$(INC_DIR) -g -fsanitize=address,undefined,integer

################################################################################

OBJS_SHARED = $(SRC_NAMES_SHARED:%.c=$(OBJ_DIR)/$(PATH_MANDATORY)/%.o)
OBJS_MANDATORY = $(SRC_NAMES_MANDATORY:%.c=$(OBJ_DIR)/$(PATH_MANDATORY)/%.o)
OBJS_BONUS = $(SRC_NAMES_BONUS:%.c=$(OBJ_DIR)/$(PATH_BONUS)/%.o)

OBJS_SHARED_DEBUG = $(SRC_NAMES_SHARED:%.c=$(OBJ_DIR)/debug/$(PATH_MANDATORY)/%.o)
OBJS_MANDATORY_DEBUG = $(SRC_NAMES_MANDATORY:%.c=$(OBJ_DIR)/debug/$(PATH_MANDATORY)/%.o)
OBJS_BONUS_DEBUG = $(SRC_NAMES_BONUS:%.c=$(OBJ_DIR)/debug/$(PATH_BONUS)/%.o)

.PHONY: all bonus \
debug debug_bonus \
clean .clean fclean re

################################################################################

all: $(NAME)

$(OBJ_DIR)/debug/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREY)$(NAME) $(DEFAULT)| $(GREEN)$< $(PURPLE)$(DEBUG_FLAGS) $(RED)> $(GREY)$@$(DEFAULT)"
	@$(CC) $(DEBUG_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREY)$(NAME) $(DEFAULT)| $(GREEN)$< $(PURPLE)$(FLAGS) $(RED)> $(GREY)$@$(DEFAULT)"
	@$(CC) $(FLAGS) -c $< -o $@

################################################################################

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

$(MLX):
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@make -C $(MLX_DIR)/build -j4

################################################################################

$(NAME): $(LIBFT) $(MLX) $(OBJS_SHARED) $(OBJS_MANDATORY)
	@$(CC) $(FLAGS) $(CC_EXT_SRCS) $(OBJS_SHARED) $(OBJS_MANDATORY) -o $(NAME)
	@echo "$(GREY)$(NAME) $(DEFAULT)| $(GREEN)Mandatory done$(DEFAULT)"

.bonus: $(LIBFT) $(MLX) $(OBJS_SHARED) $(OBJS_BONUS)
	@$(CC) $(FLAGS) $(CC_EXT_SRCS) $(OBJS_SHARED) $(OBJS_BONUS) -o $(NAME)
	@touch .bonus
	@echo "$(GREY)$(NAME) $(DEFAULT)| $(GREEN)Bonus done$(DEFAULT)"

bonus: .bonus

################################################################################

$(DEBUG_NAME): $(LIBFT) $(MLX) $(OBJS_SHARED_DEBUG) $(OBJS_MANDATORY_DEBUG)
	@$(CC) $(DEBUG_FLAGS) $(CC_EXT_SRCS) $(OBJS_SHARED_DEBUG) $(OBJS_MANDATORY_DEBUG) -o $(DEBUG_NAME)
	@echo "$(GREY)$(NAME) $(DEBUG_NAME) $(DEFAULT)| $(GREEN)Mandatory done$(DEFAULT)"

debug: $(DEBUG_NAME)

.debug_bonus: $(LIBFT) $(MLX) $(OBJS_SHARED_DEBUG) $(OBJS_BONUS_DEBUG)
	@$(CC) $(DEBUG_FLAGS) $(CC_EXT_SRCS) $(OBJS_SHARED_DEBUG) $(OBJS_BONUS_DEBUG) -o $(DEBUG_NAME)
	@touch .bonus
	@echo "$(GREY)$(NAME) $(DEBUG_NAME) $(DEFAULT)| $(GREEN)Bonus done$(DEFAULT)"

debug_bonus: .debug_bonus

################################################################################

.clean:
	@echo "$(GREY)$(NAME) $(DEFAULT)| $(RED)Removing $(DEFAULT)$(OBJ_DIR), .bonus, and .debug_bonus"
	@rm -rf $(OBJ_DIR) .bonus .debug_bonus

clean: .clean
	@make -C $(LIBFT_DIR) clean
	
fclean: .clean
	@make -C $(LIBFT_DIR) fclean
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
