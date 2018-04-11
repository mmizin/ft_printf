NAME = libftprintf.a
INCLUDES = libft.h
CC = gcc -Wall -Wextra -Werror
SRCS = f_check_letter_conversation.c \
		f_check.c \
		f_from_perc_to_perc.c \
		f_handelling_for_d_and_i_flags.c \
		f_itoa.c \
		f_no_perc_at_all.c \
		f_perc_C_big.c \
		f_perc_c_small.c \
		f_perc_d_small.c \
		f_perc_S_big.c \
		f_percent_s_small.c \
		f_sign.c \
		f_specifies_the_size_of_the_argument.c \
		f_wright_exact_length.c \
		ft_atoi.c \
		ft_printf.c \
		ft_strchr.c \
		ft_strlen.c \
		f_perc_x_X.c \
		f_reset_init.c \
		f_from_perc_to_perc.c \
		f_handl_o_O.c \
		f_handl_x_X.c \
		f_perc_p_small.c \
		f_perc_o_O.c \
		ft_itoa_base.c

all: $(NAME)

%.o:%.c
	$(CC) -I $(INCLUDES) -c $^

$(NAME): *.o
	@ar rc $(NAME) *.o
	@ranlib $(NAME)

clean:
	@/bin/rm -rf *.o *.out

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all

