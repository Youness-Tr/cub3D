CC = cc
NAME = cub3D
# B_NAME = cub3D_bomus
FSA = -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -lmlx_Linux -lXext -lX11 -lm
#------------------
SRC = main_cub.c
#Utils/
SRC += Utils/utils1.c Utils/substr.c Utils/split.c Utils/err.c
SRC += Utils/init.c
#Parsing/
SRC += Parsing/parser.c  Parsing/utils.c
#RayCasting/
SRC += RayCasting/raycaster.c
#Rendring/
SRC += Rendring/render2d.c Rendring/render3D.c
#Gnl/
SRC += Gnl/get_next_line.c Gnl/gnl_utils.c
#Glogic/
SRC += Glogic/playerMoves.c Glogic/Wall_Intersection.c
#------------------

OBJ = $(SRC:.c=.o)
# B_OBJ = $(B_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) $(CFLAGS) $(MLX_FLAGS)  -o $(NAME) $(FSA)
# bonus:$(B_NAME)

# $(B_NAME):$(B_OBJ)
# 	$(CC) $(CFLAGS) -o $(B_NAME) $(B_OBJ)
clean:
	@rm -rf $(OBJ) $(B_OBJ)

fclean: clean
	@rm -rf $(NAME) $(B_NAME)

re: fclean all
