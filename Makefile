# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:38:33 by adrianofaus       #+#    #+#              #
#    Updated: 2022/08/11 18:57:40 by afaustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# #################################################################### VARIABLES
# BINARY NAME
NAME			=	cub3D

# BASH COMMANDS
MKDIR			=	mkdir -p
RM				=	rm -rf

# HEADERS
HEADERS			=	cub3D.h

# INCLUDES
INCLUDES		=	-I $(PATH_INC)

# DEBUG
DEBUG			=	-g3 -fsanitize=address

# COMPILATION
CFLAGS			=	-Wall -Wextra -Werror $(DEBUG)
MLXFLAGS		=	-Lmlx_linux -lmlx_Linux -Imlx_linux -L/usr/lib -lXext -lX11 -lm -lz -L libft/ -lft
CC				=	gcc $(CFLAGS) $(INCLUDES)
VALGRIND		=	valgrind \
					--leak-check=full \
					--show-leak-kinds=all \
					--track-origins=yes

#PATHS
PATH_OBJ		=	obj/
PATH_SRC		=	srcs/
PATH_INC		=	includes/
PATH_TEST		=	test/

# FILES
SOURCES			=	main.c \
					draw_game.c \
					draw_radar.c \
					draw_utils.c \
					draw_3d_walls.c \
					save_params.c \
					validate_routines.c \
					map_validate.c \
					exit_routines.c \
					resize_map.c \
					save_utils.c \
					debug_map.c \
					load_file.c \
					load_game.c \
					load_utils.c \
					events.c \
					rays.c \
					rays_utils.c \
					window.c \
					draw_small_radar.c \
					doors.c \

OBJS			=	$(SOURCES:%.c=%.o)

# ###################################################################### TARGETS
all:				$(NAME)

$(NAME):			$(addprefix $(PATH_OBJ),$(OBJS))
					$(MAKE) -C ./libft
					$(MAKE) -C ./mlx_linux
					$(CC) libft/libft.a $(addprefix $(PATH_OBJ),$(OBJS)) $(MLXFLAGS) -o $(NAME)

$(PATH_OBJ)%.o:		$(PATH_SRC)%.c $(PATH_INC)$(HEADERS)
					@mkdir -p obj
					$(CC) $(MLXFLAGS) -c $< -o $@

run:				all
					./$(NAME)

valgrind:			all
					$(VALGRIND) ./$(NAME)

norm:
					norminette srcs/ libft/ includes/

test:
					gcc -I includes/ -I mlx_linux/ test/img_biggerthan_window.c mlx_linux/libmlx.a -Lmlx_linux -lmlx_Linux -Imlx_linux -L/usr/lib -lXext -lX11 -lm -lz

clean:				
					$(MAKE) -C ./libft clean
					$(MAKE) -C ./mlx_linux clean
					$(RM) $(addprefix $(PATH_OBJ), $(OBJS)) rmdir obj

fclean:				clean
					$(MAKE) -C ./libft fclean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re run valgrind