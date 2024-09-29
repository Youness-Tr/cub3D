SRC = main_cub.c  raycaster.c  #main.c render.c move.c
SRC += Utils/utils1.c Utils/substr.c Utils/split.c Utils/err.c
SRC += Utils/init.c
SRC += gnl/get_next_line.c gnl/gnl_utils.c

all:
	# @gcc main.c -lmlx -lXext -lX11 -o cub3d
	gcc $(SRC) -Lmlx -lmlx_Linux -lXext -lX11 -lm  -o cub3D #-fsanitize=address -g3
clean:
	rm cub3D