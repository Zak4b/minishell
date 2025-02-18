NAME = minishell

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[0;33m
RESET = \033[0m

LIBFT = libft/libft.a
INC = -I/opt/homebrew/opt/readline/include -I.
LIB = -L/opt/homebrew/opt/readline/lib -lreadline -L./libft/ -lft

FLAGS = -Wall -Wextra -Werror -g

SOURCES = ./builtins/builtin_utils.c ./builtins/cd.c ./builtins/echo.c ./builtins/env.c ./builtins/exit.c ./builtins/export.c ./builtins/pwd.c ./builtins/unset.c ./env/env_conversion.c ./env/getenv_value.c ./env/path.c ./env/set_env.c ./env/unset_env.c ./errors.c ./execution/exec_builder.c ./execution/execute.c ./execution/execute_pipeline.c ./execution/free_exec.c ./expand.c ./heredoc.c ./main.c ./prompt.c ./signal.c ./syntaxe.c ./tokens/clear_token_list.c ./tokens/tokenize.c ./tokens/token_utils.c ./utils.c 

SRCDIR = srcs
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)Compiling $(NAME)...$(RESET)"
	@cc $(FLAGS) $(OBJS) -o $(NAME) $(INC) $(LIB)
	@echo "$(GREEN)Compilation finished successfully!$(RESET)"

$(LIBFT):
	@echo "$(GREEN)Building Libft...$(RESET)"
	@make -s -C libft libft.a

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@cc $(FLAGS) $(INC) -c $< -o $@

norm:
	@echo "Lancement de la norminette..."
	@norminette | grep -i "error" > norm_errors.log || true
	@if [ -s norm_errors.log ]; then \
		err_count=$$(wc -l < norm_errors.log); \
		echo "$(RED)$$err_count erreur(s) détectée(s) :$(RESET)"; \
		cat norm_errors.log; \
	else \
		echo "$(GREEN)OK - Aucun problème détecté par la norminette.$(RESET)"; \
	fi
	@rm norm_errors.log

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@make -s -C libft clean

fclean: clean
	@echo "$(RED)Cleaning all...$(RESET)"
	@rm -f $(NAME)
	@make -s -C libft fclean

re: fclean $(NAME)

.PHONY: all clean fclean re
