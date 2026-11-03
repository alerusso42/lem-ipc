NAME := lem-ipc

PATH_BUILD := build
PATH_OUTPUT := $(PATH_BUILD)/output
PATH_LIBFT := $(PATH_BUILD)/libft.a
PATH_EXPERIMENT := study/experiments
PATH_SRCS 		:= srcs
PATH_MAIN	 	:= $(PATH_SRCS)/main.c
PATH_FRONTEND 	:= $(PATH_SRCS)/frontend
PATH_GAME 		:= $(PATH_SRCS)/game
PATH_SETUP 		:= $(PATH_SRCS)/setup
PATH_UTILS		:= $(PATH_SRCS)/utils
OBJ_DIR			:= $(PATH_BUILD)/obj/srcs
IS_LIB_READY	:= $(PATH_BUILD)/libft.a $(PATH_BUILD)/libSDL3.so $(PATH_BUILD)/libSDL3_mixer.so $(PATH_BUILD)/libSDL3_ttf.so 

COMP 		:= gcc -Wall -Wextra -Werror -g
INCLUDES 	:= -I libs/SDL/include -I libs/SDL_mixer/include -I libs/SDL_ttf/include
SHARED_LIB 	:= $(PATH_BUILD)/libSDL3.so $(PATH_BUILD)/libSDL3_mixer.so $(PATH_BUILD)/libSDL3_ttf.so

SRC = $(PATH_MAIN) $(shell ls $(PATH_FRONTEND)) $(shell ls $(PATH_GAME)) $(shell ls $(PATH_SETUP)) $(shell ls $(PATH_UTILS))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

$(NAME): $(IS_LIB_READY) $(OBJ)
	$(COMP) $(INCLUDES) $(OBJ) $(SHARED_LIB) 

all: $(NAME)


clean: 
	(cd Libft/ && make clean)
	rm -f *.out
	rm -f $(OBJ_DIR)

fclean: clean 
	(cd Libft/ && make fclean)
	rm -rf $(PATH_BUILD)
	@echo "not implemented"

re: fclean all

$(OBJ_DIR) : 
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(COMP) -c $< -o $@

libs: 
	mkdir -p $(PATH_OUTPUT)
	(cd Libft/ && make string && cp libft.a $$OLDPWD/$(PATH_BUILD))
	(cd libs && ./sdl_setup.sh)

$(PATH_BUILD)/libft.a:
	make libs


experiment: libft
	clear
	@echo "usage: make experiment EXP=shm_files.c"
	$(COMP) $(PATH_EXPERIMENT)/$(EXP) $(PATH_EXPERIMENT)/utils.c $(PATH_LIBFT)
	clear
	@echo "compilation ok."

.PHONY: libs