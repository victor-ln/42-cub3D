# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coder <coder@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:38:33 by adrianofaus       #+#    #+#              #
#    Updated: 2022/09/09 02:09:34 by coder            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# #################################################################### VARIABLES
# BINARY NAME
NAME			=	cub3D
NAME_BONUS		=	cub3D_bonus

# BASH COMMANDS
MKDIR			=	mkdir -p
RM				=	rm -rf

# INCLUDES
INCLUDES		=	-I $(PATH_INC)
INCLUDES_BONUS	=	-I $(PATH_INC_BONUS)

# DEBUG
DEBUG			=	-g3 #-fsanitize=address

# COMPILATION
CFLAGS			=	-Wall -Wextra -Werror -O3 $(DEBUG)
MLXFLAGS		=	-lmlx -Imlx -L/usr/lib -lXext -lX11 -lm -lz -L libft/ -lft
CC				=	gcc $(CFLAGS)
VALGRIND		=	valgrind \
					--leak-check=full \
					--show-leak-kinds=all \
					--track-origins=yes

#PATHS
PATH_OBJ		=	mandatory/obj/
PATH_OBJ_BONUS	=	bonus/obj/
PATH_SRC		=	mandatory/srcs/
PATH_SRC_BONUS	=	bonus/srcs/
PATH_INC		=	mandatory/includes/
PATH_INC_BONUS	=	bonus/includes/
PATH_TEST		=	test/

MENU_BONUS		=	menu \
					menu_actions \

LOAD_FILE		=	load_file \
					save_params \
					save_utils \

LOAD_GAME		=	load_game \
					load_textures \
					load_utils \

LOAD_GAME_BONUS	=	load_menu \

CORE			=	end_game \
					main \
					start_game \

EVENTS			=	keyboard \
					player \
					window \

EVENTS_BONUS	=	mouse \

FPS_BONUS		=	fps \

RAY_CASTING		=	rays_utils \
					rays \

RAY_CASTING_BONUS	=	ray_content \

RENDER_BONUS	=	draw_3d_sprites \
					draw_radar \
					draw_small_radar \

RENDER			=	draw_3d_walls \
					draw_env \
					pixels \
					draw_utils \

VALIDATE_BONUS	=	doors \
					enemy \
					sprites_selection \
					sprites_validate \

VALIDATE		=	map_validate \
					resize_map \
					validate_routines \

SORTING_BONUS	=	quick_sort \

# FILES
SOURCES			=	$(addprefix core/load_file/, $(addsuffix .c, $(LOAD_FILE))) \
					$(addprefix core/load_game/, $(addsuffix .c, $(LOAD_GAME))) \
					$(addprefix core/, $(addsuffix .c, $(CORE))) \
					$(addprefix events/, $(addsuffix .c, $(EVENTS))) \
					$(addprefix ray_casting/, $(addsuffix .c, $(RAY_CASTING))) \
					$(addprefix render/, $(addsuffix .c, $(RENDER))) \
					$(addprefix validate/, $(addsuffix .c, $(VALIDATE))) \

SOURCES_BONUS	=	$(addprefix menu/, $(addsuffix _bonus.c, $(MENU_BONUS))) \
					$(addprefix fps/, $(addsuffix _bonus.c, $(FPS_BONUS))) \
					$(addprefix sorting/, $(addsuffix _bonus.c, $(SORTING_BONUS))) \
					$(addprefix core/load_game/, $(addsuffix _bonus.c, $(LOAD_GAME_BONUS))) \
					$(addprefix core/, $(addsuffix _bonus.c, $(CORE_BONUS))) \
					$(addprefix events/, $(addsuffix _bonus.c, $(EVENTS_BONUS))) \
					$(addprefix ray_casting/, $(addsuffix _bonus.c, $(RAY_CASTING_BONUS))) \
					$(addprefix render/, $(addsuffix _bonus.c, $(RENDER_BONUS))) \
					$(addprefix validate/, $(addsuffix _bonus.c, $(VALIDATE_BONUS))) \
					$(addsuffix _bonus.c, $(basename $(SOURCES))) \
					
OBJS			=	$(SOURCES:%.c=%.o)
OBJS_BONUS		=	$(SOURCES_BONUS:%.c=%.o)

# ###################################################################### TARGETS
all:				$(NAME)

$(NAME):			$(addprefix $(PATH_OBJ),$(OBJS))
					$(MAKE) -C ./libft
					$(CC) $(INCLUDES) libft/libft.a $(addprefix $(PATH_OBJ),$(OBJS)) $(MLXFLAGS) -o $(NAME)
					
$(NAME_BONUS):		$(addprefix $(PATH_OBJ_BONUS),$(OBJS_BONUS))
					$(MAKE) -C ./libft
					$(CC) $(INCLUDES_BONUS) libft/libft.a $(addprefix $(PATH_OBJ_BONUS),$(OBJS_BONUS)) $(MLXFLAGS) -o $(NAME_BONUS)

$(PATH_OBJ)%.o:		$(PATH_SRC)%.c $(PATH_INC)
					@mkdir -p mandatory/obj
					@mkdir -p mandatory/obj/core/load_file
					@mkdir -p mandatory/obj/core/load_game
					@mkdir -p mandatory/obj/core
					@mkdir -p mandatory/obj/events
					@mkdir -p mandatory/obj/ray_casting
					@mkdir -p mandatory/obj/render
					@mkdir -p mandatory/obj/validate
					$(CC) $(INCLUDES) $(MLXFLAGS) -c $< -o $@
					
$(PATH_OBJ_BONUS)%.o:	$(PATH_SRC_BONUS)%.c $(PATH_INC_BONUS)
						@mkdir -p bonus/obj
						@mkdir -p bonus/obj/core/load_file
						@mkdir -p bonus/obj/core/load_game
						@mkdir -p bonus/obj/core
						@mkdir -p bonus/obj/events
						@mkdir -p bonus/obj/fps
						@mkdir -p bonus/obj/ray_casting
						@mkdir -p bonus/obj/render
						@mkdir -p bonus/obj/validate
						@mkdir -p bonus/obj/sorting
						@mkdir -p bonus/obj/menu
						$(CC) $(INCLUDES_BONUS) $(MLXFLAGS) -c $< -o $@

run:				all
					./$(NAME)

bonus:				$(NAME_BONUS)

valgrind:			all
					$(VALGRIND) ./$(NAME) maps/success/map_1.cub

norm:
					norminette mandatory/ bonus/ libft/ | grep Error

clean:				
					$(MAKE) -C ./libft clean
					$(RM) mandatory/obj
					$(RM) bonus/obj

fclean:				clean
					$(MAKE) -C ./libft fclean
					$(RM) $(NAME) $(NAME_BONUS)

re:					fclean all

.PHONY:				all clean fclean re run valgrind