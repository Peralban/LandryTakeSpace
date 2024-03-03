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
		main.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	nanotekspice

CXXFLAGS	=	-Wall -Wextra -Wshadow -I./include

TESTSRC	=	$(filter-out main.cpp, $(SRC)) \
			Test/Test_main.cpp				\
			Test/TestParsing.cpp			\
			Test/TestComponents.cpp			\


all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

tests_run:
	g++ -o unit_tests $(TESTSRC) $(CXXFLAGS) --coverage -lcriterion
	./unit_tests
