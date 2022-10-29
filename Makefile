## Name of Project

NAME =			minishell

## Color for compiling (pink)

COLOR =			\0033[1;35m

## List of Directories

INC_DIR =		include
OBJ_DIR = 		obj
SRC_DIR	= 		src

# Add dirs here

LIBS =			-L/usr/include
#LIBS =			-L/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include/readline

BUILTIN_DIR =	builtin
CMD_DIR =		cmd
ENV_DIR	=		env
LST_DIR =		lst
MAIN_DIR =		main
PARSING_DIR	=	parsing
UTILS_DIR =		utils

## Compiling Utilities

#FAST =			-Ofast

SANITIZE =		-fsanitize=address

DEBUG =			#-g3 #${SANITIZE}

FLAGS =			-Wall -Wextra -Werror $(FAST) $(DEBUG) -D_REENTRANT

INC =			-Iinclude

INCLUDE =		\
				$(INC_DIR)/builtin.h \
				$(INC_DIR)/define.h \
				$(INC_DIR)/env.h \
				$(INC_DIR)/minishell.h \
				$(INC_DIR)/parsing.h \
				$(INC_DIR)/utils.h \
				$(INC_DIR)/cmd.h \
				$(INC_DIR)/main.h \
				$(INC_DIR)/struct.h

CC =			clang $(FLAGS) $(INC)

#HOW TO LIST .c 
#	ls -l | awk '{print $9}' | grep -E ".c$"| sed "s/\.c/ \\\/g" | sed '$s/\\$//g'

BUILTIN_FT =	\
				ms_cd \
				ms_echo \
				ms_env \
				ms_exit \
				ms_export \
				ms_export_without_args \
				ms_pwd \
				ms_unset

CMD_FT =		\
				ms_exec_cmd \
				ms_fork_with_pipe \
				ms_fork_without_pipe \
				ms_pipe \
				ms_redirect_action \
				ms_red_double_left \
				ms_read_input2 \
				ms_redirection \
				ms_set_args \
				ms_set_path \
				ms_set_s_exec

ENV_FT =		\
				ms_cp_env \
				ms_create_lst_env

MAIN_FT =		\
				ms_free \
				ms_free_ms \
				ms_prompt \
				ms_set_default \
				ms_signals

PARSING_FT =	\
				ms_parsing_error \
				ms_parsing_utils \
				ms_pars_pipe_and_redirector \
				ms_pipe_lst_utils \
				ms_rafter_error \
				ms_redirector_tab \
				ms_set_lst_cmd \
				ms_split_cmd \
				ms_substitute_dollar \
				ms_substitute_dollar_utils \
				ms_substitute_quote

SRC_FT =		\
				main

UTILS_FT =		\
				ms_atol \
				ms_atoll \
				ms_bzero \
				ms_calloc \
				ms_close_fd \
				ms_free_split \
				ms_isalnum \
				ms_isalpha \
				ms_isdigit \
				ms_isspace \
				ms_itoa \
				ms_len_split \
				ms_lltoa \
				ms_ltoa \
				ms_memcpy \
				ms_memset \
				ms_print_split \
				ms_split \
				ms_split_first_limiter \
				ms_strcat_w_len \
				ms_strchr \
				ms_strcmp \
				ms_strcpy \
				ms_strdup \
				ms_str_is_alnum_undscr \
				ms_str_is_nbr \
				ms_strj_fr_1 \
				ms_strjoin \
				ms_strlen \
				ms_strncmp \
				ms_strncpy \
				ms_substr \
				ms_t_list2 \
				ms_t_list2_cmd \
				ms_t_list \
				ms_t_list_cmd \
				ms_t_list_env 

## List of Utilities
SRC =			$(SRC_FT:%=$(SRC_DIR)/%.c) \
				$(BUILTIN_FT:%=$(SRC_DIR)/$(BUILTIN_DIR)/%.c) \
				$(CMD_FT:%=$(SRC_DIR)/$(CMD_DIR)/%.c) \
				$(ENV_FT:%=$(SRC_DIR)/$(ENV_DIR)/%.c) \
				$(MAIN_FT:%=$(SRC_DIR)/$(MAIN_DIR)/%.c) \
				$(PARSING_FT:%=$(SRC_DIR)/$(PARSING_DIR)/%.c) \
				$(UTILS_FT:%=$(SRC_DIR)/$(UTILS_DIR)/%.c)

OBJ =			$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ_DIRS =		$(OBJ_DIR) \
				$(BUILTIN_DIR:%=$(OBJ_DIR)/%) \
				$(CMD_DIR:%=$(OBJ_DIR)/%) \
				$(ENV_DIR:%=$(OBJ_DIR)/%) \
				$(MAIN_DIR:%=$(OBJ_DIR)/%) \
				$(PARSING_DIR:%=$(OBJ_DIR)/%) \
				$(UTILS_DIR:%=$(OBJ_DIR)/%)

## Rules of Makefile

all: $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;30m[All OK]\0033[1;37m"

$(OBJ_DIRS):
	@mkdir -p $@
	@echo "$(COLOR)$@ \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"
	@echo "$(COLOR)Creating :\t\0033[0;32m$@\0033[1;37m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c $< -o $@
	@echo "$(COLOR)$(@:$(OBJ_DIR)/%=%) \033[100D\033[40C\0033[1;32m[Compiled]\0033[1;37m"

$(NAME): $(OBJ_DIRS) $(SRC) $(INCLUDE)
	@$(MAKE) -j -s $(OBJ)
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"
	@$(CC) $(OBJ) -lreadline -o $@
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;31m[Removed]\0033[1;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;31m[Removed]\0033[1;37m"

re:	fclean all

define print_aligned_coffee
    @t=$(NAME); \
	l=$${#t};\
	i=$$((8 - l / 2));\
	echo "             \0033[1;32m\033[3C\033[$${i}CAnd Your program \"$(NAME)\" "
endef

coffee: all clean
	@echo ""
	@echo "                                {"
	@echo "                             {   }"
	@echo "                              }\0033[1;34m_\0033[1;37m{ \0033[1;34m__\0033[1;37m{"
	@echo "                           \0033[1;34m.-\0033[1;37m{   }   }\0033[1;34m-."
	@echo "                          \0033[1;34m(   \0033[1;37m}     {   \0033[1;34m)"
	@echo "                          \0033[1;34m| -.._____..- |"
	@echo "                          |             ;--."
	@echo "                          |            (__  \ "
	@echo "                          |             | )  )"
	@echo "                          |   \0033[1;96mCOFFEE \0033[1;34m   |/  / "
	@echo "                          |             /  / "
	@echo "                          |            (  / "
	@echo "                          \             | "
	@echo "                            -.._____..- "
	@echo ""
	@echo ""
	@echo "\0033[1;32m\033[3C                    Take Your Coffee"
	$(call print_aligned_coffee)

.PHONY: all clean fclean re coffee
