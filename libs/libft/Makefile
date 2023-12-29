# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anayef <anayef@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 13:27:21 by mshehata          #+#    #+#              #
#    Updated: 2023/11/27 20:00:23 by anayef           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Library = libft

CC = gcc

FLAGS = -Wall -Wextra -Werror -c

OUTN = $(Library).a

SRC_PATH	= ./srcs/
OBJ_PATH	= ./build/

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strcpy.c\
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strcat.c\
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strnjoin.c\
			ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c\
			ft_calloc.c ft_strdup.c ft_strndup.c ft_itoa.c get_next_line.c\
			ft_striteri.c ft_strmapi.c ft_putchar_fd.c ft_putendl_fd.c ft_split.c\
			ft_putstr_fd.c ft_strjoin.c ft_strtrim.c ft_substr.c ft_putnbr_fd.c\

VPATH	:= $(SRC_PATH)\

OBJ = $(addprefix $(OBJ_PATH), $(notdir $(SRC:.c=.o)))

NAME = $(OUTN)

$(OBJ_PATH)%.o: %.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CF) -c $< -o $@

$(NAME): $(OBJ)
		ar -rc $(NAME) $^

all: $(NAME)

clean:
	@rm -rf $(OBJ) $(OBJ_PATH)

fclean:	clean
		@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re

.SILENT:	$(NAME)	$(OBJ)
