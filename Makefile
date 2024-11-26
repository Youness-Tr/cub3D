CC = cc
NAME = cub3D
BONUS_NAME = cub3D_bonus
FSA =
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -lmlx_Linux -lXext -lX11 -lm -fsanitize=address -g3 #-Lmlx -lmlx -framework OpenGL -framework AppKit
#------------------
SRC = mandatory/main_cub.c
SRC_B = bonus/main_cub_bonus.c
#Utils/
SRC += mandatory/Utils/utils1.c mandatory/Utils/substr.c mandatory/Utils/split.c mandatory/Utils/err.c
SRC += mandatory/Utils/init.c mandatory/Utils/strdup.c
SRC_B += bonus/Utils/utils1_bonus.c bonus/Utils/substr_bonus.c  bonus/Utils/split_bonus.c  bonus/Utils/err_bonus.c
SRC_B += bonus/Utils/strdup_bonus.c
#Parsing/
SRC += mandatory/Parsing/parser.c  mandatory/Parsing/utils.c mandatory/Parsing/tool.c mandatory/Parsing/utils2.c mandatory/Parsing/utils3.c
SRC_B += bonus/Parsing/parser_bonus.c   bonus/Parsing/utils_bonus.c  bonus/Parsing/tool_bonus.c  bonus/Parsing/utils2_bonus.c bonus/Parsing/utils3_bonus.c
#RayCasting/
SRC += mandatory/RayCasting/raycaster.c mandatory/RayCasting/raytools.c
SRC_B += bonus/RayCasting/raycaster_bonus.c  bonus/RayCasting/raytools_bonus.c
#Rendring/
SRC += mandatory/Rendring/render2d.c mandatory/Rendring/render3D.c mandatory/Rendring/render_utils.c
SRC_B += bonus/Rendring/render2d_bonus.c bonus/Rendring/render3D_bonus.c bonus/Rendring/render_utils_bonus.c
#Gnl/
SRC += mandatory/Gnl/get_next_line.c mandatory/Gnl/gnl_utils.c
SRC_B += bonus/Gnl/get_next_line.c bonus/Gnl/gnl_utils.c
#Glogic/
SRC += mandatory/Glogic/playerMoves.c mandatory/Glogic/Wall_Intersection.c
SRC_B += bonus/Glogic/playerMoves_bonus.c bonus/Glogic/Wall_Intersection_bonus.c
SRC_B += bonus/Glogic/elements.c bonus/Glogic/events.c
#Init/
SRC += mandatory/Init/init1.c mandatory/Init/init.c
SRC_B += bonus/Init/init1_bonus.c bonus/Init/init_bonus.c bonus/Init/init_textures.c
#------------------
SRC += mandatory/Leaks/free_all.c mandatory/Leaks/garbedge.c
SRC_B += bonus/Leaks/free_all.c bonus/Leaks/garbedge.c

OBJ = $(SRC:.c=.o)
B_OBJ = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) $(CFLAGS) $(MLX_FLAGS)  -o $(NAME)

bonus:$(BONUS_NAME)

$(BONUS_NAME):$(B_OBJ)
	$(CC) $(SRC_B) $(CFLAGS) $(MLX_FLAGS) -o $(BONUS_NAME)

clean:
	@rm -rf $(OBJ) $(B_OBJ)

fclean: clean
	@rm -rf $(NAME) $(BONUS_NAME)

re: fclean all
