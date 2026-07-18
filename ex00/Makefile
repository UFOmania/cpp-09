NAME = btc

FLAGS = -Wall -Wextra -Werror 

SRC = BitcoinExchange.cpp main.cpp
OBJ = $(SRC:.o=.cpp)

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	c++ $(FLAGS) -c $@  -o $<


clean:
	rm  -f $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all