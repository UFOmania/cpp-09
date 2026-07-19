NAME = RPN

FLAGS = -Wall -Wextra -Werror

SRC = RPN.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	c++ $(FLAGS) -c $<  -o $@


clean:
	rm  -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all