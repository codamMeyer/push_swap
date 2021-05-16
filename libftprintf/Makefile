CC=gcc
CFLAGS= -Wall -Werror -Wextra

NAME=libftprintf
CREATE_LIB=ar rcs

INC_PATH=-I./

HEADER_FILES = 					\
	ft_printf.h 				\
	inc/ft_printf_helpers.h 	\
	inc/handle_char.h			\
	inc/handle_hex.h 			\
	inc/handle_int.h 			\
	inc/handle_int_helpers.h 	\
	inc/handle_modifier.h 		\
	inc/handle_str.h 			\
	inc/handle_percent.h 		\
	inc/int_to_hex.h		 	\
	inc/int_to_hex_helpers.h	\
	inc/math.h 					\
	inc/padding.h 				\
	inc/t_flag.h 				\
	inc/utils.h 				\

SRC_FILES= \
	ft_printf.c 				\
	src/ft_printf_helpers.c 	\
	src/handle_char.c			\
	src/handle_hex.c 			\
	src/handle_int.c 			\
	src/handle_int_helpers.c 	\
	src/handle_modifier.c 		\
	src/handle_str.c 			\
	src/handle_percent.c 		\
	src/int_to_hex.c		 	\
	src/int_to_hex_helpers.c	\
	src/math.c 					\
	src/padding.c 				\
	src/t_flag.c 				\
	src/utils.c 				\

SRC_OBJ = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): libft $(NAME).a

$(NAME).a: $(SRC_OBJ)
	cp ./libft/libft.a $(NAME).a
	ar rc $(NAME).a $(SRC_OBJ)

%.o: %.c $(HEADER_FILES)
	$(CC) $(INC_PATH) -c $(CFLAGS) -o $@ $<

clean:
	$(MAKE) clean -C ./libft
	rm -f $(SRC_OBJ)

re: fclean all

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME).a

libft:
	$(MAKE) -C ./libft

.PHONY: all clean fclean re test libft run
