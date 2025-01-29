NAME := cub3d

# Compilation
CC := cc -g
CFLAGS := -Wall -g
#MLX42FLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
LIBFT_INCLUDES := -I./lib/libft/include
MLX_INCLUDES := -I./lib/MLX42/include/MLX42
cub3d_INCLUDES := -I./include

INCLUDES = $(LIBFT_INCLUDES) $(MLX_INCLUDES) $(cub3d_INCLUDES)

# Directories
BUILD_DIR := bin
SRC_DIR := src
INC_DIR := include
LIBFT := lib/libft/libft.a
MLX42 = lib/MLX42/build/libmlx42.a
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# OS Spe
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX42FLAGS = -lglfw -lm -ldl -lX11 -lpthread
endif

ifeq ($(UNAME_S),Darwin)
    MLX42FLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

ifeq ($(OS),Windows_NT)
    CC := gcc
    CFLAGS := -Wall -Wextra -Werror
    MLX42FLAGS = -lglfw3 -lgdi32 -lopengl32
endif

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX42FLAGS) $(OBJS) $(LIBFT) $(MLX42) -o $(NAME)
	
$(LIBFT):
	$(MAKE) -C lib/libft

$(MLX42):
	cd lib/MLX42 && cmake -B build && cmake --build build -j4

clean:
	$(MAKE) -C lib/libft clean
	rm -rf $(BUILD_DIR)

fclean: clean
	$(MAKE) -C lib/libft fclean
	rm -f $(NAME)
	
re: fclean all

memcheck:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re $(LIBFT) $(MLX42)
