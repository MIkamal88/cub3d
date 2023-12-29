NAME	= cub3d
LIBFT	=libft.a

OBJ_PATH = ./obj/
SRC_PATH = ./src/
INCLUDE_PATH = ./include/
LIB_PATH = ./libs/
FT_PATH = $(LIB_PATH)libft/
LIBFT = libft.a

OS	= $(shell uname)
ifeq ($(OS), Linux)
	MLX = libmlx_Linux.a
	MLX_PATH = $(LIB_PATH)mlx/linux/
# else ifeq ($(OS), Darwin)
# 	MLX = mlx_mac
#		MLX_PATH = $(LIB_PATH)mlx/mac/
else
	$(error Unsupported OS: $(OS))
endif

CC	= gcc
CF	= -Wall -Wextra -Werror -g
CFI	= -I$(INCLUDE)
CFI_FT	= -L$(FT_PATH) -lft
CFI_MLX	= -L$(MLX_PATH) -lmlx -lXext -lX11

SRC	= main.c\

VPATH	= $(SRC_PATH)\

OBJ	= $(addprefix $(OBJ_PATH), $(notdir $(SRC:.c=.o)))

RM	= rm -rf

$(OBJ_PATH)%.o: %.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CF) $(CFI) -c $< -o $@

$(NAME):	ANNOUNCE $(OBJ)
	@printf "$(GR)Objects ready!$(RC)\n"
	@printf "\n$(CY)Compiling MLX...$(RC)\n"
	@make --no-print-directory -C $(MLX_PATH)
	@printf "$(GR)MLX created!$(RC)\n\n"
	@printf "\n$(CY)Compiling Libft...$(RC)\n"
	@make --no-print-directory -C $(FT_PATH)
	@printf "$(GR)Libft created!$(RC)\n\n"		
	@printf "$(CY)Compiling CUB3D Executable...$(RC)\n"
	$(CC) $(CF) $(OBJ) $(CFI) $(CFI_FT) $(CFI_MLX) -lm -lz -o $(NAME) 
	@printf "$(GR)Done!$(RC)\n"

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
	@printf "$(GR)Done!$(RC)\n"

leak:			all			
				valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

.PHONY:		all clean fclean re

GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m
# $(LINUX):	ANNOUNCE $(OFILES)
# 	$(CC) $(CFLAGS) $(OFILES) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(LINUX)
#
#$(MAC):	ANNOUNCE $(OFILES)
#	$(CC) $(CFLAGS) $(OFILES) -Lmlx_mac -lmlx -framework OpenGL -framework AppKit -o $(MAC)
