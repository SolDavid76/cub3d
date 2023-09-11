SRCS_PARSING_DIR	=	srcs/parsing/

SRC_PARSING		=	data.c\
					free.c\
					getters.c\
					graphics.c\
					lst.c\
					mini_map.c\
					parsing.c\
					path_finding.c\
					utils.c\
					utils_aux.c\

SRCS_GAME_DIR	=	srcs/game/

SRC_GAME		=	move.c\
					drawing.c\
					raycasting.c\
					raycasting_utils.c\
					main.c\
					init.c\
					hook.c\
					move_utils.c\
				
SRCS		=	$(addprefix $(SRCS_PARSING_DIR), $(SRC_PARSING))\
				$(addprefix $(SRCS_GAME_DIR), $(SRC_GAME))

OBJS_DIR	=	objs/

OBJ			=	${SRC_PARSING:.c=.o}\
				${SRC_GAME:.c=.o}

OBJS		=	$(addprefix $(OBJS_DIR), $(OBJ))

NAME		=	cub3D

CC			=	gcc -g

CFLAGS		=	-Wall -Wextra -Werror

INCS		=	-I ./includes/

MLX			=	srcs/minilibx-linux/libmlx_Linux.a -L -I srcs/minilibx-linux/mlx.h -O3 -lXext -lX11 -lm

MLX_DIR		= srcs/minilibx-linux/

all:		MAKE_MLX ${OBJS_DIR} ${NAME}

${OBJS_DIR}:
			mkdir ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRCS_PARSING_DIR}%.c
			${CC} ${CFLAGS} -c $< -o $@ ${INCS}

${OBJS_DIR}%.o: ${SRCS_GAME_DIR}%.c
			${CC} ${CFLAGS} -c $< -o $@ ${INCS}

${NAME}:	${OBJS}
			${CC} ${FLAGS} ${OBJS} -o ${NAME} ${MLX}

MAKE_MLX:
			make -C ${MLX_DIR}

clean:
			rm -rf ${OBJS_DIR}
			make clean -C ${MLX_DIR}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
