# ——————————————————————————————
#  Makefile for “DAFT” project (SDL3 + Libft + src)
# ——————————————————————————————

# Directory where all .o files go:
O_DIR := obj
LIBFT_OBJ_DIR := $(O_DIR)/Libft_obj
PREP_OBJ_DIR := $(O_DIR)/prep_obj
DAFT_OBJ_DIR := $(O_DIR)/daft_obj
DAFT_H := ../daft.h

# Project root (current directory)
ROOT := .

# ------------------------------------------------
# 1) Collect every .c under Libft/ 
#    (ft_*.c, other_*.c, plus the three “mfile_*.c” files)
# ------------------------------------------------
LIBFT_SRC := \
	$(wildcard $(ROOT)/Libft/ft_*.c) \
	$(wildcard $(ROOT)/Libft/other_*.c) \
	$(wildcard $(ROOT)/Libft/*printf*.c) \
	$(ROOT)/Libft/mfile_a_gnl.c \
	$(ROOT)/Libft/mfile_rw_support.c \
	$(ROOT)/Libft/mfile_store_fds_user.c \
	$(ROOT)/Libft/mfile_store_fds_utils.c \
	$(ROOT)/Libft/mfile_reset_fd.c

# ------------------------------------------------
# 2) Collect every .c under src/ 
# ------------------------------------------------
PREP_SRC := $(ROOT)/main.c $(wildcard $(ROOT)/prep_src/*.c)
DAFT_SRC := $(wildcard $(ROOT)/daft_src/*.c)

# ------------------------------------------------
# 3) Turn “./Libft/foo.c”  → “obj/foo.o”
# ------------------------------------------------
#    We know every entry in LIBFT_SRC looks like “./Libft/NAME.c”, 
#    so the pattern “$(ROOT)/Libft/%.c” matches it.
#    Replacing with “$(O_DIR)/%.o” yields “obj/NAME.o”.
# ------------------------------------------------
LIBFT_OBJ := $(patsubst $(ROOT)/Libft/%.c,$(LIBFT_OBJ_DIR)/%.o,$(LIBFT_SRC))

# ------------------------------------------------
# 4) Turn “src/bar.c”  → “obj/bar.o”
# ------------------------------------------------
PREP_OBJ := $(patsubst ./prep_src/%.c,$(PREP_OBJ_DIR)/%.o,$(PREP_SRC)) $(LIBFT_OBJ)
DAFT_OBJ := $(patsubst ./daft_src/%.c,$(DAFT_OBJ_DIR)/%.o,$(DAFT_SRC)) $(LIBFT_OBJ)

# ------------------------------------------------
# 6) Our final files:
# ------------------------------------------------
PREP := prep.out
DAFT := ../daft.a

# ------------------------------------------------
# 7) Compiler + flags
# ------------------------------------------------
COMP   := cc
# Include paths
CFLAGS +=  -Wall -Wextra -Werror -g \
  -I$(HOME)/libs/SDL2/SDL_image/include/ \
  -I$(HOME)/libs/SDL2/SDL_mixer/include/ \
  -I$(HOME)/libs/SDL2/SDL/include

#LDFLAGS = $(shell pkg-config --libs --cflags sdl3 sdl3-mixer sdl3-image)\
# Library paths and linking
LDFLAGS =	-L$(HOME)/.local/bin/sdl -lSDL2 \
  			-L$(HOME)/.local/bin/sdl -lSDL2_mixer \
  			-L$(HOME)/.local/bin/sdl -lSDL2_image -lm  \

# ------------------------------------------------
# 8) Phony targets
# ------------------------------------------------
.PHONY: all clean fclean re

# ------------------------------------------------
# Default rule: build the executable
# ------------------------------------------------
all: $(PREP) $(DAFT)

# Link step: make $(NAME) from all object files
# Note: “| $(O_DIR)” means “ensure obj/ exists before proceeding”
$(PREP): $(PREP_OBJ) $(DAFT_H) | $(O_DIR)
	$(COMP) $(CFLAGS) $(PREP_OBJ) -o $(PREP) $(LDFLAGS)

$(DAFT): $(DAFT_OBJ) $(DAFT_H) | $(O_DIR)
	ar rcs $(DAFT) $(PREP_OBJ) $(DAFT_OBJ)

# ------------------------------------------------
# 9) Ensure the obj/ directory exists
# ------------------------------------------------
# This rule says: “if you ever need obj/, just mkdir -p it”
$(O_DIR):
	mkdir -p $(O_DIR)
	mkdir -p $(LIBFT_OBJ_DIR)
	mkdir -p $(PREP_OBJ_DIR)
	mkdir -p $(DAFT_OBJ_DIR)

# ------------------------------------------------
# 10) How to compile ANY “./Libft/NAME.c” → “obj/NAME.o”
#     (Note: identical target‐pattern for all Libft files)
# ------------------------------------------------

# ------------------------------------------------
# 11) How to compile ANY “src/NAME.c” → “obj/NAME.o”
# ------------------------------------------------

# 11a) Libft
$(LIBFT_OBJ_DIR)/%.o: $(ROOT)/Libft/%.c | $(O_DIR)
	$(COMP) $(CFLAGS) -c $< -o $@

# 11b) Prep
$(PREP_OBJ_DIR)/%.o: prep_src/%.c | $(O_DIR)
	$(COMP) $(CFLAGS) -c $< -o $@

# 11c) Daft
$(DAFT_OBJ_DIR)/%.o: daft_src/%.c | $(O_DIR)
	$(COMP) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(O_DIR)

fclean: clean
	rm -f $(PREP) $(DAFT)

re: fclean all
.SILENT: 