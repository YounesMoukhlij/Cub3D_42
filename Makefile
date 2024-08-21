# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 13:35:58 by youmoukh          #+#    #+#              #
#    Updated: 2024/08/21 18:34:53 by youmoukh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = mandatory/cub3d.c \
	  mandatory/parsing/get_line.c \
	  mandatory/parsing/parse.c \
	  mandatory/parsing/parse_tools.c \
	  mandatory/parsing/parse_tools_2.c \
	  mandatory/parsing/parse_tools_3.c \
	  mandatory/parsing/parse_tools_4.c \
	  mandatory/parsing/parse_tools_5.c \
	  mandatory/parsing/load_map.c \
	  mandatory/parsing/check_extension.c \
	  mandatory/utils/utils_1.c \
	  mandatory/utils/utils_2.c \
	  mandatory/utils/utils_3.c \
	  mandatory/utils/utils_4.c \
	  mandatory/utils/utils_5.c \
	  mandatory/utils/utils_6.c \
	  mandatory/utils/utils_20.c \
	  mandatory/utils/ft_split.c \
	  mandatory/utils/error_msg.c \
	  mandatory/utils/movment.c \
	  mandatory/utils/tools.c \
	  mandatory/draw/draw.c \
	  mandatory/draw/draw_utils.c \
	  mandatory/raycast/ray_cast.c \
	  mandatory/raycast/ray_cast_utils.c \
	  mandatory/utils/garbage_collector.c \
	  mandatory/utils/garbage_collector_utils.c \

bonus_folder = bonus/

SRC_B = ${bonus_folder}cub3d_bonus.c \
	 ${bonus_folder}parsing/get_line_bonus.c \
	 ${bonus_folder}parsing/parse_bonus.c \
	 ${bonus_folder}parsing/parse_tools_bonus.c \
	 ${bonus_folder}parsing/parse_tools_2_bonus.c \
	 ${bonus_folder}parsing/parse_tools_3_bonus.c \
	 ${bonus_folder}parsing/parse_tools_4_bonus.c \
	 ${bonus_folder}parsing/parse_tools_5_bonus.c \
	 ${bonus_folder}parsing/load_map_bonus.c \
	 ${bonus_folder}parsing/check_extension_bonus.c \
	 ${bonus_folder}utils/utils_1_bonus.c \
	 ${bonus_folder}utils/utils_2_bonus.c \
	 ${bonus_folder}utils/utils_3_bonus.c \
	 ${bonus_folder}utils/utils_4_bonus.c \
	 ${bonus_folder}utils/utils_5_bonus.c \
	 ${bonus_folder}utils/utils_6_bonus.c \
	 ${bonus_folder}utils/utils_7_bonus.c \
	 ${bonus_folder}utils/handle_mouse_bonus.c \
	 ${bonus_folder}utils/ft_split_bonus.c \
	 ${bonus_folder}utils/error_msg_bonus.c \
	 ${bonus_folder}utils/movment_bonus.c \
	 ${bonus_folder}draw/draw_bonus.c \
	 ${bonus_folder}draw/draw_utils_bonus.c \
	 ${bonus_folder}draw/draw_utils_1_bonus.c \
	 ${bonus_folder}raycast/ray_cast_bonus.c \
	 ${bonus_folder}raycast/ray_cast_utils_bonus.c \
	 ${bonus_folder}utils/garbage_collector_bonus.c \
	 ${bonus_folder}utils/garbage_collector_utils_bonus.c \
 
OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
HEADER = mandatory/cub.h
NAME = cub3D
NAME_BONUS = cub3D_bonus
CFLAGS =  -Ofast -Wall -Wextra -Werror

all : $(NAME)

bonus : ${NAME_BONUS}

$(NAME) : $(OBJ)
	@cc ${CFLAGS} $(OBJ) -o $@ MLX42/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
	@echo "\033[1;31m \n Linking ... \033[0m"
	@echo "\033[1;32m \n READY To PLAY  \033[1;31m^_*\033[0m"

%_bonus.o : %_bonus.c ${bonus_folder}cub_bonus.h
	@cc  ${CFLAGS} -c $< -o $@
	@echo "\033[1;30m compiling ...\033[0m"

$(NAME_BONUS) : $(OBJ_B)
	@cc ${CFLAGS} $(OBJ_B) -o $@ MLX42/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
	@echo "\033[1;31m \n Linking ... \033[0m"
	@echo "\033[1;32m \n READY To PLAY  \033[1;31m^_*\033[0m"

%.o : %.c ${HEADER}
	@cc  ${CFLAGS} -c $< -o $@
	@echo "\033[1;30m compiling ...\033[0m"

clean :
	@rm -rf $(OBJ_B) $(OBJ)
	@echo "\033[1;33m Object files has been deleted Successfully. \033[0m"

fclean : clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@echo "\033[1;33m Executable has been deleted Successfully. \033[0m"

re : fclean all

.PHONY : clean
