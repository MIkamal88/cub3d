NAME		= cub3D
LIBFT		=libft.a

OBJ_PATH = ./build/
SRC_PATH = ./src/
INCLUDE = ./include/
LIB_PATH = ./libs/
FT_PATH = $(LIB_PATH)libft/
LIBFT = libft.a

OS	= $(shell uname)
ifeq ($(OS), Linux)
	MLX = libmlx_Linux.a
	MLX_PATH = $(LIB_PATH)mlx/linux/
	CFI_MLX		= -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz -o
else ifeq ($(OS), Darwin)
	MLX = mlx_mac
	MLX_PATH = $(LIB_PATH)mlx/mac/
	CFI_MLX = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit -o
else
	$(error Unsupported OS: $(OS))
endif

CC				= gcc -g
CF				= -Wall -Wextra -Werror #-fsanitize=address
CFI					= -I$(INCLUDE)
CFI_FT		= -L$(FT_PATH) -lft

SRC			= main.c\
					utils.c\
					errors.c\
					destroy.c\
					keybinds.c\
					mapping.c\
					checker.c\
					ceiling_floor.c\
					grid.c\
					pixels.c\
					lines.c\
					minimap.c\
					text.c\

VPATH		= $(SRC_PATH)\
					$(SRC_PATH)utils/\
					$(SRC_PATH)rendering/\
					$(SRC_PATH)parsing/\

OBJ			= $(addprefix $(OBJ_PATH), $(notdir $(SRC:.c=.o)))

RM	= rm -rf

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CF) $(CFI) -c $< -o $@

$(NAME):	ANNOUNCE $(OBJ)
	@printf "$(BL)Objects ready!$(RC)\n"
	@printf "\n$(YE)Compiling MLX...$(RC)\n"
	@make --no-print-directory -sC $(MLX_PATH)
	@printf "$(BL)MLX created!$(RC)\n"
	@printf "\n$(YE)Compiling Libft...$(RC)\n"
	@make --no-print-directory -sC $(FT_PATH)
	@printf "$(BL)Libft created!$(RC)\n\n"
	@printf "$(YE)Compiling CUB3D Executable...$(RC)\n"
	$(CC) $(CF) $(OBJ) $(CFI) $(CFI_FT) $(CFI_MLX) $(NAME)
	@printf "\n$(GR)Program ready!$(RC)\n"

all: $(NAME)

ANNOUNCE:
	@printf "$(YE)Generating Object Files...$(RC)\n"

re: fclean all

clean:
	@printf "$(RE)Deleting Objects...$(RC)\n"
	@make --no-print-directory -C $(FT_PATH) clean
	@make --no-print-directory -C $(MLX_PATH) clean
	@$(RM) $(OBJ) $(OBJ_PATH)
	@printf "$(GR)Done!$(RC)\n"

fclean: clean
	@printf "$(RE)Deleting Executable...$(RC)\n"
	@make --no-print-directory -C $(FT_PATH) fclean
	@$(RM) $(NAME)
	@printf "$(GR)Done!$(RC)\n\n"

leak:			all
				valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) ./maps/test.cub

leak2:			all
				valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) ./maps/g_map02.cub

debug:			all
				lldb-16 ./$(NAME) ./maps/test.cub

.PHONY:		all clean fclean re

GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[0;33m
CY	= \033[36;1m
BL	= \033[94m
RC	= \033[0m

# $(LINUX):	ANNOUNCE $(OFILES)
# 	$(CC) $(CFLAGS) $(OFILES) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(LINUX)
#
#$(MAC):	ANNOUNCE $(OFILES)
#	$(CC) $(CFLAGS) $(OFILES) -Lmlx_mac -lmlx -framework OpenGL -framework AppKit -o $(MAC)
