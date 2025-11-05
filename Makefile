CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include

# OS detection
UNAME := $(shell uname -s)

# Platform-specific settings
ifeq ($(UNAME), Darwin)
	# macOS
	MLX_DIR = lib/minilibx
	MLX_FLAGS = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	CFLAGS += -I $(MLX_DIR)
else ifeq ($(UNAME), Linux)
	# Linux
	MLX_DIR = lib/minilibx-linux
	MLX_FLAGS = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm
	CFLAGS += -I $(MLX_DIR)
else
	# Default to Linux
	MLX_DIR = lib/minilibx-linux
	MLX_FLAGS = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm
	CFLAGS += -I $(MLX_DIR)
endif

LDFLAGS = $(MLX_FLAGS)

SRC_DIR = src
LIB_VEC_DIR = src/lib/vec3
LIB_FT_DIR = src/lib/libft
PARSER_DIR = src/parser
RENDERER_DIR = src/renderer
TEST_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(LIB_VEC_DIR)/*.c) \
       $(wildcard $(LIB_FT_DIR)/*.c) \
       $(wildcard $(PARSER_DIR)/*.c) \
       $(wildcard $(RENDERER_DIR)/*.c)

OBJS = $(SRCS:.c=.o)

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)

CORE_OBJS = $(filter-out $(SRC_DIR)/main.o, $(OBJS))

NAME = miniRT
TEST_NAME = miniRT_test

.PHONY: all clean fclean re test info

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME) for $(UNAME)..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

test: $(TEST_NAME)
	./$(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS) $(CORE_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_NAME) $^ $(LDFLAGS)

info:
	@echo "Operating System: $(UNAME)"
	@echo "MLX Directory: $(MLX_DIR)"
	@echo "Compiler Flags: $(CFLAGS)"
	@echo "Linker Flags: $(LDFLAGS)"
