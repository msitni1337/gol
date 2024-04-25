SRC = general.c input.c main.c utils.c
OBJ = $(SRC:.c=.o)
CC = cc
MLX_DIR = ./mlx

ifeq ($(OS), Linux)
	X11_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm
	MLX_LIB = $(MLX_DIR)/libmlx.a
else
	MLX_LIB =  $(MLX_DIR)/libmlx_Darwin.a
	MLXFLAGS =  -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	X11_FLAGS = -L/usr/X11/lib -lXext -lX11
endif

NAME = gol

all :	$(NAME)

%.o : %.c
	$(CC) -Imlx -c $< -o $@	

$(NAME): $(MLX_LIB) $(OBJ)
	$(CC) $(OBJ) $(MLXFLAGS) $(X11_FLAGS) -o $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean :
	rm -f $(OBJ)