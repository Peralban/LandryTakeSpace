##
## EPITECH PROJECT, 2023
## Nanotekspice
## File description:
## Makefile
##

SRC	=	AComponent.cpp	\
		AdvancedComponents.cpp	\
		BasicGates.cpp	\
		GatesComponents.cpp	\
		ParseFile.cpp	\
		SpecialComponents.cpp	\
		NanotekSpice.cpp	\
		Main.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	nanotekspice

CXXFLAGS	=	-Wall -Wextra -Wshadow -I./include

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
