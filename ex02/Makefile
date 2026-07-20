NAME = PmergeMe

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3


SRC = PmergeMe.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp PmergeMe.hpp
	c++ $(FLAGS) -c $<  -o $@


clean:
	rm  -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all