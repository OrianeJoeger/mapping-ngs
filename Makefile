CC	= g++

RM	= rm -rf

INC = include/

CFLAGS	= -Wall -ansi -pedantic

SRCS	= $(shell find ./src -type f -name "*.cpp") main.cpp

HEADERS	= $(shell find ./include -type f -name "*.h")

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
	$(RM) $(OBJS)

archive: re
	tar -czf $(NAME).tar.gz $(HEADERS) $(SRCS) $(NAME)

.PHONY: all re clean fclean archive