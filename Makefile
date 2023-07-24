SRCS_DIR	=	srcs/parsing/

SRC			=	parsing.c\
				graphics.c\
				lst.c\

SRCS		=	$(addprefix $(SRCS_DIR), $(SRC))

OBJS_DIR	=	objs/

OBJ			=	${SRC:.c=.o}

OBJS		=	$(addprefix $(OBJS_DIR), $(OBJ))

NAME		=	cub3D

CC			=	gcc -g

CFLAGS		=	-Wall -Wextra -Werror

INCS		=	-I ./includes/

MLX			=	srcs/minilibx-linux/libmlx_Linux.a -L -I srcs/minilibx-linux/mlx.h -O3 -lXext -lX11 -lm

all:		${OBJS_DIR} ${NAME}

${OBJS_DIR}:
			mkdir ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
			${CC} ${CFLAGS} -c $< -o $@ ${INCS}

${NAME}:	${OBJS}
			${CC} ${FLAGS} ${OBJS} -o ${NAME} ${MLX}

clean:
			rm -rf ${OBJS_DIR}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re