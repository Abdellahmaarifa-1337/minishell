CC = cc
CFLAGS = -g #-Wall -Werror -Wextra

#------------------------- BUILTINS ------------------------#
BUILTINS = builtins.c echo.c pwd.c env.c export.c unset.c \
		cd.c \
		./lib/export_print.c ./lib/is_valid_idn.c \
		../execution/methods/parameters.c

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
