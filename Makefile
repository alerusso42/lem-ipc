PATH_BUILD := build
PATH_OUTPUT := ${PATH_BUILD}/output
PATH_LIBFT := $(PATH_OUTPUT)/libft.a

all: libft
	@echo "not implemented"

clean: 
	(cd Libft/ && make clean)
	rm -f $(addprefix ${PATH_BUILD}/, $(shell ls ${PATH_BUILD})) 2> /dev/null || exit 0

fclean: clean 
	(cd Libft/ && make fclean)
	rm -rf ${PATH_BUILD}
	@echo "not implemented"

re: fclean all

libft:
	mkdir -p ${PATH_OUTPUT}
	(cd Libft/ && make string && cp libft.a $$OLDPWD/${PATH_OUTPUT})