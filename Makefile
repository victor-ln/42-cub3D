# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:38:33 by adrianofaus       #+#    #+#              #
#    Updated: 2022/07/07 21:46:42 by vlima-nu         ###   ########.fr        #
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
MLXFLAGS		=	-Lmlx_linux -lmlx_Linux -Imlx_linux -L/usr/lib -lXext -lX11 -lm -lz
CC				=	gcc $(CFLAGS) $(INCLUDES)
VALGRIND		=	valgrind \
					--leak-check=full \
					--show-leak-kinds=all \
					--track-origins=yes \

#PATHS
PATH_OBJ		=	obj/
PATH_SRC		=	srcs/
PATH_INC		=	includes/

# FILES
SOURCES			=	main.c load_file.c save_params.c file_validate.c map_validate.c exit_routines.c resize_map.c\
					exit_routines.c

OBJS			=	$(SOURCES:%.c=%.o)

# ###################################################################### TARGETS
all:				makedir $(NAME)

makedir:
					$(MKDIR) $(PATH_OBJ)

$(NAME):			$(addprefix $(PATH_OBJ),$(OBJS))
					$(CC) $(addprefix $(PATH_OBJ),$(OBJS)) $(MLXFLAGS) -o $(NAME)

$(PATH_OBJ)%.o:		$(PATH_SRC)%.c $(PATH_INC)$(HEADERS)
					$(CC) $(MLXFLAGS) -c $< -o $@

run:				all
					./$(NAME)

valgrind:			all
					$(VALGRIND) ./$(NAME)

clean:				
					$(RM) $(addprefix $(PATH_OBJ), $(OBJS)) rmdir obj

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re run valgrind