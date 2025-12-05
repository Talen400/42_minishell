# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0mc

# Configuration
NAME := minishell
CC := cc
CFLAGS	:= -g -Wextra -Wall -Werror

# Directories
SRC_DIR := ./srcs
SRC_BONUS_DIR := ./srcs_bonus
OBJ_DIR := ./objs
OBJ_BONUS_DIR := ./objs_bonus
LIBFT_DIR := ./libft

# Libraries
LIBFT := $(LIBFT_DIR)/libft.a
LIBS := $(LIBFT) -lreadline

# Mandatory sources
SRCS := $(SRC_DIR)/main.c \
		$(SRC_DIR)/data.c \
		$(SRC_DIR)/input.c \
		$(SRC_DIR)/lexer/automato.c \
		$(SRC_DIR)/lexer/table_driven.c \
		$(SRC_DIR)/lexer/token.c \
		$(SRC_DIR)/lexer/debug.c \
		$(SRC_DIR)/lexer/token_type.c \
		$(SRC_DIR)/parser/helpers.c \
		$(SRC_DIR)/parser/init.c \
		$(SRC_DIR)/parser/parse_command.c \
		$(SRC_DIR)/parser/parse_generic.c \
		$(SRC_DIR)/parser/parse_logical.c \
		$(SRC_DIR)/parser/parse_pipeline.c \
		$(SRC_DIR)/parser/parse_sequence.c \
		$(SRC_DIR)/parser/clear.c \
		$(SRC_DIR)/parser/merge.c \
		$(SRC_DIR)/parser/debug.c \
		$(SRC_DIR)/builtins/get_builtin.c \
		$(SRC_DIR)/builtins/pwd.c \
		$(SRC_DIR)/expander/expander.c \
		$(SRC_DIR)/expander/wildcards.c \

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRCS_BONUS := $(SRC_BONUS_DIR)/main_bonus.c \

OBJS_BONUS := $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

MANDATORY_MARK := .mandatory
BONUS_MARK := .bonus

all: $(NAME)

# Mandatory part

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Created objects directory$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(CYAN)Compiled: $(notdir $<)$(RESET)"

$(NAME): $(MANDATORY_MARK)

$(MANDATORY_MARK): $(LIBFT) $(OBJS)
	@rm -f $(BONUS_MARK)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@touch $(MANDATORY_MARK)
	@echo "$(GREEN)$(NAME) build successfully!$(RESET)"

# Bonus part
$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)
	@echo "$(BLUE)Created bonus objects directory$(RESET)"

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(MAGENTA)Compiled bonus: $(notdir $<)$(RESET)"

bonus: $(BONUS_MARK)

$(BONUS_MARK): $(LIBFT) $(OBJS_BONUS)
	@rm -f $(MANDATORY_MARK)
	@echo "$(YELLOW)Linking $(NAME) (bonus)...$(RESET)"
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME)
	@touch $(BONUS_MARK)
	@echo "$(GREEN)$(NAME) (bonus) built successfully!$(RESET)"

# Libraries
$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft built successfully!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_BONUS_DIR)
	@rm -f $(MANDATORY_MARK)
	@rm -f $(BONUS_MARK)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(RED)Clean completed!$(RESET)"

fclean: clean
	@echo "$(RED)Full clean...$(RESET)"
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(RED)Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
