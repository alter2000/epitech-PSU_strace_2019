##
## EPITECH PROJECT, 2019
## cpp_rush3_2019
## File description:
## automated desc ftw
##

NAME = strace

SRC = \
	  ./args.c \
	  ./helpers.c \
	  ./logic.c \
	  ./main.c \
	  ./prints.c \

CPL = gcc
CFLAGS = -Wextra -Wall -I.
LDFLAGS =
DFLAGS = \
	  -fsanitize=address \
	  -fsanitize=alignment \
	  -fsanitize=enum \
	  -fsanitize=undefined \
	  -fsanitize=nullability \
	  -Wextra -Wall -I. -g

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CPL) -o $(NAME) $(OBJ) $(LDFLAGS)

debug: $(SRC)
	clang -o $(NAME) $(SRC) $(DFLAGS) $(LDFLAGS)

clean:
	@$(foreach var, $(OBJ), if [ -e $(var) ] ; then rm -f $(var) ; fi;)
	@rm -f vgcore.*

fclean: clean
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

%.o: %.c
	$(CPL) $(CFLAGS) -o $@ -c $<

.PHONY: all clean fclean re
