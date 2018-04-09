cmake_minimum_required(VERSION 3.9)
project(ft_printf)

set(CMAKE_CXX_STANDARD 11)

add_executable(ft_printf
        f_check.c
        f_check_letter_conversation.c
        f_from_perc_to_perc.c
        f_handelling_for_d_and_i_flags.c
        f_itoa.c
        f_no_perc_at_all.c
        f_perc_C_big.c
        f_perc_c_small.c
        f_perc_d_small.c
        f_perc_S_big.c
        f_percent_s_small.c
        f_sign.c
        f_wright_exact_length.c
        ft_atoi.c
        ft_printf.c
        ft_printf.h
        ft_strchr.c
        ft_strlen.c
        main.c
        f_specifies_the_size_of_the_argument.c f_perc_x_X.c)
