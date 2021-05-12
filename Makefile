PUSH_SWAP=push_swap
CHECKER=checker
FT_PRINTF=libftprintf
CC=gcc
CFLAGS= -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak
TEST_CFLAGS=-ggdb3 $(CFLAGS)
DEBUG_CFLAGS=-ggdb3 $(CFLAGS)
INC_PATH=-I./$(FT_PRINTF) -I./src -I./$(FT_PRINTF)/libft
LDFLAGS=-L./$(FT_PRINTF) -lftprintf -lm

COMMOM_FILES=								\
	src/parser/parse_numbers.c 				\
	src/utils/status.c 						\
	src/utils/math_utils.c					\
	src/parser/parse_instructions.c 		\
	src/parser/parse_flags.c 	   			\
	src/parser/parse_numbers.h 				\
	src/utils/defs.h 						\
	src/utils/status.h						\
	src/utils/math_utils.h					\
	src/parser/parse_instructions.h 		\
	src/parser/parse_flags.h 				\
	src/stack/stack_utils.c					\
	src/stack/stack.c 						\
	src/stack/stack_swap.c 					\
	src/stack/processor.c					\
	src/stack/processor_swap.c				\
	src/stack/processor_push.c				\
	src/stack/processor_rotate.c			\
	src/stack/processor_reverse_rotate.c	\
	src/stack/processor.h					\
	src/stack/stack.h						\
	src/stack/stack_utils.h					\

PUSH_SWAP_FILES= 							\
	src/push_swap/push_swap.c				\
	src/push_swap/insertion_sort.c			\
	src/push_swap/bucket_sort.c				\
	src/push_swap/special_cases_sort.c		\
	src/push_swap/utils.c					\
	src/push_swap/sorting_utils.c
	

PUSH_SWAP_INC_FILES= 						\
	src/push_swap/push_swap.h				\
	src/push_swap/special_cases_sort.h		\
	src/push_swap/insertion_sort.h			\
	src/push_swap/bucket_sort.h				\
	src/push_swap/utils.h					\
	src/push_swap/sorting_utils.h

CHECKER_FILES= 								\
	src/checker/checker.c 					\
	src/checker/verbose.c					\
	src/checker/write_result.c				\


CHECKER_INC_FILES=	 						\
	src/checker/checker.h					\
	src/checker/verbose.h					\
	src/checker/write_result.h				\


TEST_FILES=									\
	test/main.c 							\
	test/tests.c							\
	test/stack_test.c						\
	test/processor_test.c					\
	test/parser_test.c						\
	test/checker_test.c						\
	test/push_swap_test.c					\

all: $(FT_PRINTF) $(PUSH_SWAP) $(CHECKER)

$(PUSH_SWAP): $(FT_PRINTF) $(PUSH_SWAP_INC_FILES) $(PUSH_SWAP_FILES) $(COMMOM_FILES)
		$(CC) -O3 $(CFLAGS) $(INC_PATH) $(COMMOM_FILES) $(PUSH_SWAP_FILES) src/push_swap/main.c $(LDFLAGS) -o $@

$(CHECKER): $(FT_PRINTF) $(CHECKER_INC_FILES) $(CHECKER_FILES) $(COMMOM_FILES)
		$(CC) -O3 $(CFLAGS) $(INC_PATH) $(COMMOM_FILES) $(CHECKER_FILES) src/checker/main.c $(LDFLAGS) -o $@

$(FT_PRINTF):
	$(MAKE) -C ./$(FT_PRINTF)

test_run: test
	./tester
	./run_norminette.sh

test_integration: $(FT_PRINTF) $(PUSH_SWAP) $(CHECKER)
	./test/integration_test.py

test: $(FT_PRINTF) $(PUSH_SWAP) $(CHECKER) $(TEST_FILES)
	$(CC) $(TEST_CFLAGS) $(INC_PATH) $(COMMOM_FILES) $(CHECKER_FILES) $(PUSH_SWAP_FILES) $(TEST_FILES) $(LDFLAGS) -o tester

clean:
	$(MAKE) clean -C ./$(FT_PRINTF)

re: fclean all

fclean: clean
	$(MAKE) fclean -C ./$(FT_PRINTF)
	rm -f $(PUSH_SWAP)
	rm -f $(CHECKER)
	rm -f tester
	rm -f norminette_result
	rm -f result

.PHONY: all clean fclean re test libftprintf push_swap checker