CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address

#------------------------- BUILTINS ------------------------#
BUILTINS = builtins.c echo.c pwd.c env.c export.c unset.c \
		cd.c exit.c \
		./lib/export_print.c ./lib/is_valid_idn.c \
		./lib/env_convert.c ./lib/builtins_helper.c

#---------------------- EXECUTION SOURCE -------------------#
SRC = ${BUILTINS}


NAME = builtins.a

OBJ = ${SRC:.c=.o}

.c.o:
	@${CC} ${CFLAGS} -c $< -o $@
	@ar rc ${NAME} $@

all: ${NAME}

${NAME} : ${OBJ}

${OBJ} : ${SRC}

clean :
	rm -rf ${OBJ}
fclean : clean
	rm -rf ${NAME}
.PHONY : clean fclean all
