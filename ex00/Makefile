NAME		=	btc
CXX			=	c++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98 -MMD -MP

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	inc/

SRC_FILES	=	main.cpp BitcoinExchange.cpp
OBJ_FILES	=	$(SRC_FILES:.cpp=.o)
DEP_FILES	=	$(OBJ_FILES:.o=.d)

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
DEP			=	$(addprefix $(OBJ_DIR), $(DEP_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
	fi

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re