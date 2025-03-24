SRCS		=	src/utils/controls_utils.c \
				src/utils/controls.c \
				src/utils/convert_utils.c \
				src/utils/convert.c \
				src/utils/draw.c \
				src/utils/img.c \
				src/utils/instructions.c \
				src/utils/map.c \
				src/utils/matrix.c \
				src/utils/rotation_matrix.c \
				src/utils/utils.c \
				src/main.c
HEADERS		= 	src/includes/fdf.h \
				src/includes/keys.h
NAME		=	fdf
CC			=	clang -Wall -Wextra -Werror -g
FLAGS		=	-lm -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit
FLAGS_LINUX	=	-lm -Lminilibx_linux -lmlx -Llibft -lft -lXext -lX11

%.o: %.c ${HEADERS} libft/libft.a libmlx.dylib
			${CC} $< -c -o $@

all:		libft mlx ${NAME}

${NAME}:	${SRCS:.c=.o} ${HEADERS}
			${CC} ${SRCS:.c=.o} -o ${NAME} ${FLAGS}

clean:
			rm -rf ${SRCS:.c=.o}
			make clean -C libft
			make clean -C mlx

fclean:		clean
			make fclean -C libft
			rm -rf libmlx.dylib
			rm -rf ${NAME}

re:			fclean all

libft:
			@make -C libft

mlx:
			@make -C mlx

linux:		${SRCS:.c=.o} ${HEADERS}
			make -C libft
			make -C minilibx_linux
			${CC} ${SRCS:.c=.o} -o ${NAME} ${FLAGS_LINUX}

.PHONY:		all clean fclean re libft mlx linux
