#!/bin/bash
# THis script set 42 madrid termination mail (@student.42madrid.com) properly on *.cpp, *.hpp & Makfile

if [ $(uname -s) = 'Darwin' ]; then
	find . -type f -name "*.cpp" -exec sed -i "" "s|@student.42.fr>          +#+  +:+       +#+        |@student.42madrid.com>   +#+  +:+       +#+        |" {} +
	find . -type f -name "*.hpp" -exec sed -i "" "s|@student.42.fr>          +#+  +:+       +#+        |@student.42madrid.com>   +#+  +:+       +#+        |" {} +
	find . -type f -name "Makefile" -exec sed -i "" "s|@student.42.fr>          +#+  +:+       +#+        |@student.42madrid.com>   +#+  +:+       +#+        |" {} +
elif [ $(uname -s) = 'Linux' ]; then
	find . -type f -name "*.cpp" -exec sed -i 's|@student.42.fr>          +#+  +:+       +#+        |@student.42madrid.com>   +#+  +:+       +#+        |' {} +
	find . -type f -name "*.hpp" -exec sed -i 's|@student.42.fr>          +#+  +:+       +#+        |@student.42madrid.com>   +#+  +:+       +#+        |' {} +
	find . -type f -name "Makefile" -exec sed -i 's|@student.42.fr>          +#+  +:+       +#+        |@student.42madrid.com>   +#+  +:+       +#+        |' {} +
else
	echo "This unit test are prepared to run either on Linux or Darwin systems"
fi