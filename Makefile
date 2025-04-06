NAME := cub3D

# Compilation
CC := cc
CFLAGS := -Wall -Werror -Wextra
FLAGS += -g3 -fsanitize=address
LIBFT_INCLUDES := -I./lib/libft/include
MLX_INCLUDES := -I./lib/MLX42/include/MLX42
cub3d_INCLUDES := -I./include

INCLUDES = $(LIBFT_INCLUDES) $(MLX_INCLUDES) $(cub3d_INCLUDES)

# Directories
BUILD_DIR := bin
SRC_DIR := src
EXEC_DIR := $(SRC_DIR)/execution
PARS_DIR := $(SRC_DIR)/parsing
SET_DIR := $(SRC_DIR)/set_up
UTL_DIR := $(SRC_DIR)/utils

MAIN_SRC := main.c
EXEC_SRC := calcs.c key_moves.c launch.c path.c render.c minimap.c
PARS_SRC := handle_map.c input.c map_validation.c parse_color.c parse_file.c \
			parse_texture.c player.c path_checker.c extract_elements.c \
			populate_grid.c map_properties.c map_validation_II.c \
			split.c extract_fc.c extract_text.c map_padding.c \
			unpadded_map_validation.c
SET_SRC := fill_and_colors.c set_position.c set_up.c
UTL_SRC := error_handling.c init.c test_print.c 

INC_DIR := include
LIBFT := lib/libft/libft.a
MLX42 = lib/MLX42/build/libmlx42.a
SRCS := $(addprefix $(SRC_DIR)/, $(MAIN_SRC)) \
		$(addprefix $(EXEC_DIR)/, $(EXEC_SRC)) \
		$(addprefix $(PARS_DIR)/, $(PARS_SRC)) \
		$(addprefix $(SET_DIR)/, $(SET_SRC)) \
		$(addprefix $(UTL_DIR)/, $(UTL_SRC))

OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# OS Specific
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

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX42FLAGS) $(OBJS) $(LIBFT) $(MLX42) -o $(NAME)

$(LIBFT):
	$(MAKE) -C lib/libft

$(MLX42): lib/MLX42/CMakeLists.txt lib/MLX42/src/*.c
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

.PHONY: all clean fclean re
