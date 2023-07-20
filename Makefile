# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 15:58:03 by ndahib            #+#    #+#              #
#    Updated: 2023/07/21 00:11:10 by ndahib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COMMANDS#
CC		= cc 
FLAGS	= -g -fsanitize=address #-Wall -Wextra -Werror
RM		= rm -rf
#REDLINE	= $(shell brew  --prefix readline)

#VARIBLES#
NAME		= minishell
BUILD_DIR	= build
SRC_DIR		= src
SRCS		= $(addprefix $(SRC_DIR)/, $(FILES))
OBJS		= $(addprefix $(BUILD_DIR)/, $(FILES:%.c=%.o))
FILES		= analyser/analyser.c executer/exec_utils.c executer/execution2.c executer/execution_utils.c executer/get_next_line.c executer/redirections.c expander/expansion.c expander/expansion2.c lexer/lexer.c main/env.c main/env2.c main/free_utils.c main/test.c main/utils.c parser/parse_cmd.c parser/parse_files.c parser/parse_utils.c executer/built_ins_1.c executer/built_ins_2.c
LIBFT		= libft.a
LIBFTDIR	= libft/
INCLUDE 	= -I include -I $(LIBFTDIR)

all : $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

$(NAME) : $(OBJS)
	$(CC) -lreadline $(FLAGS) $(LIBFTDIR)$(LIBFT) $(INCLUDE) $(OBJS) -o $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/analyser
	mkdir -p $(BUILD_DIR)/executer
	mkdir -p $(BUILD_DIR)/expander
	mkdir -p $(BUILD_DIR)/lexer
	mkdir -p $(BUILD_DIR)/main
	mkdir -p $(BUILD_DIR)/parser
	$(CC) $(INCLUDE) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(BUILD_DIR)
	make -C $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean

re	: fclean all
