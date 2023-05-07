# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 10:53:31 by emadriga          #+#    #+#              #
#    Updated: 2023/05/06 09:58:18 by emadriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program's name
NAME	= webserv

# compiler
GCC		= clang++

FLAGS	= -Wall -Wextra -Werror $(VERSION) $(SANITIZE) -g3  -pedantic $(NAMESPACE) $(SHOW_CONS_DEST)

# compiling flags

# sanitize
#SANITIZE =
SANITIZE = -fsanitize=address

# version
VERSION = -std=c++98 -MMD

# Namespace in use
NAMESPACE =

# Header files
INCLUDES_FILES =	utils/log.hpp							\
					network/server.hpp						\
					conf/conf.hpp							\
					conf/serverconf.hpp						\
					conf/location.hpp						\
					responses/Filetypes.hpp					\
					responses/responses.hpp					\
					actuators/methods.hpp					\
					actuators/cgi.hpp						\
					requests/Request.hpp					\
					responses/Response.hpp					\
					general.hpp

# Source and object files
SRC_FILES	= 	main.cpp								\
				network/server.cpp						\
				parsing/request_header_parsing.cpp		\
				conf/conf.cpp							\
				responses/responses.cpp					\
				responses/Filetypes.cpp					\
				responses/Directories.cpp				\
				actuators/get.cpp						\
				actuators/cgi.cpp						\
				to_string.cpp							\
				requests/Request.cpp					\
				responses/Response.cpp					\
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
$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp $(INCLUDES)
	@mkdir -p $(@D)
	@$(GCC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

# Compiling
$(NAME): $(OBJ)
	@echo "\033[0;33mCompiling... Wait a sec.\033[0;39m"
	@$(GCC) $(OBJ) $(FLAGS) -lm -o $(NAME)
	@echo "\033[0;32m$(NAME) generated!\033[0m"

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
