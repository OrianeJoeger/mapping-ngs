CC	= g++

RM	= rm -rf

#TODO
INC = include/

CFLAGS	= -Wall -ansi -pedantic

SRCS	= $(shell find src -type f -name "*.cpp")

HEADERS	= $(shell find include -type f -name "*.h")

OBJS	= $(SRCS:.cpp=.o)

NAME	= prog_exec

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

archive: $(HEADERS) $(SOURCES) arch_makefile
	tar -czf $(PROG).tgz $^

.PHONY: all re clean fclean archive