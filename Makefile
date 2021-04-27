PUSH_SWAP=push_swap
CHECKER=checker
LIBFT=libft
CC=gcc
CFLAGS= -Wall -Wextra -Werror #-fsanitize=address -fsanitize=leak
TEST_CFLAGS=-ggdb3 $(CFLAGS) #-fsanitize=address -fsanitize=leak
DEBUG_CFLAGS=-ggdb3 $(CFLAGS)
INC_PATH=-I./$(LIBFT) -I./src
LDFLAGS=-L./$(LIBFT) -lft

PUSH_SWAP_FILES= 							\
	src/push_swap/push_swap.c				\
	src/parser/parse_numbers.c 				\

PUSH_SWAP_INC_FILES= 						\
	src/push_swap/push_swap.h				\
	src/parser/parse_numbers.h 				\
	src/utils/defs.h 						\


CHECKER_FILES= 								\
	src/checker/stack.c 					\
	src/checker/stack_swap.c 				\
	src/checker/checker.c 					\
	src/checker/processor.c					\
	src/checker/processor_swap.c			\
	src/checker/processor_push.c			\
	src/checker/processor_rotate.c			\
	src/checker/processor_reverse_rotate.c	\
	src/parser/parse_numbers.c 				\
	src/parser/parse_instructions.c 		\

CHECKER_INC_FILES=	 					\
	src/checker/stack.h					\
	src/checker/checker.h				\
	src/checker/processor.h				\
	src/utils/defs.h					\
	src/parser/parse_numbers.h 			\
	src/parser/parse_instructions.h 	\


TEST_FILES=					\
	test/main.c 			\
	test/stack_test.c		\
	test/processor_test.c	\
	test/parser_test.c		\
	test/checker_test.c		\

all: $(LIBFT) $(PUSH_SWAP) $(CHECKER)

$(PUSH_SWAP): $(PUSH_SWAP_INC_FILES) $(PUSH_SWAP_FILES)
		$(CC) -O3 $(CFLAGS) $(INC_PATH) $(PUSH_SWAP_FILES) src/push_swap/main.c $(LDFLAGS) -o $(PUSH_SWAP)

$(CHECKER): $(CHECKER_INC_FILES) $(CHECKER_FILES)
		$(CC) -O3 $(CFLAGS) $(INC_PATH) $(CHECKER_FILES) src/checker/main.c $(LDFLAGS) -o $(CHECKER)

$(LIBFT):
	$(MAKE) -C ./$(LIBFT)


test_run: test
	./tester
	./run_norminette.sh

test: $(LIBFT) $(CHECKER_INC_FILES) $(CHECKER_FILES) $(TEST_FILES)
	$(CC) $(TEST_CFLAGS) $(INC_PATH) $(CHECKER_FILES) $(TEST_FILES) $(LDFLAGS) -o tester

clean:
	$(MAKE) clean -C ./$(LIBFT)

re: fclean all

fclean: clean
	$(MAKE) fclean -C ./$(LIBFT)
	rm -f $(PUSH_SWAP)
	rm -f $(CHECKER)
	rm -f tester

.PHONY: all clean fclean re test libft push_swap checker