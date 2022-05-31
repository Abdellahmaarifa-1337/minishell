CC=cc
CFLAGS= -Wall -Wextra -Wall #-fsanitize=address
UTILS= src/utils
PARSER= src/parser

LIB = src/lib/set_env.c src/lib/create_env.c
SRC= minishell.c ${LIB} ${BUILTINS}
LIBFT= src/libft/libft.a
PARSER= src/parser/parser.a
BUILTIN= src/builtins/builtins.a

OBJ=${SRC:.c=.o}

NAME=minishell

.c.o:
	@${CC} ${CFLAGS} -c $< -o $@

All: call_make ${NAME}

call_make:
	make -C src/libft
	make -C src/parser
	make -C src/builtins

${NAME}:${OBJ} $(LIBFT) $(PARSER) $(BUILTIN)
	@${CC} ${CFLAGS} ${LIBFT} ${PARSER} ${BUILTIN} ${OBJ} -o ${NAME} -lreadline

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
re : fclean All
.PHONY: clean fclean re All call_make
