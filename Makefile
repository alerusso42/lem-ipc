PATH_BUILD := build
PATH_OUTPUT := $(PATH_BUILD)/output
PATH_LIBFT := $(PATH_OUTPUT)/libft.a
PATH_EXPERIMENT := study/experiments

COMP := gcc -Wall -Wextra -Werror -g

all: libft
	mkdir -p $(PATH_OUTPUT)
	@echo "not implemented"

clean: 
	(cd Libft/ && make clean)
	rm -f $(addprefix $(PATH_BUILD)/, $(shell ls $(PATH_BUILD))) 2> /dev/null || exit 0

fclean: clean 
	(cd Libft/ && make fclean)
	rm -rf $(PATH_BUILD)
	@echo "not implemented"

re: fclean all

libft:
	mkdir -p $(PATH_OUTPUT)
	(cd Libft/ && make string && cp libft.a $$OLDPWD/$(PATH_OUTPUT))

experiment: libft
# 	@if [ [ $$NAME = "" ] ]; then \
# 		echo "please give a name, like make NAME=shm_files.c" ; \
# 		exit 1; \
# 	fi
# 	@if [ -f $(PATH_EXPERIMENT)/$$NAME]; then \
# 		echo "$(PATH_EXPERIMENT)/$$NAME does not exist. Try one of the following:"; \
# 		ls $(PATH_EXPERIMENT); \
# 		exit 1 \
# 	fi
	$(COMP) $(PATH_EXPERIMENT)/$(EXP) $(PATH_LIBFT)