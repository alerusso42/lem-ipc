NAME := lem-ipc

PATH_BUILD := build
PATH_OUTPUT := $(PATH_BUILD)/output
PATH_LIBFT := $(PATH_BUILD)/libft.a
PATH_EXPERIMENT := study/experiments
PATH_TEST		:= test/
PATH_SUPP		:= $(PATH_TEST)/valgrind.supp
PATH_SRCS 		:= srcs
PATH_MAIN	 	:= $(PATH_SRCS)/main.c
PATH_FRONTEND 	:= $(PATH_SRCS)/frontend
PATH_BACKEND	:= $(PATH_SRCS)/backend
PATH_UTILS		:= $(PATH_SRCS)/utils
OBJ_DIR			:= $(PATH_BUILD)/obj
IS_LIB_READY	:= $(PATH_BUILD)/libft.a $(PATH_BUILD)/libSDL3.so $(PATH_BUILD)/libSDL3_mixer.so $(PATH_BUILD)/libSDL3_ttf.so 

COMP 		:= gcc -Wall -Wextra -Werror -g
RPATH		:= -Wl,-rpath=$(shell pwd)/$(PATH_BUILD)
INCLUDES 	:= -I libs/SDL/include -I libs/SDL_mixer/include -I libs/SDL_ttf/include
SHARED_LIB 	:= $(PATH_BUILD)/libSDL3.so $(PATH_BUILD)/libSDL3_mixer.so $(PATH_BUILD)/libSDL3_ttf.so
STATIC_LIB	:= $(PATH_BUILD)/libft.a

SRC = $(PATH_MAIN) $(addprefix $(PATH_FRONTEND)/, $(shell ls $(PATH_FRONTEND))) $(addprefix $(PATH_BACKEND)/, $(shell ls $(PATH_BACKEND))) $(addprefix $(PATH_UTILS)/, $(shell ls $(PATH_UTILS)))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

#SECTION - compilation rules

$(NAME): $(IS_LIB_READY) $(OBJ)
	$(COMP) $(RPATH) $(INCLUDES) $(OBJ) $(SHARED_LIB) $(STATIC_LIB) -o $(NAME)
	cp $(NAME) $(PATH_OUTPUT)/$(NAME)
	export LD_LIBRARY_PATH=$(shell pwd)/$(PATH_BUILD)

all: $(NAME)


clean: 
	(cd Libft/ && make clean)
	rm -f *.out
	rm -rf $(OBJ_DIR)

fclean: clean 
	(cd Libft/ && make fclean)
	rm -rf $(PATH_BUILD) $(NAME)

clean_prog:
	rm -rf $(OBJ_DIR)

re: fclean all

#useful when a header file is modified
prog: clean_prog $(NAME)
	

#SECTION - utils rules

$(OBJ_DIR) : 
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(COMP) $(INCLUDES) -c $< -o $@

$(PATH_BUILD)/lib%:
	make libs

libs: 
	mkdir -p $(PATH_OUTPUT)
	(cd Libft/ && make essentials && cp libft.a $$OLDPWD/$(PATH_BUILD))
	(cd libs && ./sdl_setup.sh)

#SECTION - run rules

run: $(NAME)
	./$(NAME) &

valgrind: $(NAME)
	valgrind --show-leak-kinds=all --leak-check=yes --suppressions=$(PATH_SUPP) ./$(NAME) &

#SECTION - test rules

experiment: $(IS_LIB_READY)
	clear
	@echo "usage: make experiment EXP=shm_files.c"
	export LD_LIBRARY_PATH=$(shell pwd)/$(PATH_BUILD)
	$(COMP) $(RPATH) $(INCLUDES) $(PATH_EXPERIMENT)/$(EXP) $(SHARED_LIB) $(PATH_EXPERIMENT)/utils.c $(PATH_LIBFT)
	clear
	@echo "compilation ok."

shm_reset:
	rm -f /dev/shm/lem-ipc_shared_memory

.PHONY: libs shm_reset run