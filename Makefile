# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 10:53:31 by emadriga          #+#    #+#              #
#    Updated: 2023/06/08 12:57:19 by emadriga         ###   ########.fr        #
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
					network/listen_sockets.hpp				\
					network/cached_response.hpp				\
					conf/conf.hpp							\
					conf/serverconf.hpp						\
					conf/location.hpp						\
					conf/Filetypes.hpp						\
					actuators/cgi.hpp						\
					requests/Request.hpp					\
					responses/Response.hpp					\
					general.hpp

# Source and object files
SRC_FILES	= 	main.cpp								\
				network/server.cpp						\
				network/listen_sockets.cpp				\
				parsing/request_header_parsing.cpp		\
				conf/conf.cpp							\
				conf/Filetypes.cpp						\
				conf/serverconf.cpp						\
				responses/Directories.cpp				\
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
		@./scripts/pre_gTest.sh
		@./scripts/enableExceptions.sh
		cmake $(MACHINE) -S ./gTest -B $(BUILD_DIR) # devs
		cmake --build $(BUILD_DIR)
		@./scripts/post_gTest.sh

MACHINE= -Wno-dev
# MACHINE=


# phony
.PHONY:		all clean fclean re gTest
