NAME = minishell
CFLAGS = -Wextra -Wall -Werror
LIBFT = -L./libft -lft

HEADERS = -I./libft -I./include

SRCS_DIR = src
SRCS_SUBDIR = builtins execution pre_handler tools signal
VPATH = $(SRCS_DIR) $(addprefix $(SRCS_DIR)/, $(SRCS_SUBDIR))
SRCS =	main.c interface.c \
		signal.c signal_handler.c \
		ast.c checker.c expander.c lexer.c parser.c token.c \
		envlist.c error.c for_ms.c link_list.c matrix.c restart.c utils.c \
		cd.c echo.c env.c exit.c export.c unset.c \
		execute.c pipe.c exec_tools.c redirection.c path.c \

OBJS_DIR = objs
OBJS = $(SRCS:.c=.o)
TARGETS = $(addprefix $(OBJS_DIR)/, $(OBJS))

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS_DIR) $(TARGETS)
	@$(MAKE) -C ./libft
	@cc $(CFLAGS) $(TARGETS) $(LIBFT) -o $(NAME) -lreadline

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
