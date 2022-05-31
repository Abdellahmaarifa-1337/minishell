CC=cc
CFLAGS= -Wall -Wextra -Wall #-fsanitize=address
UTILS= src/utils
PARSER= src/parser

LIB = src/lib/set_env.c src/lib/create_env.c
BUILTINS  = src/builtins/unset.c src/builtins/env.c src/builtins/export.c \
		 src/builtins/lib/export_print.c src/builtins/lib/is_valid_idn.c
SRC= minishell.c ${LIB} ${BUILTINS}
LIBFT= src/libft/libft.a
PARSER= src/parser/parser.a
OBJ=${SRC:.c=.o}

NAME=minishell

.c.o:
	@${CC} ${CFLAGS} -c $< -o $@

All: call_make ${NAME}

call_make:
	make -C src/libft
	make -C src/parser

${NAME}:${OBJ} $(LIBFT) $(PARSER)
	@${CC} ${CFLAGS} ${LIBFT} ${PARSER} ${OBJ} -o ${NAME} -lreadline

#${OBJ}:${SRC}

clean:
	cd src/libft && make clean
	cd src/parser && make clean
	rm -rf ${OBJ} 
fclean: clean
	cd src/libft && make fclean 
	cd src/parser && make fclean
	rm -rf ${NAME}
.PHONY: clean fclean


