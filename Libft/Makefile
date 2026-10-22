#SECTION -	settings

NAME = libft.a
OBJ_DIR = obj_dir
CFLAGS = -Wall -Wextra -Werror -fPIC -g
LFLAGS = 
CC = cc

#SECTION - paths

PATH_BFS =			algorythm/bfs
PATH_CHECKS =		checks
PATH_DAFT_PREP =	daft/program/prep_src
PATH_DAFT_PROG =	daft/program/daft_src
PATH_DATA_MATR =	data/matrix
PATH_DATA_MAP =		data/map
PATH_DATA_LIST =	data/list
PATH_FILES =		files
PATH_MATH =			math
PATH_MEM =			mem
PATH_PRINTF =		printf
PATH_STRING =		string

#SECTION - filepaths

SRC_ALGORYTHM =	$(addprefix $(PATH_BFS)/, $(shell ls $(PATH_BFS) 2>/dev/null | grep \\.c))
SRC_CHECKS =	$(addprefix $(PATH_CHECKS)/, $(shell ls $(PATH_CHECKS) 2>/dev/null | grep \\.c))
SRC_DAFT =		$(addprefix $(PATH_DAFT_PREP)/, $(shell ls $(PATH_DAFT_PREP) 2>/dev/null | grep \\.c)) 	\
				$(addprefix $(PATH_DAFT_PROG)/, $(shell ls $(PATH_DAFT_PROG) 2>/dev/null | grep \\.c))
SRC_DATA =		$(addprefix $(PATH_DATA_MATR)/, $(shell ls $(PATH_DATA_MATR) 2>/dev/null | grep \\.c)) \
				$(addprefix $(PATH_DATA_LIST)/, $(shell ls $(PATH_DATA_LIST) 2>/dev/null | grep \\.c)) \
				$(addprefix $(PATH_DATA_MAP)/, $(shell ls $(PATH_DATA_MAP) 2>/dev/null | grep \\.c))
SRC_FILES =		$(addprefix $(PATH_FILES)/, $(shell ls $(PATH_FILES) 2>/dev/null | grep \\.c))
SRC_MATH =		$(addprefix $(PATH_MATH)/, $(shell ls $(PATH_MATH) 2>/dev/null | grep \\.c))
SRC_MEM =		$(addprefix $(PATH_MEM)/, $(shell ls $(PATH_MEM) 2>/dev/null | grep \\.c))
SRC_PRINTF =	$(addprefix $(PATH_PRINTF)/, $(shell ls $(PATH_PRINTF) 2>/dev/null | grep \\.c))
SRC_STRING =	$(addprefix $(PATH_STRING)/, $(shell ls $(PATH_STRING) 2>/dev/null | grep \\.c))

#SECTION - modules

ALL =				$(SRC_ALGORYTHM) $(SRC_CHECKS) $(SRC_DAFT) $(SRC_DATA) $(SRC_FILES) $(SRC_MATH) $(SRC_MEM) $(SRC_PRINTF) $(SRC_STRING)
MODULE_ALGORYTHM = 	$(SRC_ALGORYTHM) $(SRC_DATA) $(SRC_MEM)
MODULE_CHECKS = 	$(SRC_CHECKS)
MODULE_DAFT = 		$(SRC_DAFT) $(SRC_CHECKS) $(SRC_FILES) $(SRC_MATH) $(SRC_MEM) $(SRC_PRINTF) $(SRC_STRING)
MODULE_FILES = 		$(SRC_CHECKS) $(SRC_FILES) $(SRC_MATH) $(SRC_MEM) $(SRC_PRINTF) $(SRC_STRING)
MODULE_MATH = 		$(SRC_MATH)
MODULE_MEM = 		$(SRC_MEM)
MODULE_PRINTF = 	$(SRC_PRINTF) $(SRC_STRING) $(SRC_CHECKS) $(SRC_DATA) $(SRC_MEM) $(SRC_MATH)
MODULE_STRING = 	$(SRC_PRINTF) $(SRC_STRING) $(SRC_CHECKS) $(SRC_DATA) $(SRC_MEM) $(SRC_MATH)

#SECTION - object declaration

OBJ_ALL = $(addprefix $(OBJ_DIR)/, $(ALL:.c=.o))
OBJ_ALGORYTHM = $(addprefix $(OBJ_DIR)/, $(MODULE_ALGORYTHM:.c=.o))
OBJ_CHECKS = $(addprefix $(OBJ_DIR)/, $(MODULE_CHECKS:.c=.o))
OBJ_DAFT = $(addprefix $(OBJ_DIR)/, $(MODULE_DAFT:.c=.o))
OBJ_DATA = $(addprefix $(OBJ_DIR)/, $(MODULE_DATA:.c=.o))
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(MODULE_FILES:.c=.o))
OBJ_MATH = $(addprefix $(OBJ_DIR)/, $(MODULE_MATH:.c=.o))
OBJ_MEM = $(addprefix $(OBJ_DIR)/, $(MODULE_MEM:.c=.o))
OBJ_PRINTF = $(addprefix $(OBJ_DIR)/, $(MODULE_PRINTF:.c=.o))
OBJ_STRING = $(addprefix $(OBJ_DIR)/, $(MODULE_STRING:.c=.o))

#SECTION -	commands

$(NAME): $(OBJ_ALL)
	ar rcs $(NAME)  $(OBJ_ALL)

count: 
	@echo $(OBJ_ALL) | wc -w

all: $(NAME)

algorythm: $(OBJ_ALGORYTHM)
	ar rcs $(NAME) $(OBJ_ALGORYTHM)

checks: $(OBJ_CHECKS)
	ar rcs $(NAME) $(OBJ_CHECKS)	

daft: $(OBJ_DAFT)
	ar rcs $(NAME) $(OBJ_DAFT)

data: $(OBJ_DATA)
	ar rcs $(NAME) $(OBJ_DATA)

files: $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES)

math: $(OBJ_MATH)
	ar rcs $(NAME) $(OBJ_MATH)

mem: $(OBJ_MEM)
	ar rcs $(NAME) $(OBJ_MEM)

printf: $(OBJ_PRINTF)
	ar rcs $(NAME) $(OBJ_PRINTF)

string: $(OBJ_STRING)
	ar rcs $(NAME) $(OBJ_STRING)

help:
	@echo "List of all modules:\n\033[33m"\
			"all\n"\
			"algorythm\n"\
			"checks\n"\
			"daft\n"\
			"data\n"\
			"files\n"\
			"math\n"\
			"mem\n"\
			"printf\n"\
			"string\033[0m"

$(OBJ_DIR) : 
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.txt *.out *.log
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f daft/DATA_DIR/hash_data/*

re: fclean all

.PHONY: help files
