# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 10:53:31 by emadriga          #+#    #+#              #
#    Updated: 2023/04/09 21:16:21 by jvacaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program's name
NAME	= webserv

# compiler
GCC		= clang++

FLAGS	= -Wall -Wextra -Werror $(VERSION) $(SANITIZE) -g -O3 -pedantic $(NAMESPACE) $(SHOW_CONS_DEST)

# compiling flags

# sanitize
SANITIZE =
# SANITIZE = -fsanitize=address

# version
VERSION = -std=c++98

# Namespace in use
NAMESPACE =

# Header files
INCLUDES_FILES =	network/fdlibc-network.hpp				\
					network/server/fdlibc-server.hpp		\
					network/server/AServer.hpp				\
					network/server/TestServer.hpp			\
					network/socket/fdlibc-socket.hpp		\
					network/socket/ASocket.hpp				\
					network/socket/BindSocket.hpp			\
					network/socket/ListenSocket.hpp			\
					network/socket/ConnectSocket.hpp		\
					parsing/request_header_parsing.hpp		\
					general.hpp

# Source and object files
SRC_FILES	= 	main.cpp								\
				network/server/AServer.cpp				\
				network/server/TestServer.cpp			\
				network/socket/ASocket.cpp				\
				network/socket/BindSocket.cpp			\
				network/socket/ListenSocket.cpp			\
				network/socket/ConnectSocket.cpp		\
				parsing/request_header_parsing.cpp		\
				utils.cpp

OBJ_FILES	= $(SRC_FILES:.cpp=.o)

# Folders
INC_DIR = ./src/
SRC_DIR = ./src/
OBJ_DIR = ./obj/
BUILD_DIR = ./gTest/build/

# Paths
INCLUDES = $(addprefix $(INC_DIR), $(INCLUDES_FILES))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# all rule
all: obj $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)network/
	@mkdir -p $(OBJ_DIR)network/socket/
	@mkdir -p $(OBJ_DIR)network/server/
	@mkdir -p $(OBJ_DIR)parsing/
$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp $(INCLUDES)
	@$(GCC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

# Compiling
$(NAME): $(OBJ)
	@echo "\033[0;33mCompiling... Wait a sec.\033[0;39m"
	@$(GCC) $(OBJ) $(FLAGS) -lm -o $(NAME)
	@echo "\033[0;32m$(NAME) generated!\033[0;37m"

# clean rule
clean:
			@rm -Rf $(OBJ_DIR)
			@rm -Rf $(BUILD_DIR)
			@echo "\033[1;34m[INFO]\033[0m Objects removed!"

# fclean rule
fclean:		clean
			@rm -f $(NAME)
			@echo "$(NAME) removed!"
 
# re rule
re:			fclean all

# gTest rule
gTest:
			cmake -S ./gTest -B $(BUILD_DIR)
			cmake --build $(BUILD_DIR)

# phony
.PHONY:		all clean fclean re gTest
