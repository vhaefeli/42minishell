# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 16:28:53 by vhaefeli          #+#    #+#              #
#    Updated: 2022/11/16 10:09:36 by vhaefeli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS 			= -g -Wall -Wextra -Werror #-fsanitize=address -fno-omit-frame-pointer
LDFLAGS			= -lreadline
TARGET 			= minishell
SRCS_DIR 		= ./src
OBJS_DIR 		= ./obj
LIBFT_DIR		= ./libft
INCLUDES_DIRS	= $(LIBFT_DIR) ./includes
INCLUDES		= $(addprefix -I,$(INCLUDES_DIRS))
#INCLUDES_READLINE = -I /opt/homebrew/Cellar/readline/8.2.1/include
#LINK_READLINE 	= -lreadline -L /opt/homebrew/Cellar/readline/8.2.1/lib
INCLUDES_READLINE = -I $(HOME)/.brew/Cellar/readline/8.2.1/include
LINK_READLINE 	= -lreadline -L $(HOME)/.brew/Cellar/readline/8.2.1/lib
LIBS			= $(LIBFT_DIR)/libft.a
_SRCS 			= 	env_analyze.c\
					ft_del.c\
					ft_fill_data1.c\
					ft_fill_data2.c\
					ft_in_out_files1.c\
					ft_in_out_files2.c\
					ft_in_out_files3.c\
					ft_pipe_split.c\
					ft_splitcmd1.c\
					ft_splitcmd2.c\
					quotes_utiles.c\
					list_cmds.c\
					listmanip.c\
					pipe_children_process.c\
					pipe_utils.c\
					minishell.c \
					signal.c \
					builtins/shlvl.c\
					builtins/cmd_pwd.c\
					builtins/cmd_cd.c\
					builtins/env_utils.c\
					builtins/cmd_echo.c\
					builtins/cmd_env.c\
					builtins/env.c\
					builtins/get_env.c\
					builtins/print_env.c\
					builtins/cmd_unset.c\
					builtins/cmd_exit.c\
					builtins/dollar_data.c\
					builtins/cmd_export.c




OBJS 			= $(patsubst %.c, $(OBJS_DIR)/%.o, $(_SRCS))
SRCS 			= $(patsubst %, $(SRCS_DIR)/%, $(_SRCS))

.PHONY : all clean fclean re bonus test

all: $(TARGET)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)


fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(TARGET)

re: fclean all

$(OBJS_DIR):
	@mkdir -p $(dir $(OBJS))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) -o $@ $^ $(INCLUDES)  $(INCLUDES_READLINE)

$(TARGET): $(LIBFT_DIR)/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCLUDES) $(LIBS) $(LINK_READLINE)  $(INCLUDES_READLINE)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -sC $(LIBFT_DIR)

bonus: $(TARGET)



