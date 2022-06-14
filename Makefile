CC=cc
CFLAGS= -Wall -Wextra -Wall -g -fsanitize=address 
UTILS= src/utils
PARSER= src/parser

RDLIB= -L/Users/${USER}/Documents/.brew/opt/readline/lib 
RDINCLUDE = -I/Users/${USER}/Documents/.brew/opt/readline/include/

#RDLIB= -L/Users/${USER}/.brew/Cellar/readline/8.1.2/lib
#RDINCLUDE = -I/Users/${USER}/.brew/Cellar/readline/8.1.2/include/

LIB = src/lib/set_env.c src/lib/create_env.c src/lib/get_env.c \
	src/lib/get_index_char.c src/lib/signals.c
SRC= minishell.c ${LIB} ${BUILTINS}
LIBFT= src/libft/libft.a
PARSER= src/parser/parser.a
BUILTIN= src/builtins/builtins.a
EXECUTION= src/execution/execution.a
OBJ=${SRC:.c=.o}

NAME=minishell

.c.o:
	@${CC} ${CFLAGS} -c $< -o $@

All: call_make ${NAME}

call_make:
	make -C src/libft
	make -C src/parser
	make -C src/builtins
	make -C src/execution

${NAME}:${OBJ} $(LIBFT) $(PARSER) $(BUILTIN) $(EXECUTION)
	@${CC} ${CFLAGS} -lreadline ${RDLIB} ${RDINCLUDE} ${LIBFT} ${PARSER} ${BUILTIN} $(EXECUTION) ${OBJ} -o ${NAME} 

clean:
	make clean -C src/libft
	make clean -C src/parser
	make clean -C src/builtins
	make clean -C src/execution
	rm -rf ${OBJ} 
fclean: clean
	make fclean -C src/libft
	make fclean -C src/parser
	make fclean -C src/builtins
	make fclean -C src/execution
	rm -rf ${NAME}
re : fclean All
.PHONY: clean fclean re All call_make