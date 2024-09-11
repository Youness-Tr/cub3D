all:
	gcc main.c -lmlx -lXext -lX11 -o cub3d
clean:
	rm cub3d