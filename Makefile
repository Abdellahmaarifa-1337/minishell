CC=cc
CFLAGS= #-Wall -Wextra -Wall -fsanitize=address
UTILS= src/utils
PARSER= src/parser

LIB = src/lib/set_env.c
BUILTINS  = src/builtins/unset.c src/builtins/env.c
SRC= minishell.c ${LIB} ${BUILTINS}
LIBFT= src/libft/libft.a
PARSER= src/parser/parser.a
BUILTINS= src/builtins/builtins.a
OBJ=${SRC:.c=.o}

NAME=minishell

.c.o:
	@${CC} ${CFLAGS} -c $< -o $@

all: call_make ${NAME}

call_make:
	make -C src/libft
	make -C src/parser
	make -C src/builtins

${NAME}:${OBJ} $(LIBFT) $(PARSER)
	@${CC} ${CFLAGS} ${LIBFT} ${PARSER} ${BUILTINS} ${OBJ} -o ${NAME} -lreadline

#${OBJ}:${SRC}

clean:
	make clean -C src/libft
	make clean -C src/parser
	make clean -C src/builtins
	rm -rf ${OBJ} 
fclean: clean
	make fclean -C src/libft
	make fclean -C src/parser
	make fclean -C src/builtins
	rm -rf ${NAME}
re : fclean all
.PHONY: clean fclean re all call_make


