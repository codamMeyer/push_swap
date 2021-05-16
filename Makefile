PUSH_SWAP=push_swap
CHECKER=checker
FT_PRINTF=libftprintf
CC=gcc
CFLAGS= -O3 -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak
TEST_CFLAGS=-ggdb3 $(CFLAGS)
INC_PATH=-I./$(FT_PRINTF) -I./src -I./$(FT_PRINTF)/libft
LDFLAGS=-L./$(FT_PRINTF) -lftprintf -lm

COMMOM_SRC_FILES=							\
	src/parser/parse_numbers.c 				\
	src/utils/status.c 						\
	src/utils/math_utils.c					\
	src/parser/parse_instructions.c 		\
	src/parser/parse_flags.c 	   			\
	src/stack/stack_utils.c					\
	src/stack/stack.c 						\
	src/stack/stack_swap.c 					\
	src/stack/processor.c					\
	src/stack/processor_swap.c				\
	src/stack/processor_push.c				\
	src/stack/processor_rotate.c			\
	src/stack/processor_reverse_rotate.c

COMMOM_INC_FILES=							\
	src/parser/parse_numbers.h 				\
	src/utils/defs.h 						\
	src/utils/status.h						\
	src/utils/math_utils.h					\
	src/utils/instructions.h				\
	src/parser/parse_instructions.h 		\
	src/parser/parse_flags.h 				\
	src/stack/processor.h					\
	src/stack/stack.h						\
	src/stack/stack_utils.h					\


PUSH_SWAP_SRC_FILES= 						\
	src/push_swap/push_swap.c				\
	src/push_swap/insertion_sort.c			\
	src/push_swap/bucket_sort.c				\
	src/push_swap/bucket_sort_utils.c		\
	src/push_swap/bucket.c					\
	src/push_swap/special_cases_sort.c		\
	src/push_swap/utils.c					\
	src/push_swap/sorting_utils.c
	

PUSH_SWAP_INC_FILES= 						\
	src/push_swap/push_swap.h				\
	src/push_swap/special_cases_sort.h		\
	src/push_swap/insertion_sort.h			\
	src/push_swap/bucket_sort.h				\
	src/push_swap/bucket_sort_utils.h		\
	src/push_swap/bucket.h					\
	src/push_swap/utils.h					\
	src/push_swap/sorting_utils.h

CHECKER_SRC_FILES= 							\
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

PUSH_SWAP_OBJS = $(PUSH_SWAP_SRC_FILES:.c=.o)
CHECKER_OBJS = $(CHECKER_SRC_FILES:.c=.o)
COMMON_OBJS = $(COMMOM_SRC_FILES:.c=.o)

all: $(FT_PRINTF) $(PUSH_SWAP) $(CHECKER)

$(PUSH_SWAP): $(PUSH_SWAP_OBJS) $(COMMON_OBJS)
		$(CC) $(CFLAGS) $(INC_PATH) src/push_swap/main.c -o $@ $^ $(LDFLAGS)

$(CHECKER): $(CHECKER_OBJS) $(COMMON_OBJS)
		$(CC) $(CFLAGS) $(INC_PATH) src/checker/main.c -o $@ $^ $(LDFLAGS)

$(FT_PRINTF):
	$(MAKE) -C ./$(FT_PRINTF)

%.o: %.c 
		$(CC) $(CFLAGS) $(INC_PATH) -c -o $@ $< 

test_run: test
	./tester
	./run_norminette.sh

test_integration: $(FT_PRINTF) $(PUSH_SWAP) $(CHECKER)
	./test/integration_test.py

test: $(FT_PRINTF) $(PUSH_SWAP) $(CHECKER) $(TEST_FILES)
	$(CC) $(TEST_CFLAGS) $(INC_PATH) $(COMMON_OBJS) $(CHECKER_OBJS) $(PUSH_SWAP_OBJS) $(TEST_FILES) -o tester $(LDFLAGS)

clean:
	$(MAKE) clean -C ./$(FT_PRINTF)
	rm -f $(PUSH_SWAP_OBJS)
	rm -f $(CHECKER_OBJS)
	rm -f $(COMMON_OBJS)

re: fclean all

fclean: clean
	$(MAKE) fclean -C ./$(FT_PRINTF)
	rm -f $(PUSH_SWAP)
	rm -f $(CHECKER)
	rm -f tester
	rm -f norminette_result
	rm -f result

.PHONY: all clean fclean re test libftprintf 
