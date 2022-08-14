# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 16:28:53 by vhaefeli          #+#    #+#              #
#    Updated: 2022/08/14 13:03:47 by vhaefeli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS 			= -Wall -Wextra -Werror -g #-fsanitize=address -fno-omit-frame-pointer
TARGET 			= minishell
SRCS_DIR 		= ./src
OBJS_DIR 		= ./obj
LIBFT_DIR		= ./libft
INCLUDES_DIRS	= $(LIBFT_DIR) ./includes
INCLUDES		= $(addprefix -I,$(INCLUDES_DIRS))
LIBS			= $(LIBFT_DIR)/libft.a
_SRCS 			= 	cmd_cd.c\
					cmd_echo.c\
					cmd_env.c\
					cmd_exit.c\
					cmd_pwd.c\
					cmd_export.c\
					cmd_uset.c\
					env_analyze.c\
					ft_del.c\
					ft_error_exit.c\
					ft_fill_data1.c\
					ft_fill_data2.c\
					ft_in_out_files.c\
					ft_pipe_split.c\
					ft_splitcmd1.c\
					ft_splitcmd2.c\
					list_cmds.c\
					listmanip.c\
					pipe_children_process.c
					pipe_utils.c\
					minishell.c


OBJS 			= $(patsubst %.c, $(OBJS_DIR)/%.o, $(_SRCS))
SRCS 			= $(patsubst %, $(SRCS_DIR)/%, $(_SRCS))

.PHONY : all clean fclean re bonus test

all: $(TARGET)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	rm -d $(OBJS_DIR)


fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(TARGET)

re: fclean all

$(OBJS_DIR):
	@mkdir -p $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) -o $@ $^ $(INCLUDES)

$(TARGET): $(LIBFT_DIR)/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCLUDES) $(LIBS)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -sC $(LIBFT_DIR)

bonus: $(TARGET)



