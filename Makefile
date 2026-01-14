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
		$(SRC_DIR)/lexer/utils_lexer.c \
		$(SRC_DIR)/checker/checker_syntax.c \
		$(SRC_DIR)/checker/helpers.c \
		$(SRC_DIR)/checker/utils.c \
		$(SRC_DIR)/parser/helpers.c \
		$(SRC_DIR)/parser/init.c \
		$(SRC_DIR)/parser/parse_command.c \
		$(SRC_DIR)/parser/parse_generic.c \
		$(SRC_DIR)/parser/parse_logical.c \
		$(SRC_DIR)/parser/parse_pipeline.c \
		$(SRC_DIR)/parser/parse_sequence.c \
		$(SRC_DIR)/parser/clear.c \
		$(SRC_DIR)/parser/debug.c \
		$(SRC_DIR)/builtins/get_builtin.c \
		$(SRC_DIR)/builtins/pwd.c \
		$(SRC_DIR)/builtins/cd.c \
		$(SRC_DIR)/builtins/echo.c \
		$(SRC_DIR)/builtins/unset.c \
		$(SRC_DIR)/builtins/env.c \
		$(SRC_DIR)/builtins/export.c \
		$(SRC_DIR)/builtins/exit.c \
		$(SRC_DIR)/utils/env.c \
		$(SRC_DIR)/expander/expander.c \
		$(SRC_DIR)/expander/wildcards.c \
		$(SRC_DIR)/exec/exec_cmd.c \
		$(SRC_DIR)/exec/helpers.c \
		$(SRC_DIR)/exec/convert.c \
		$(SRC_DIR)/exec/exec_pipe.c \
		$(SRC_DIR)/exec/pipe_utils.c \
		$(SRC_DIR)/exec/exec_ast.c \
		$(SRC_DIR)/exec/redirects.c \
		$(SRC_DIR)/exec/heredoc.c \
		$(SRC_DIR)/expander/table_driven_expander.c \
		$(SRC_DIR)/expander/automato_expander.c \
		$(SRC_DIR)/expander/utils_expander.c \
		$(SRC_DIR)/expander/wildcard_utils.c \
		$(SRC_DIR)/expander/subshell_expander.c \
		$(SRC_DIR)/expander/helpers_expander.c \
		$(SRC_DIR)/signals/signals.c \
		$(SRC_DIR)/signals/sigint.c \
		$(SRC_DIR)/signals/sigquit.c \
		$(SRC_DIR)/autocomplete/init.c \
		$(SRC_DIR)/autocomplete/match.c \
		$(SRC_DIR)/autocomplete/completion.c \
		$(SRC_DIR)/autocomplete/insert.c \
		$(SRC_DIR)/autocomplete/scan.c \

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

readline.supp:
	@echo '{' > $@
	@echo '   ignore_libreadline_memory_errors' >> $@
	@echo '   Memcheck:Leak' >> $@
	@echo '   ...' >> $@
	@echo '   obj:*/libreadline.so.*' >> $@
	@echo '}' >> $@

val: readline.supp all
	@/bin/valgrind -q --suppressions=readline.supp \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				./${NAME}

.PHONY: all clean fclean re bonus
