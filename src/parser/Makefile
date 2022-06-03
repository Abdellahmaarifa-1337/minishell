CC=cc
CFLAGS= -Wall -Wextra -Wall -g

#------------------------ PATHS ------------------------#

METHODS = ./methods
MODULES = ./modules
TMP = ./tmp
LEXER_MD = ./modules/lexer
EXPAN_MD = ./modules/expander
LIB = ./lib
QUOTERM_MD = ./modules/quote_removal
PARSSERR_MD = ./modules/parsing_err

STX_CHECK= ./syntax_check
TOKEN_MT = ./methods/token
TOKENSRC = ./methods/token_source

#-------------------- SYNTAX CHECKER --------------------#
SYNTAX_CHECK = ${STX_CHECK}/syntax_checker.c \
	${STX_CHECK}/pipe_check.c ${STX_CHECK}/redirection_check.c \
	${STX_CHECK}/quotes_check.c

#---------------------- PARSER LIB ----------------------#
LIB_SRC = ${LIB}/parse_cmd.c ${LIB}/join_strings.c \
		  ${LIB}/flag_pipe.c

#---------------------- TOKEN METHODS ----------------------#
TOKEN_MT_SRC = ${TOKEN_MT}/token.c

#---------------------- Parssing Errors -------------------#
TOKENSRC_SRC = ${TOKENSRC}/token_source.c

#-------------------- Scanner Module ---------------------#
LEXER_MD_SRC = ${LEXER_MD}/lexer.c 

#-------------------- Expander Module ---------------------#
EXPAN_MD_SRC = ${EXPAN_MD}/expander.c ${EXPAN_MD}/quotes_opr.c

#----------------------- Quote Removal --------------------#
QUOTERM_MD_SRC = ${QUOTERM_MD}/quote_removal.c

#---------------------- Parssing Errors -------------------#
PARSSERR_MD_SRC = ${PARSSERR_MD}/parsing_err.c

#---------------------- PARSSER SOURCE -------------------#
SRC = parser.c \
	${SYNTAX_CHECK} \
	${LIB_SRC} ${LEXER_MD_SRC} \
	${EXPAN_MD_SRC} ${QUOTERM_MD_SRC} \
	${TOKEN_MT_SRC} \
	${TOKENSRC_SRC} \
	${TMP}/print_data.c \


NAME = parser.a

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
