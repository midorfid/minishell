NAME := libftprintf.a
SRC = 	ft_printf.c			\
		ft_printf_ptr.c		\
		ft_printf_hex.c		\
		ft_printf_unsign.c	\
		ft_itoa.c			\
		utils.c				\

OBJFILES = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJFILES)
	ar -rcs $(NAME) $(OBJFILES)

%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
