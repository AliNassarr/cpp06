CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = identify

SRCS = main.cpp Base.cpp Identify.cpp
OBJS = $(SRCS:.cpp=.o)

HEADERS = Base.hpp Identify.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
