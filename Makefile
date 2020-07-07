# Made by CocoKitty on 2020-06-30

# does not work with compilers
# that have different flags
# than gcc, so you cant just
# change it to clang or something
CC := gcc

# program version
VER_MAJOR := 0
VER_MINOR := 0
VER_PATCH := 0
VER_STR   := $(VER_MAJOR).$(VER_MINOR).$(VER_PATCH)

# flags
BOTH_FLAGS := -Wall -Wextra -Wunreachable-code -std=c11 -pedantic
DEBUG_FLAGS := -ggdb
RELEASE_FLAGS := -O1
debug: ANY_FLAGS := $(BOTH_FLAGS) $(DEBUG_FLAGS)
release: ANY_FLAGS := $(BOTH_FLAGS) $(RELEASE_FLAGS)

# macros
BOTH_MACROS := -DMAJOR=$(VER_MAJOR) \
               -DMINOR=$(VER_MINOR) \
			   -DPATCH=$(VER_PATCH) \
			   -DVER_STR=\"$(VER_STR)\"
DEBUG_MACROS := -DDEBUG
RELEASE_MACROS := -DRELEASE
debug: ANY_MACROS := $(DEBUG_MACROS) $(BOTH_MACROS)
release: ANY_MACROS := $(RELEASE_MACROS) $(BOTH_MACROS)

# object file locations
DEBUG_OBJ_LOC := ./obj/debug
RELEASE_OBJ_LOC := ./obj/release
debug: ANY_OBJ_LOC := $(DEBUG_OBJ_LOC)
release: ANY_OBJ_LOC := $(RELEASE_OBJ_LOC)

# src loc
SRC_LOC := ./src

# targets
debug: make_dirs main.o
	$(CC) $(ANY_FLAGS) -o ./bin/debug.exe $(ANY_OBJ_LOC)/*.o

release: make_dirs main.o
	$(CC) $(ANY_FLAGS) -o debug.exe $(ANY_OBJ_LOC)/*.o

# files

# function for easily adding files
# usage: $(call gen_ccomp,<c_file_loc>)
define gen_ccomp
	$(CC) $(ANY_FLAGS) $(ANY_MACROS) -c -o $(ANY_OBJ_LOC)/$(basename $(notdir $(1))).o $(SRC_LOC)/$(1)
endef

# not cross platform
make_dirs:
	mkdir -p "obj/debug"
	mkdir -p "obj/release"
main.o:
	$(call gen_ccomp,main.c)


