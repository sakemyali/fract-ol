# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mosakura <mosakura@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/08 04:49:05 by mosakura          #+#    #+#              #
#    Updated: 2025/12/08 04:49:15 by mosakura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_PATH = minilibx-linux

SRCS		= burning_ship.c \
			  draw.c \
			  init.c \
			  julia.c \
			  main.c \
			  mandelbrot.c \
			  mouse_and_keys.c \
			  utils.c \
			  utils2.c \
			  utils3.c

OBJS		= $(SRCS:.c=.o)

MLX = $(MLX_PATH)/libmlx.a

NAME = fractol

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $^ -o $@ -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz

$(MLX):
	make -C $(MLX_PATH)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -ff $(NAME)

re: fclean all

.PHONY: all clean fclean re
