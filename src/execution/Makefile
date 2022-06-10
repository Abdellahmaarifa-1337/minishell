CC=cc
CFLAGS= -Wall -Wextra -Wall -fsanitize=address


METHODS= ./methods/get_args.c ./methods/resolve_path.c \
		./methods/exec_here_doc.c ./methods/get_in_out_file.c \

SRC = execution.c $(METHODS)

NAME = execution.a

OBJ=${SRC:.c=.o}

.c.o:
	@${CC} ${CFLAGS} -c $< -o $@
	@ar rc ${NAME} $@

all: ${NAME}

${NAME}:${OBJ}

${OBJ}:${SRC}

clean:
	rm -rf ${OBJ} 
fclean: clean
	rm -rf ${NAME}
.PHONY: clean fclean all
