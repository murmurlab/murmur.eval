os					=	${shell uname -s}
CC					=	clang
RM					=	rm -rf
DEFINES				=	-D BUFFER_SIZE=65535
CFLAGS				=	-std=c99 $(DEFINES)

DIR					=	$(shell echo $(PWD))
PROGRAM				=	libmurmureval.a
LIB_DIR				=	lib
SRC_DIR				=	srcs
OBJ_DIR				=	.objs
BIN_DIR				=	build
NAME				=	$(BIN_DIR)/$(PROGRAM)
# CMD_DIR			=	cmd
# INC_DIR			=	-I $(SRC_DIR)/incs

program_dir			=	.

#lib paths######################################################################
ifeq "$(os)" "Darwin"
# minilibx_D			=	$(LIB_DIR)/minilibx_mms_20200219/
else ifeq ($(os),Linux)
# minilibx_D			=	$(LIB_DIR)/minilibx-linux
endif

# libft_D				=	$(LIB_DIR)/libft/
murmur_eval_D			=	$(program_dir)/

################################################################################

#lib paths######################################################################
# readline_L		=	-L $(LIB_DIR)/readline/lib/readline/lib -lreadline $(ltinfo)
# minilibx-linux_L	=	-L $(LIB_DIR)/minilibx-linux -lmlx

# minilibx-mms_L		=	-L $(minilibx_D) -lmlx
# libft_L				=	-L $(libft_D) -lft
################################################################################

#inc paths######################################################################
# readline_I		=	-I $(LIB_DIR)/readline/lib/readline/include
# minilibx-linux_I	=	-I $(LIB_DIR)/minilibx-linux/
# minilibx-mms_I		=	-I $(minilibx_D)
# lava_caster_I		=	-I $(program_dir)/inc/
# libft_I				=	-I $(libft_D)

murmur_eval_I		=	-I $(murmur_eval_D)/incs/
################################################################################

# readline_A		=	$(LIB_DIR)/readline/lib/libreadline.a
# minilibx-linux_A	=	$(LIB_DIR)/minilibx-linux/libmlx.a

# minilibx-mms_A		=	$(minilibx_D)/libmlx.dylib
# libft_A				=	$(libft_D)/libft.a

libr				=	


incs				=	$(murmur_eval_I)

CFLAGS				+=	$(incs)

SRCS				=	$(SRC_DIR)/murmur_eval.c

OBJS				=	$(SRCS:.c=.o)

CMD					=	
CMD_OBJS			=	$(CMD:.c=.o)
# CMD				=	$(PROGRAM).c

DEPENDENCIES		=	


j = 0
ifeq '$(os)' 'Darwin'
NPROCS = $(shell sysctl -n hw.ncpu)
else ifeq '$(os)' 'Linux'
NPROCS = $(shell nproc)
endif
ifeq '$(j)' '1'
MAKEFLAGS += -j$(NPROCS)
endif

w = 1
ifeq '$(w)' '1'
CFLAGS += -Wextra -Werror -Wall
endif

debug = 0
ifeq '$(debug)' '1'
CFLAGS += -g
endif

asan = 0
ifeq '$(asan)' '1'
# CFLAGS += -fsanitize=address
# CFLAGS += -fsanitize=thread
endif

leak =
msl = 0
ifeq '$(msl)' '1'
leak=MallocStackLogging=1
endif

test = 0
ifeq '$(test)' '1'
CFLAGS += -D TEST=$(test)
./$(attest) .
endif

all: $(DEPENDENCIES)
# @mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME)
# mv *.o $(OBJ_DIR)/

# b: bonus

m: mandatory

mandatory: all

# $(READLINE):
# 	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz
# 	@tar -xvf readline-8.2-rc1.tar.gz
# 	@$(RM) readline-8.2-rc1.tar.gz
# 	@cd readline-8.2-rc1 && ./configure --prefix=$(DIR)/lib/readline && make && make install
# 	@$(RM) readline-8.2-rc1

# $(lrl):
# 	$(MAKE) -C lib -j$(NPROCS) DIR=$(PWD)/lib

# $(minilibx-linux_A):
# 	$(MAKE) -C $(LIB_DIR)/minilibx-linux/

# $(minilibx-mms_A):
# 	$(MAKE) -j1 -C $(minilibx_D)

# $(libft_A):
# 	$(MAKE) -C $(LIB_DIR)/libft/

$(NAME): $(CMD_OBJS) $(OBJS) $(DEPENDENCIES)
	@mkdir -p $(BIN_DIR)
	ar -rcs $(NAME) $(OBJS) $(CMD_OBJS)
# $(CC) $(CMD_OBJS) $(libr) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@# @mv $@ $(OBJ_DIR)/

# run: t
# 	@echo "===================================program======================================\n"
# 	DYLD_LIBRARY_PATH=$(minilibx_D) $(leak) ./$(NAME)

clean:
	$(RM) $(OBJS) $(CMD_OBJS)
# $(MAKE) -C $(minilibx_D) clean
# $(MAKE) -C $(libft_D) clean
# find . -name "*.o" -exec $(RM) '{}' \;
c: clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(DEPENDENCIES)

f: fclean

re: fclean
	$(MAKE) all

t: all
	$(MAKE) clean
# @mkdir -p $(BIN_DIR)
# @$(CC) $(CFLAGS) $(INC_DIR) test/testing.c test/token_test.c test/dollar_test.c test/equal_primitive.c $(SRCS) -o bin/test
# @./bin/test

.PHONY: all clean fclean re run t f c run m b bonus mandatory





# INC	=%%%%

# UNAME = $(shell uname)
# CC	= gcc
# ifeq ($(UNAME),FreeBSD)
# 	CC = clang
# endif

# NAME		= libmlx.a
# NAME_UNAME	= libmlx_$(UNAME).a

# SRC	= mlx_init.c mlx_new_window.c mlx_pixel_put.c mlx_loop.c \
# 	mlx_mouse_hook.c mlx_key_hook.c mlx_expose_hook.c mlx_loop_hook.c \
# 	mlx_int_anti_resize_win.c mlx_int_do_nothing.c \
# 	mlx_int_wait_first_expose.c mlx_int_get_visual.c \
# 	mlx_flush_event.c mlx_string_put.c mlx_set_font.c \
# 	mlx_new_image.c mlx_get_data_addr.c \
# 	mlx_put_image_to_window.c mlx_get_color_value.c mlx_clear_window.c \
# 	mlx_xpm.c mlx_int_str_to_wordtab.c mlx_destroy_window.c \
# 	mlx_int_param_event.c mlx_int_set_win_event_mask.c mlx_hook.c \
# 	mlx_rgb.c mlx_destroy_image.c mlx_mouse.c mlx_screen_size.c \
# 	mlx_destroy_display.c

# OBJ_DIR = obj
# OBJ	= $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))
# CFLAGS	= -O3 -I$(INC)

# all	: $(NAME)

# $(OBJ_DIR)/%.o: %.c
# 	@mkdir -p $(OBJ_DIR)
# 	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# $(NAME)	: $(OBJ)
# 	ar -r $(NAME) $(OBJ)
# 	ranlib $(NAME)
# 	cp $(NAME) $(NAME_UNAME)

# check: all
# 	@test/run_tests.sh

# show:
# 	@printf "NAME  		: $(NAME)\n"
# 	@printf "NAME_UNAME	: $(NAME_UNAME)\n"
# 	@printf "CC		: $(CC)\n"
# 	@printf "CFLAGS		: $(CFLAGS)\n"
# 	@printf "SRC		:\n	$(SRC)\n"
# 	@printf "OBJ		:\n	$(OBJ)\n"

# clean	:
# 	rm -rf $(OBJ_DIR)/ $(NAME) $(NAME_UNAME) *~ core *.core

# .PHONY: all check show clean