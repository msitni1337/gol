SRC = general.c main.c

OBJ = $(SRC:.c=.o)

CC = cc

LDFLAGS = -L. -lmlx -L/usr/lib -lXext -lX11 -lm 

NAME = gol

MLX = libmlx.a

.PHONY : re fclean all clean

all : $(NAME)

%.o : %.c
	$(CC) $< -c -o $@

$(NAME): $(MLX) $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

