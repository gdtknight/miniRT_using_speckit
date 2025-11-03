CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include -I lib/minilibx
LDFLAGS = -L lib/minilibx -lmlx -framework OpenGL -framework AppKit

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

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJS)
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
