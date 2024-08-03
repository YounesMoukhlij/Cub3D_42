# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 13:35:58 by youmoukh          #+#    #+#              #
#    Updated: 2024/08/03 18:50:49 by youmoukh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = cub3d.c \
	  parsing/get_line.c \
	  parsing/parse.c \
	  parsing/load_map.c \
	  utils/utils_1.c \
	  utils/utils_2.c \
	  utils/utils_3.c \
	  utils/utils_4.c \
	  utils/utils_5.c \
	  utils/ft_split.c \
	  utils/error_msg.c \
	  utils/movment.c \
	  utils/tools.c \
	  draw/draw.c \
	  raycast/ray_cast.c \
	  raycast/ray_cast_utils.c \
	  utils/garbage_collector.c \
	  utils/garbage_collector_utils.c \
	  

OBJ = $(SRC:.c=.o)
HEADER = cub.h
NAME = cub3D
CFLAGS =  -Ofast -g -fsanitize=address -Wall -Wextra -Werror

all : $(NAME)

%.o : %.c $(HEADER)
	@cc  ${CFLAGS} -c $< -o $@
	@echo "\033[1;30m compiling ...\033[0m"

$(NAME) : $(OBJ)
	@cc ${CFLAGS} $(OBJ) -o $@ MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
	@echo "\033[1;31m \n Linking ... \033[0m"
	@echo "\033[1;32m \n READY To PLAY  \033[1;31m^_*\033[0m"

clean :
	@rm -rf $(OBJ)
	@echo "\033[1;33m Object files has been deleted Successfully. \033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[1;33m Executable has been deleted Successfully. \033[0m"

re : fclean all

.PHONY : clean
