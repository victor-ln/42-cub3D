# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:38:33 by adrianofaus       #+#    #+#              #
#    Updated: 2022/07/13 23:04:11 by afaustin         ###   ########.fr        #
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
DEBUG			=	-g3

# COMPILATION
CFLAGS			=	-Wall -Wextra -Werror
MLXFLAGS		=	-Lmlx_linux -lmlx_Linux -Imlx_linux -L/usr/lib -lXext -lX11 -lm -lz -L libft/ -lft
CC				=	gcc $(CFLAGS) $(INCLUDES) $(DEBUG)
VALGRIND		=	valgrind \
					--leak-check=full \
					--show-leak-kinds=all \
					--track-origins=yes

#PATHS
PATH_OBJ		=	obj/
PATH_SRC		=	srcs/
PATH_INC		=	includes/

# FILES
SOURCES			=	main.c \
					load_file.c \
					save_params.c \
					validate_routines.c \
					map_validate.c \
					exit_routines.c \
					resize_map.c \
					save_utils.c \
					debug_map.c \

OBJS			=	$(SOURCES:%.c=%.o)

# ###################################################################### TARGETS
all:				$(NAME)

$(NAME):			$(addprefix $(PATH_OBJ),$(OBJS))
					$(MAKE) -C ./libft
					$(CC) libft/libft.a $(addprefix $(PATH_OBJ),$(OBJS)) $(MLXFLAGS) -o $(NAME)

$(PATH_OBJ)%.o:		$(PATH_SRC)%.c $(PATH_INC)$(HEADERS)
					@mkdir -p obj
					$(CC) $(MLXFLAGS) -c $< -o $@

run:				all
					./$(NAME)

valgrind:			all
					$(VALGRIND) ./$(NAME)

clean:				
					$(MAKE) -C ./libft clean
					$(RM) $(addprefix $(PATH_OBJ), $(OBJS)) rmdir obj

fclean:				clean
					$(MAKE) -C ./libft fclean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re run valgrind