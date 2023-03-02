NAME	=	cub3D

SRCS	=	ft_isdigit.c ft_isalpha.c ft_atoi.c ft_split.c ft_strrchr.c ft_strjoin.c tstt.c get_next_line_utils.c get_next_line.c  parsing.c parsing_hlp.c parsing_hlp1.c parsing_hlp2.c parsing_hlp3.c main.c

OBJCT	=	${SRCS:.c=.o}

RM		=	rm -f

CC		=	gcc  -fsanitize=address  -Wall -Wextra -Werror

all : $(NAME)

all : $(NAME)
$(NAME):$(SRCS)
	$(CC) $(SRCS) -lmlx -framework OpenGL -framework AppKit -o  $(NAME)

clean :
	${RM} ${OBJCT}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY:		all clean fclean re 