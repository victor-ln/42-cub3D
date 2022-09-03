# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:38:33 by adrianofaus       #+#    #+#              #
#    Updated: 2022/09/02 20:53:35 by afaustin         ###   ########.fr        #
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
CFLAGS			=	-Wall -Wextra -Werror
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

MENU			=	menu.c

LOAD_FILE		=	load_file.c \
					save_params.c \
					save_utils.c \

LOAD_GAME		=	load_game.c \
					load_menu.c \
					load_textures.c \
					load_utils.c \

CORE			=	end_game.c \
					main.c \
					start_game.c \

EVENTS			=	keyboard.c \
					mouse.c \
					player.c \
					window.c \

FPS				=	fps.c \

RAY_CASTING		=	rays_utils.c \
					rays.c \

RENDER			=	draw_3d_sprites.c \
					draw_3d_walls.c \
					draw_env.c \
					draw_radar.c \
					draw_small_radar.c \
					draw_utils.c \

VALIDATE		=	doors.c \
					enemy.c \
					map_validate.c \
					resize_map.c \
					sprites_selection.c \
					sprites_validate.c \
					validate_routines.c \

SORTING			=	quick_sort.c \

# FILES
SOURCES			=	$(addprefix core/load_file/, $(LOAD_FILE)) \
					$(addprefix core/load_game/, $(LOAD_GAME)) \
					$(addprefix menu/, $(MENU)) \
					$(addprefix core/, $(CORE)) \
					$(addprefix events/, $(EVENTS)) \
					$(addprefix fps/, $(FPS)) \
					$(addprefix ray_casting/, $(RAY_CASTING)) \
					$(addprefix render/, $(RENDER)) \
					$(addprefix validate/, $(VALIDATE)) \
					$(addprefix sorting/, $(SORTING)) \

OBJS			=	$(SOURCES:%.c=%.o)

# ###################################################################### TARGETS
all:				$(NAME)

$(NAME):			$(addprefix $(PATH_OBJ),$(OBJS))
					$(MAKE) -C ./libft
					$(MAKE) -C ./mlx_linux
					$(CC) libft/libft.a $(addprefix $(PATH_OBJ),$(OBJS)) $(MLXFLAGS) -o $(NAME)

$(PATH_OBJ)%.o:		$(PATH_SRC)%.c $(PATH_INC)$(HEADERS)
					@mkdir -p obj
					@mkdir -p obj/core/load_file
					@mkdir -p obj/core/load_game
					@mkdir -p obj/core
					@mkdir -p obj/events
					@mkdir -p obj/fps
					@mkdir -p obj/ray_casting
					@mkdir -p obj/render
					@mkdir -p obj/validate
					@mkdir -p obj/sorting
					@mkdir -p obj/menu
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