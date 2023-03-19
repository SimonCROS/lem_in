# Properties

NAME				:= lem-in

# Commands

override CC		:= gcc
override CFLAGS	:= -Wall -Wextra -Werror# -g3# -fsanitize=address

# Sources

override LIBFT		:= libft/libft.a

override SRCS		:=								\
				main.c								\
				algo.c								\
				bfs.c								\
				score.c								\
				print.c								\
				utils.c								\
				parsing.c							\
				parsing_utils.c						\
				debug.c								\

override HEADERS	:=								\
				lem_in.h							\

override HEADERS	:=								\
				$(addprefix includes/,$(HEADERS))	\
				libft/includes/libft.h				\

override OBJS		:= $(addprefix obj/, $(SRCS:.c=.o))

override OBJDIRS	:= $(sort $(dir $(OBJS)))

# Rules

all:		libft $(NAME)

obj/%.o:	src/%.c $(HEADERS) Makefile
			$(CC) $(CFLAGS) -c $< -o $@ -Iincludes -Ilibft/includes

$(OBJS):	| $(OBJDIRS)

$(OBJDIRS):
			mkdir -p $@

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT)
		
libft:
			$(MAKE) -C libft

clean:
			$(MAKE) -C libft clean
			rm -rf obj

fclean:
			$(MAKE) -C libft fclean
			rm -rf obj
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re libft
