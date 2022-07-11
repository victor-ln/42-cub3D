NAME		=	libft.a

CC			=	clang
FLAGS		=	-Wall -Wextra -Werror -g3 -O3 -fPIE

SRC			=	ft_atoi.c ft_bzero.c ft_calloc.c ft_putendl_fd.c ft_isspace.c ft_isdigit.c ft_substr.c \
				ft_strdup.c ft_strjoin.c ft_strlen.c ft_memcpy.c ft_split.c\
				ft_strcmp.c ft_utoa.c ft_rand.c ft_delay.c ft_free_null.c \
				ft_free_matrix.c ft_count_vectors.c ft_strchr.c ft_strrchr.c ft_strncmp.c\

OBJ_DIR		=	obj
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all:		$(NAME)

$(OBJ_DIR)/%.o:	%.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME):	$(OBJ_DIR)	$(OBJ)
	@ar crs $(NAME) $(OBJ)

clean:
	@rm -fr ./obj

fclean:		clean
	@rm -fr $(NAME)

re:	fclean all

.PHONY: all, clean, fclean, re, bonus
