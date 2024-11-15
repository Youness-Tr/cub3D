CC = cc
NAME = cub3D_bonus
# B_NAME = cub3D_bomus
FSA = 
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -fsanitize=address -g3 #-Lmlx -lmlx_Linux -lXext -lX11 -lm
#------------------
SRC = main_cub_bonus.c 
#Utils/
SRC += Utils/utils1_bonus.c Utils/substr_bonus.c  Utils/split_bonus.c  Utils/err_bonus.c  
SRC += Utils/init_bonus.c 
#Parsing/
SRC += Parsing/parser_bonus.c   Parsing/utils_bonus.c  Parsing/tool_bonus.c  Parsing/utils2_bonus.c Parsing/utils3_bonus.c
#RayCasting/
SRC += RayCasting/raycaster.c RayCasting/raytools.c
#Rendring/
SRC += Rendring/render2d.c Rendring/render3D.c Rendring/render_utils.c
#Gnl/
SRC += Gnl/get_next_line.c Gnl/gnl_utils.c
#Glogic/
SRC += Glogic/playerMoves.c Glogic/Wall_Intersection.c
#Init/
SRC += Init/init1.c Init/init.c
#------------------

OBJ = $(SRC:.c=.o)
# B_OBJ = $(B_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) $(CFLAGS) $(MLX_FLAGS)  -o $(NAME)
# bonus:$(B_NAME)

# $(B_NAME):$(B_OBJ)
# 	$(CC) $(CFLAGS) -o $(B_NAME) $(B_OBJ)
clean:
	@rm -rf $(OBJ) $(B_OBJ)

fclean: clean
	@rm -rf $(NAME) $(B_NAME)

re: fclean all
