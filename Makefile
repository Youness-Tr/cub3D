NAME = cub3d

SRC = main.c
SRC += Parsing/parser.c Parsing/utils.c gnl/get_next_line.c gnl/gnl_utils.c floodfill.c

all:
	# @gcc main.c -o cub3d
	gcc $(SRC) -o cub3d 
#-fsanitize=address -g3
clean:
	rm cub3d
