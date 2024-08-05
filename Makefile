# project name
NAME = minishell

# library name
LIBFT_NAME = libft.a
LIBFT_DIR = libft/

# include
INCLUDE_DIR = include/
INCLUDE = -I $(INCLUDE_DIR)
LIBFT_INCLUDE = -I $(LIBFT_DIR)$(INCLUDE_DIR)

SRC_DIR = src/
OBJ_DIR = .obj/

ERROR_DIR = error/

# compiler
CC = cc
LDFRAGS = -lreadline -fsanitize=address,undefined
CFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined -g
# LDFRAGS = -lreadline
# CFLAGS = -Wall -Wextra -Werror
# debug option
# CFLAGS = -g
RM = rm -rf
NORM = norminette

BUILTIN_DIR = 	builtin/
BUILTIN_SRC = 	builtin.c\
				builtin_exit.c\
				builtin_cd.c\
				builtin_echo.c\
				builtin_pwd.c\
				builtin_export.c\
				builtin_env.c\
				builtin_unset.c

CHILD_DIR =		child/
CHILD_SRC =		child.c\
				childset.c

ENV_DIR =	env/
ENV_SRC =	env_list.c\
			env_list_utils.c\
			env_init.c\
			env_utils.c

EXPANSION_DIR =	expansion/
EXPANSION_SRC =	expansion.c\
				expansion_utils.c

PARSER_DIR =	parser/
PARSER_SRC =	parser.c\
				ats_list.c

PIPE_REDIRECT_DIR =	pipeRedirect/
PIPE_REDIRECT_SRC =	pipe.c\
					redirect.c\
					heredoc.c

SINGNAL_DIR =	signal/
SINGNAL_SRC =	signal.c\
				signal_child.c

TOKENISER_DIR =	tokenizer/
TOKENISER_SRC =	tokenizer.c\
				token_list.c\
				tokenizer_utils.c

UTILS_DIR =	utils/
UTILS_SRC =	utils.c\
			error.c\
			syntax.c\
			free.c

SRC_FILES = main.c

SRC_FILES += $(addprefix $(BUILTIN_DIR), $(BUILTIN_SRC))
SRC_FILES += $(addprefix $(CHILD_DIR), $(CHILD_SRC))
SRC_FILES += $(addprefix $(ENV_DIR), $(ENV_SRC))
SRC_FILES += $(addprefix $(EXPANSION_DIR), $(EXPANSION_SRC))
SRC_FILES += $(addprefix $(PARSER_DIR), $(PARSER_SRC))
SRC_FILES += $(addprefix $(PIPE_REDIRECT_DIR), $(PIPE_REDIRECT_SRC))
SRC_FILES += $(addprefix $(SINGNAL_DIR), $(SINGNAL_SRC))
SRC_FILES += $(addprefix $(TOKENISER_DIR), $(TOKENISER_SRC))
SRC_FILES += $(addprefix $(UTILS_DIR), $(UTILS_SRC))

OJB_FILES = $(SRC_FILES:%.c=%.o)

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(OJB_FILES))

# color **********************************************
Y 			= "\033[33m"
R 			= "\033[31m"
G 			= "\033[32m"
B 			= "\033[34m"
X 			= "\033[0m"
UP 			= "\033[A"
CUT 		= "\033[K"
# *****************************************************

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(Y) "$(NAME) src files successfully compiled\n" $(X)
	@echo $(B) "--> Into $(LIBFT_DIR)" $(X)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo $(B) "<-- Out of $(LIBFT_DIR)\n" $(X)
	@echo $(B) "$(NAME) creating" $(X)
	@printf $(UP)$(CUT)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFRAGS) $(LIBFT_DIR)$(LIBFT_NAME) -o $(NAME)
	@echo $(G) "!! $(NAME) created !!\n" $(X)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)$(BUILTIN_DIR)
	@mkdir $(OBJ_DIR)$(CHILD_DIR)
	@mkdir $(OBJ_DIR)$(ENV_DIR)
	@mkdir $(OBJ_DIR)$(EXPANSION_DIR)
	@mkdir $(OBJ_DIR)$(PARSER_DIR)
	@mkdir $(OBJ_DIR)$(PIPE_REDIRECT_DIR)
	@mkdir $(OBJ_DIR)$(SINGNAL_DIR)
	@mkdir $(OBJ_DIR)$(TOKENISER_DIR)
	@mkdir $(OBJ_DIR)$(UTILS_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo $(Y) "Compiling $<" $(X)
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT_INCLUDE) -c $< -o $@
	@printf $(UP)$(CUT)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(ERROR_DIR)
	@echo $(R) "$(NAME) cleaned\n" $(X)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@$(RM) $(ERROR_DIR)
	@echo $(R) "$(NAME) fcleaned\n" $(X)

re: fclean all

test: all
	@echo $(Y) "<<< $(NAME) test >>>" $(X)
	@./tester/my_tester/tester.sh

diff: all
	@echo $(Y) "<<< $(NAME) diff >>>" $(X)
	@./tester/my_tester/diff.sh

all_test: all test diff

norm:
	@echo $(R) "<<< $(NAME) error count >>>" $(X)
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error | grep -v Error! | wc -l
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error || true
	@$(MAKE) -C $(LIBFT_DIR) norm

.PHONY: all clean fclean re norm
