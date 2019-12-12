# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/12 18:46:50 by mmeleage          #+#    #+#              #
#    Updated: 2019/12/12 18:48:14 by mmeleage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIB_NAME = libft/libft.a

SRCS = ft_printf_f.c \
	ft_printf_h.c \
	ft_printf_hh.c \
	ft_printf_hhoux.c \
	ft_printf_houx.c \
	ft_printf_l.c \
	ft_printf_lf.c \
	ft_printf_ll.c \
	ft_printf_lloux.c \
	ft_printf_loux.c \
	ft_printf_oux.c \
	ft_printf_p.c \
	ft_printf.c \
	f_add.c \
	f_int_fract.c \
	f_multiply_divide.c \
	fill_flags_sizes.c \
	fill_num_funcs.c \
	get_arg.c \
	define_symbols.c \
	print_flags.c \
	spaces_to_width.c \
	libft/ft_memset.c \
	libft/ft_bzero.c \
	libft/ft_memcpy.c \
	libft/ft_memccpy.c \
	libft/ft_memmove.c \
	libft/ft_memchr.c \
	libft/ft_memcmp.c \
	libft/ft_strlen.c \
	libft/ft_strdup.c \
	libft/ft_strcpy.c \
	libft/ft_strncpy.c \
	libft/ft_strcat.c \
	libft/ft_strncat.c \
	libft/ft_strlcat.c \
	libft/ft_strchr.c \
	libft/ft_strrchr.c \
	libft/ft_strstr.c \
	libft/ft_strnstr.c \
	libft/ft_strcmp.c \
	libft/ft_strncmp.c \
	libft/ft_atoi.c \
	libft/ft_isalpha.c \
	libft/ft_isdigit.c \
	libft/ft_isalnum.c \
	libft/ft_isascii.c \
	libft/ft_isprint.c \
	libft/ft_toupper.c \
	libft/ft_tolower.c \
	libft/ft_memalloc.c \
	libft/ft_memdel.c \
	libft/ft_strnew.c \
	libft/ft_strdel.c \
	libft/ft_strclr.c \
	libft/ft_striter.c \
	libft/ft_striteri.c \
	libft/ft_strmap.c \
	libft/ft_strmapi.c \
	libft/ft_strequ.c \
	libft/ft_strnequ.c \
	libft/ft_strsub.c \
	libft/ft_strjoin.c \
	libft/ft_strtrim.c \
	libft/ft_strsplit.c \
	libft/ft_putchar.c \
	libft/ft_putstr.c \
	libft/ft_putendl.c \
	libft/ft_itoa.c \
	libft/ft_putnbr.c \
	libft/ft_putchar_fd.c \
	libft/ft_putstr_fd.c \
	libft/ft_putendl_fd.c \
	libft/ft_putnbr_fd.c \
	libft/ft_lstnew.c \
	libft/ft_lstdelone.c \
	libft/ft_lstdel.c \
	libft/ft_lstadd.c \
	libft/ft_lstiter.c \
	libft/ft_lstmap.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c $(HEADS)
	gcc -Wall -Werror -Wextra -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIB_NAME)
	
re: fclean all