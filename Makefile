# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:38:33 by adrianofaus       #+#    #+#              #
#    Updated: 2022/10/10 14:23:21 by vlima-nu         ###   ########.fr        #
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

LIBFT_PATH		=	libraries/libft/
MLX_PATH		=	libraries/mlx_linux

# DEBUG
DEBUG			=	-g3 -fsanitize=address

# COMPILATION
CFLAGS			=	-Wall -Wextra -Werror -O3 #$(DEBUG)
MLXFLAGS		=	-L$(MLX_PATH) -lmlx_Linux -I$(MLX_PATH) \
					-L/usr/lib -lXext -lX11 -lm -lz -L$(LIBFT_PATH) -lft
MAKEFILE_FLAGS	=	--no-print-directory --quiet

CC				=	gcc $(CFLAGS)
VALGRIND		=	valgrind \
					--leak-check=full \
					---quiethow-leak-kinds=all \
					--track-origins=yes

OBJ_DIR			=	mandatory/obj \
					mandatory/obj/core/load_file \
					mandatory/obj/core/load_game \
					mandatory/obj/core \
					mandatory/obj/events \
					mandatory/obj/ray_casting \
					mandatory/obj/render \
					mandatory/obj/validate \

OBJ_DIR_BONUS	=	bonus/obj \
					bonus/obj/core/load_file \
					bonus/obj/core/load_game \
					bonus/obj/core \
					bonus/obj/events \
					bonus/obj/fps \
					bonus/obj/ray_casting \
					bonus/obj/render \
					bonus/obj/validate \
					bonus/obj/sorting \
					bonus/obj/menu \

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
					colision

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
SOURCES			=	$(addprefix core/load_file/, $(LOAD_FILE)) \
					$(addprefix core/load_game/, $(LOAD_GAME)) \
					$(addprefix core/, $(CORE)) \
					$(addprefix events/, $(EVENTS)) \
					$(addprefix ray_casting/, $(RAY_CASTING)) \
					$(addprefix render/, $(RENDER)) \
					$(addprefix validate/, $(VALIDATE)) \

SOURCES_BONUS	=	$(addprefix menu/, $(MENU_BONUS)) \
					$(addprefix fps/, $(FPS_BONUS)) \
					$(addprefix sorting/, $(SORTING_BONUS)) \
					$(addprefix core/load_game/, $(LOAD_GAME_BONUS)) \
					$(addprefix core/, $(CORE_BONUS)) \
					$(addprefix events/, $(EVENTS_BONUS)) \
					$(addprefix ray_casting/, $(RAY_CASTING_BONUS)) \
					$(addprefix render/, $(RENDER_BONUS)) \
					$(addprefix validate/, $(VALIDATE_BONUS)) \
					$(basename $(SOURCES)) \

SOURCES			:= $(addsuffix .c, $(SOURCES))
SOURCES_BONUS	:= $(addsuffix _bonus.c, $(SOURCES_BONUS))

OBJS			=	$(addprefix $(PATH_OBJ),$(SOURCES:%.c=%.o))
OBJS_BONUS		=	$(addprefix $(PATH_OBJ_BONUS),$(SOURCES_BONUS:%.c=%.o))

ifndef ECHO
	T := $(shell $(MAKE) $(MAKECMDGOALS) -n ECHO="counter" | grep -c "counter")
endif

ifeq ($(firstword $(MAKECMDGOALS)), $(shell echo re))
	T := $(shell expr $(words $(FILES)) + 1)
endif

ITALIC_LIGHTER_YELLOW	= "\e[1;3;33m"
ITALIC_BOLD_GREEN		= "\e[0;3;92m"
RESET_COLOR				= "\e[0m"
PRINT	:=	$(shell which echo) -e

N := x
C = $(words $N)$(eval N := x $N)
P = "`expr $C '*' 100 / $T`"

ECHO = $(PRINT) $(ITALIC_BOLD_GREEN)"[$(P)%]\t"

# ###################################################################### TARGETS

all:				$(NAME)

$(NAME):			 $(OBJ_DIR) $(OBJS)
	@$(MAKE) $(MAKEFILE_FLAGS) -C $(LIBFT_PATH)
	@$(MAKE) $(MAKEFILE_FLAGS) -C $(MLX_PATH)
	@$(CC) $(INCLUDES) $(OBJS) $(MLXFLAGS) -o $(NAME)
	@$(ECHO) Game Created! $(RESET_COLOR)

$(NAME_BONUS):		$(OBJ_DIR_BONUS) $(OBJS_BONUS)
	@$(MAKE) $(MAKEFILE_FLAGS) -C $(LIBFT_PATH)
	@$(MAKE) $(MAKEFILE_FLAGS) -C $(MLX_PATH)
	@$(CC) $(INCLUDES_BONUS) $(OBJS_BONUS) $(MLXFLAGS) -o $(NAME_BONUS)
	@$(ECHO) Game Created! $(RESET_COLOR)

$(PATH_OBJ)%.o:		$(PATH_SRC)%.c $(PATH_INC)
	@$(ECHO) Compiling $< $(RESET_COLOR)
	@$(CC) $(INCLUDES) $(MLXFLAGS) -c $< -o $@
					
$(PATH_OBJ_BONUS)%.o:	$(PATH_SRC_BONUS)%.c $(PATH_INC_BONUS)
	@$(ECHO) Compiling $< $(RESET_COLOR)
	@$(CC) $(INCLUDES_BONUS) $(MLXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	@$(MKDIR) $(OBJ_DIR_BONUS)

run:				all
	./$(NAME)

bonus:				$(NAME_BONUS)

valgrind:			all
	$(VALGRIND) ./$(NAME) maps/map_0.cub

norm:
	norminette mandatory/ bonus/ $(LIBFT_PATH) | grep Error

clean:
	@$(MAKE) $(MAKEFILE_FLAGS) -C $(LIBFT_PATH) clean
	@$(MAKE) $(MAKEFILE_FLAGS) -C $(MLX_PATH) clean
	@$(RM) mandatory/obj
	@$(RM) bonus/obj
	@$(PRINT) $(ITALIC_LIGHTER_YELLOW)"Objects deleted" $(RESET_COLOR)

fclean:				clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME) $(NAME_BONUS)
	@$(PRINT) $(ITALIC_LIGHTER_YELLOW)"Game deleted" $(RESET_COLOR)

re:					fclean all

.PHONY:				all clean fclean re run valgrind
