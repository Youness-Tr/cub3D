all:
	# @gcc main.c -lmlx -lXext -lX11 -o cub3d
	gcc main.c -Lmlx -lmlx_Linux -lXext -lX11 -lm  -o cub3d -fsanitize=address -g3
clean:
	rm cub3d